// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>

#define BUF_SIZE 1024
#define PORT 8888
#define TIMEOUT 5000  // 超时时间（单位：毫秒）
#define WINDOW_SIZE 5 // 窗口大小

// 数据包结构体
struct packet
{
    int seq_num;         // 序列号
    int ack_num;         // 确认号
    int data_len;        // 数据长度
    char data[BUF_SIZE]; // 数据
};

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    int base_seq_num = 0;              // 窗口中第一个未确认的序列号
    int next_seq_num = 0;              // 下一个要发送的序列号
    int ack_num = -1;                  // 当前已收到的最大确认号
    struct packet window[WINDOW_SIZE]; // 窗口
    int window_size = 0;               // 当前窗口大小
    struct timeval start_time;         // 发送窗口中第一个数据包的时间
    int is_timeout = 0;                // 是否超时

    // 创建UDP套接字
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    // 绑定服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    printf("服务器已启动，等待客户端连接...\n");

    while (1)
    {
        // 接收客户端数据
        int recv_len = recvfrom(server_fd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len < 0)
        {
            perror("recvfrom");
            exit(1);
        }

        // 解析数据包
        struct packet recv_packet;
        memcpy(&recv_packet, buffer, sizeof(recv_packet));

        // 处理数据包
        if (recv_packet.seq_num == ack_num + 1) // 收到的是期望的数据包
        {
            ack_num = recv_packet.seq_num;
            printf("收到数据包：%d\n", ack_num);

            // 将窗口中已确认的数据包移除
            int i;
            for (i = 0; i < window_size; i++)
            {
                if (window[i].seq_num == ack_num + 1)
                {
                    window_size--;
                    memmove(window, window + 1, window_size * sizeof(struct packet));
                    break;
                }
            }

            // 如果窗口中还有未确认的数据包，重新计时
            if (window_size > 0)
            {
                gettimeofday(&start_time, NULL);
                is_timeout = 0;
            }
            
        }
        else if (recv_packet.seq_num <= ack_num) // 收到的是已确认的数据包
        {
            printf("收到重复数据包：%d\n", recv_packet.seq_num);
        }
        else // 收到的是未确认的数据包
        {
            // 将数据包插入窗口
            if (window_size < WINDOW_SIZE)
            {
                memcpy(&window[window_size], &recv_packet, sizeof(recv_packet));
                window_size++;
                printf("收到数据包：%d\n", recv_packet.seq_num);
            }
            else
            {
                printf("窗口已满，丢弃数据包：%d\n", recv_packet.seq_num);
            }

            // 发送ACK确认
            struct packet ack_packet;
            ack_packet.seq_num = -1;
            ack_packet.ack_num = ack_num;
            ack_packet.data_len = 0;

            int send_len = sendto(server_fd, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr *)&client_addr, addr_len);
            if (send_len < 0)
            {
                perror("sendto");
                exit(1);
            }

            // 如果窗口中只有一个数据包，开始计时
            if (window_size == 1)
            {
                gettimeofday(&start_time, NULL);
                is_timeout = 0;
            }
        }

        // 检查是否超时
        if (window_size > 0)
        {
            struct timeval now;
            gettimeofday(&now, NULL);
            long elapsed_time = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
            if (elapsed_time >= TIMEOUT)
            {
                printf("超时，重传数据包：%d\n", window[0].seq_num);

                int send_len = sendto(server_fd, &window[0], sizeof(window[0]), 0, (struct sockaddr *)&client_addr, addr_len);
                if (send_len < 0)
                {
                    perror("sendto");
                    exit(1);
                }

                gettimeofday(&start_time, NULL);
                is_timeout = 1;
            }
        }

        // 发送窗口中的数据包
        while (next_seq_num < base_seq_num + WINDOW_SIZE && next_seq_num < ack_num + 2 && next_seq_num < window[0].seq_num + WINDOW_SIZE)
        {
            struct packet send_packet;
            send_packet.seq_num = next_seq_num;
            send_packet.ack_num = -1;
            send_packet.data_len = sprintf(send_packet.data, "数据包：%d", next_seq_num);

            int send_len = sendto(server_fd, &send_packet, sizeof(send_packet), 0, (struct sockaddr *)&client_addr, addr_len);
            if (send_len < 0)
            {
                perror("sendto");
                exit(1);
            }

            printf("发送数据包：%d\n", next_seq_num);

            // 将数据包插入窗口
            if (window_size < WINDOW_SIZE)
            {
                memcpy(&window[window_size], &send_packet, sizeof(send_packet));
                window_size++;
            }
            else
            {
                printf("窗口已满，丢弃数据包：%d\n", send_packet.seq_num);
            }

            next_seq_num++;
        }

        // 如果窗口中只有一个数据包，并且已经超时一次，开始拥塞控制
        if (window_size == 1 && is_timeout)
        {
            window_size /= 2;
            printf("拥塞控制，窗口大小降为%d\n", window_size);
        }
        else
        { // 如果窗口大小小于等于2，开始慢启动
            if (window_size <= 2)
            {
                window_size;
                printf("慢启动，窗口大小增加为%d\n", window_size);
            }
            else
            { // 如果窗口大小大于2，开始拥塞避免
                window_size += window_size / 2;
                printf("拥塞避免，窗口大小增加为%d\n", window_size);
            }
        }
    }
    close(server_fd);
    return 0;
}

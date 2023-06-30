// client.c
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
#define SERVER_IP "127.0.0.1"
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
    int client_fd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUF_SIZE];
    int base_seq_num = 0;              // 窗口中第一个未确认的序列号
    int next_seq_num = 0;              // 下一个要发送的序列号
    int ack_num = -1;                  // 当前已收到的最大确认号
    struct packet window[WINDOW_SIZE]; // 窗口
    int window_size = 0;               // 当前窗口大小
    struct timeval start_time;         // 发送窗口中第一个数据包的时间
    int is_timeout = 0;                // 是否超时

    // 创建UDP套接字
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (1)
    {
        // 发送窗口中的数据包
        while (next_seq_num < base_seq_num + WINDOW_SIZE)
        {
            struct packet send_packet;
            send_packet.seq_num = next_seq_num;
            send_packet.ack_num = ack_num;
            send_packet.data_len = sprintf(send_packet.data, "数据包：%d", next_seq_num);

            int send_len = sendto(client_fd, &send_packet, sizeof(send_packet), 0, (struct sockaddr *)&server_addr, addr_len);
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

        // 检查是否超时
        if (window_size > 0)
        {
            struct timeval now;
            gettimeofday(&now, NULL);
            long elapsed_time = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
            if (elapsed_time >= TIMEOUT)
            {
                printf("超时，重传数据包：%d\n", window[0].seq_num);

                int send_len = sendto(client_fd, &window[0], sizeof(window[0]), 0, (struct sockaddr *)&server_addr, addr_len);
                if (send_len < 0)
                {
                    perror("sendto");
                    exit(1);
                }

                gettimeofday(&start_time, NULL);
                is_timeout = 1;
            }
        }

        // 接收服务器返回的ACK确认
        int recv_len = recvfrom(client_fd, buffer, BUF_SIZE, 0, NULL, NULL);
        if (recv_len < 0)
        {
            perror("recvfrom");
            exit(1);
        }

        // 解析ACK确认
        struct packet recv_packet;
        memcpy(&recv_packet, buffer, sizeof(recv_packet));

        // 处理ACK确认
        if (recv_packet.ack_num == ack_num) // 收到的是重复的ACK确认
        {
            printf("收到重复ACK确认：%d\n", recv_packet.ack_num);
        }
        else if (recv_packet.ack_num > ack_num) // 收到的是新的ACK确认
        {
            ack_num = recv_packet.ack_num;
            printf("收到ACK确认：%d\n", ack_num);

            // 将窗口中已确认的数据包移除
            int i;
            for (i = 0; i < window_size; i++)
            {
                if (window[i].seq_num <= ack_num)
                {
                    printf("移除已确认数据包：%d\n", window[i].seq_num);
                    window_size--;
                    base_seq_num++;
                }
                else
                {
                    break;
                }
            }
            // 更新窗口大小
            window_size -= i;

            // 更新发送窗口中第一个数据包的时间
            if (window_size > 0)
            {
                gettimeofday(&start_time, NULL);
                is_timeout = 0;
            }
        }

        // 如果窗口为空且没有超时，则等待ACK确认
        if (window_size == 0 && !is_timeout)
        {
            printf("等待ACK确认...\n");
            usleep(TIMEOUT);
        }
    }

    return 0;
}
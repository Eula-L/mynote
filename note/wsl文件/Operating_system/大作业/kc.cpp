#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 进程结构体
struct Process {
    int pid;  // 进程ID
    int arrivalTime;  // 到达时间
    int burstTime;  // 执行时间
    int remainingTime;  // 剩余执行时间
    int priority;  // 优先级
};

// 多级反馈队列调度类
class MFQScheduler {
private:
    vector<queue<Process>> queues;  // 多个队列
    vector<int> timeQuantums;  // 每个队列的时间片大小

public:
    MFQScheduler(const vector<int>& quantums) {
        int numQueues = quantums.size();
        this->queues.resize(numQueues);
        this->timeQuantums = quantums;
    }

    // 添加进程到第一个队列
    void addProcess(const Process& process) {
        queues[0].push(process);
    }

    // 执行调度
    void schedule() {
        int currentTime = 0;
        int currentQueue = 0;

        while (true) {
            // 选择下一个要执行的进程
            Process& currentProcess = queues[currentQueue].front();

            // 更新进程状态
            int timeQuantum = timeQuantums[currentQueue];
            currentProcess.remainingTime -= timeQuantum;
            currentTime += timeQuantum;

            // 进程执行完毕
            if (currentProcess.remainingTime <= 0) {
                cout << "进程 " << currentProcess.pid << " 执行完毕，耗时 " << currentTime << " 单位时间" << endl;
                queues[currentQueue].pop();
            }
            // 进程未执行完毕，移到下一个队列
            else {
                cout << "进程 " << currentProcess.pid << " 时间片用尽，移到下一个队列" << endl;
                queues[currentQueue].pop();
                queues[currentQueue + 1].push(currentProcess);
            }

            // 检查是否所有队列都为空
            bool allQueuesEmpty = true;
            for (const auto& queue : queues) {
                if (!queue.empty()) {
                    allQueuesEmpty = false;
                    break;
                }
            }

            // 所有队列都为空，调度结束
            if (allQueuesEmpty) {
                break;
            }

            // 切换到下一个队列
            currentQueue = (currentQueue + 1) % queues.size();
        }
    }
};

int main() {
    // 创建多级反馈队列调度器
    vector<int> timeQuantums = { 4, 8, 16 };  // 每个队列的时间片大小
    MFQScheduler scheduler(timeQuantums);

    // 从键盘输入进程数量
    int numProcesses;
    cout << "请输入进程数量：";
    cin >> numProcesses;

    // 从键盘输入进程信息
    for (int i = 0; i < numProcesses; i++) {
        Process process;
        cout << "请输入进程 " << i + 1 << " 的到达时间：";
        cin >> process.arrivalTime;
        cout << "请输入进程 " << i + 1 << " 的执行时间：";
        cin >> process.burstTime;
        process.remainingTime = process.burstTime;
        cout << "请输入进程 " << i + 1 << " 的优先级：";
        cin >> process.priority;
        process.pid = i + 1;

        scheduler.addProcess(process);
    }

    // 执行调度
    scheduler.schedule();

    return 0;
}
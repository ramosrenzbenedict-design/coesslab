#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    double burst;
    double burstRemaining;
    double waiting;
    double turnaround;
    double completionTime;
};

int main() {
    const int n = 5;
    const double timeQuantum = 20;

    Process p[n] = {
        {1, 50.54, 50.54, 0, 0, 0},
        {2, 10.11, 10.11, 0, 0, 0},
        {3, 33.34, 33.34, 0, 0, 0},
        {4, 2.5, 2.5, 0, 0, 0},
        {5, 101.1, 101.1, 0, 0, 0}
    };

    queue<int> readyQueue;
    for (int i = 0; i < n; i++) {
        readyQueue.push(i);
    }

    double currentTime = 0;

    // Round Robin scheduling
    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();

        double timeUsed = min(timeQuantum, p[idx].burstRemaining);

        p[idx].burstRemaining -= timeUsed;
        currentTime += timeUsed;

        if (p[idx].burstRemaining > 0) {
            // Process not finished, add back to queue
            readyQueue.push(idx);
        } else {
            // Process finished
            p[idx].completionTime = currentTime;
        }
    }

    // Calculate turnaround and waiting times for all processes
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completionTime - 0; // All processes arrive at time 0
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    // Output
    cout << fixed << setprecision(2);
    cout << "Round Robin Scheduling (Time Quantum = " << timeQuantum << ")\n";
    cout << "============================================\n";
    cout << "PID\tBurst\tWaiting\tTurnaround\tCompletion\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].burst << "\t"
             << p[i].waiting << "\t"
             << p[i].turnaround << "\t\t"
             << p[i].completionTime << "\n";
    }

    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    cout << "\nAverage Waiting Time = " << totalWT / n << "\n";
    cout << "Average Turnaround Time = " << totalTAT / n << "\n";

    return 0;
}
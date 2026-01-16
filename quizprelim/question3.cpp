#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    double burst;
    double waiting;
    double turnaround;
};

int main() {
    const int n = 5;
    Process p[n] = {
        {1, 50.54, 0, 0},
        {2, 10.11, 0, 0},
        {3, 33.34, 0, 0},
        {4, 2.5, 0, 0},
        {5, 101.1, 0, 0}
    };

    // Sort by burst time (SJF)
    sort(p, p + n, [](Process a, Process b) {
        return a.burst < b.burst;
    });

    // Calculate waiting time
    p[0].waiting = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting = p[i - 1].waiting + p[i - 1].burst;
    }

    // Calculate turnaround time
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].waiting + p[i].burst;
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    // Output
    cout << fixed << setprecision(2);
    cout << "Shortest Job First (SJF) Scheduling\n";
    cout << "====================================\n";
    cout << "PID\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].burst << "\t"
             << p[i].waiting << "\t"
             << p[i].turnaround << "\n";
    }

    cout << "\nAverage Waiting Time = " << totalWT / n << "\n";
    cout << "Average Turnaround Time = " << totalTAT / n << "\n";

    return 0;
}
#include <iostream>
#include <iomanip>
using namespace std;

struct Process {
int pid;
double burst;
double waiting;
double turnaround;
double completionTime;
};

int main() {
    const int n = 10;
    Process p[n] = {
    {1, 3, 0, 0, 0},
    {2, 5, 0, 0, 0},
    {3, 4, 0, 0, 0},
    {4, 3, 0, 0, 0},
    {5, 2, 0, 0, 0},
    {6, 1, 0, 0, 0},
    {7, 6, 0, 0, 0},
    {8, 7, 0, 0, 0},
    {9, 8, 0, 0, 0},
    {10, 1, 0, 0, 0}
    };

    // FCFS Scheduling
    double currentTime = 0;
    for (int i = 0; i < n; i++) {
        p[i].waiting = currentTime;
        currentTime += p[i].burst;
        p[i].completionTime = currentTime;
        p[i].turnaround = p[i].completionTime - 0; // Arrival time is 0
    }

    // Output
    cout << fixed << setprecision(2);
    cout << "First Come First Serve (FCFS) Scheduling\n";
    cout << "=========================================\n";
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
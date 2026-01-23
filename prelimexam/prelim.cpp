#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct Process {
    string pid[8];
    int at[8];
    int bt[8];
    int br[8];
    int ct[8];
    double tt[8];
    double wt[8];
};

int timeQuantum(Process p) {
    int sum = 0;
    for(int i = 0; i < 8; i++) sum += p.bt[i];
    double mean = (double)sum / 8.0;
    return round(mean);
}

void RoundRobin(Process &p, int tq) {
    vector<int> remaining(p.bt, p.bt + 8);
    vector<bool> completed(8, false);
    vector<bool> in_queue(8, false);
    queue<int> q;
    int current_time = 0;
    int completed_count = 0;
    int current_process = -1;
    while(completed_count < 8) {
        // Add arrived processes
        for(int j = 0; j < 8; j++) {
            if(p.at[j] <= current_time && !completed[j] && !in_queue[j]) {
                q.push(j);
                in_queue[j] = true;
            }
        }
        if(current_process == -1 && !q.empty()) {
            current_process = q.front();
            q.pop();
            in_queue[current_process] = false;
        }
        if(current_process != -1) {
            int exec_time = min(tq, remaining[current_process]);
            current_time += exec_time;
            remaining[current_process] -= exec_time;
            if(remaining[current_process] == 0) {
                completed[current_process] = true;
                p.ct[current_process] = current_time;
                p.tt[current_process] = p.ct[current_process] - p.at[current_process];
                p.wt[current_process] = p.tt[current_process] - p.bt[current_process];
                completed_count++;
                current_process = -1;
            } else {
                q.push(current_process);
                in_queue[current_process] = true;
                current_process = -1;
            }
        } else {
            // Advance to next arrival
            int next_at = INT_MAX;
            for(int j = 0; j < 8; j++) {
                if(!completed[j]) next_at = min(next_at, p.at[j]);
            }
            current_time = next_at;
        }
    }
    // Print table
    cout << "Round Robin Scheduling:" << endl;
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << endl;
    for(int i = 0; i < 8; i++) {
        cout << left << setw(5) << p.pid[i] << setw(5) << p.at[i] << setw(5) << p.bt[i] << setw(5) << p.ct[i] << setw(5) << p.tt[i] << setw(5) << p.wt[i] << endl;
    }
    double avg_tt = 0, avg_wt = 0;
    for(int i = 0; i < 8; i++) {
        avg_tt += p.tt[i];
        avg_wt += p.wt[i];
    }
    avg_tt /= 8;
    avg_wt /= 8;
    cout << "Average Turnaround Time: " << avg_tt << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

void ShortestJobFirst(Process &p) {
    vector<int> remaining(p.bt, p.bt + 8);
    vector<bool> completed(8, false);
    int current_time = 0;
    int completed_count = 0;

    while(completed_count < 8) {
        int min_bt = INT_MAX;
        int selected = -1;
        for(int i = 0; i < 8; i++) {
            if(p.at[i] <= current_time && !completed[i] && remaining[i] < min_bt) {
                min_bt = remaining[i];
                selected = i;
            }
        }
        if(selected == -1) {
            // No process ready, advance to next arrival
            int next_at = INT_MAX;
            for(int i = 0; i < 8; i++) {
                if(!completed[i]) next_at = min(next_at, p.at[i]);
            }
            current_time = next_at;
            continue;
        }
        // Execute selected process fully
        current_time += remaining[selected];
        remaining[selected] = 0;
        completed[selected] = true;
        p.ct[selected] = current_time;
        p.tt[selected] = p.ct[selected] - p.at[selected];
        p.wt[selected] = p.tt[selected] - p.bt[selected];
        completed_count++;
    }

    // Print table
    cout << "Shortest Job First Scheduling:" << endl;
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << endl;
    for(int i = 0; i < 8; i++) {
        cout << left << setw(5) << p.pid[i] << setw(5) << p.at[i] << setw(5) << p.bt[i] << setw(5) << p.ct[i] << setw(5) << p.tt[i] << setw(5) << p.wt[i] << endl;
    }
    double avg_tt = 0, avg_wt = 0;
    for(int i = 0; i < 8; i++) {
        avg_tt += p.tt[i];
        avg_wt += p.wt[i];
    }
    avg_tt /= 8;
    avg_wt /= 8;
    cout << "Average Turnaround Time: " << avg_tt << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

void ShortestRemainingTimeFirst(Process &p) {
    vector<int> remaining(p.bt, p.bt + 8);
    vector<bool> completed(8, false);
    int current_time = 0;
    int completed_count = 0;
    int current_process = -1;

    while(completed_count < 8) {
        // Find the process with smallest remaining time among arrived
        int min_rem = INT_MAX;
        int candidate = -1;
        for(int i = 0; i < 8; i++) {
            if(p.at[i] <= current_time && !completed[i] && remaining[i] < min_rem) {
                min_rem = remaining[i];
                candidate = i;
            }
        }
        if(candidate == -1) {
            // No process ready, advance to next arrival
            int next_at = INT_MAX;
            for(int i = 0; i < 8; i++) {
                if(!completed[i]) next_at = min(next_at, p.at[i]);
            }
            current_time = next_at;
            continue;
        }
        if(current_process != candidate) {
            current_process = candidate;
        }
        // Execute until next event
        int exec_time = remaining[current_process];
        int next_arrival = INT_MAX;
        for(int i = 0; i < 8; i++) {
            if(!completed[i] && p.at[i] > current_time) {
                next_arrival = min(next_arrival, p.at[i]);
            }
        }
        exec_time = min(exec_time, next_arrival - current_time);
        current_time += exec_time;
        remaining[current_process] -= exec_time;
        if(remaining[current_process] == 0) {
            completed[current_process] = true;
            p.ct[current_process] = current_time;
            p.tt[current_process] = p.ct[current_process] - p.at[current_process];
            p.wt[current_process] = p.tt[current_process] - p.bt[current_process];
            completed_count++;
            current_process = -1;
        }
    }

    // Print table
    cout << "Shortest Remaining Time First Scheduling:" << endl;
    cout << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" << setw(5) << "CT" << setw(5) << "TT" << setw(5) << "WT" << endl;
    for(int i = 0; i < 8; i++) {
        cout << left << setw(5) << p.pid[i] << setw(5) << p.at[i] << setw(5) << p.bt[i] << setw(5) << p.ct[i] << setw(5) << p.tt[i] << setw(5) << p.wt[i] << endl;
    }
    double avg_tt = 0, avg_wt = 0;
    for(int i = 0; i < 8; i++) {
        avg_tt += p.tt[i];
        avg_wt += p.wt[i];
    }
    avg_tt /= 8;
    avg_wt /= 8;
    cout << "Average Turnaround Time: " << avg_tt << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;
}

int main() {
    Process p;
    string pids[8] = {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8"};
    for(int i = 0; i < 8; i++) p.pid[i] = pids[i];
    int ats[8] = {4, 2, 3, 6, 1, 5, 8, 7};
    for(int i = 0; i < 8; i++) p.at[i] = ats[i];
    int bts[8] = {53, 43, 18, 16, 44, 73, 99, 27};
    for(int i = 0; i < 8; i++) p.bt[i] = bts[i];
    for(int i = 0; i < 8; i++) p.br[i] = p.bt[i];
    // ct, tt, wt are already arrays, no need to initialize

    int tq = timeQuantum(p);
    cout << "Recommended Value for Time Quantum(MEAN): " << tq << endl;
    cout << "\n\n";
    RoundRobin(p, tq);
    cout << "\n\n";
    ShortestJobFirst(p);
    cout << "\n\n";
    ShortestRemainingTimeFirst(p);

    return 0;
}
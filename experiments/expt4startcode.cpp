/*Ques. 13. Write a program for multilevel queue scheduling algorithm. There must be three
/queues generated. There must be specific range of priority associated with every queue. Now
prompt the user to enter number of processes along with their priority and burst time. Each
process must occupy the respective queue with specific priority range according to its priority.
Apply Round robin algorithm with quantum time 4 on queue with highest priority range. Apply
priority scheduling algorithm on the queue with medium range of priority and First come first
serve algorithm on the queue with lowest range of priority. Each and every queue should get a
quantum time of 10 seconds. Cpu will keep on shifting between queues after every 10
seconds i.e. to apply round robin algorithm of 10 seconds on over all structure.
Calculate Waiting time and turnaround time for every process. The input for number of
processes should be given by the user.
*/

//ALGORITHM
//Initiate 3 queues and associate specific range of priority with every queue
//Enter number of processes along with their priority and burst time.
//Each process should occupy respective queue
//Apply Round Robin Algorithm (q=4) with highest priority range
//Apply Priority Scheduling Algorithm on medium priority range
//First Come First Serve on lowest priority range
//Each queue will only get 10 seconds
//Round Robin on overall structure

//q1 : p1,p2,p3 |RR(4) |
//q2 : p4,p5,p6 |PS ---| Round Robin (10)
//q3 : p7,p8,p9 |FCFS |

#include <iostream>
#include <algorithm>

using namespace std;

struct process {
int pid;
int priority;
int burst_time;
int initial_burst_time;
int completion_time = 0; // Stores exactly when the process finished
};

struct queues {
int priority_start;
int priority_end;
int length = 0;
process *p;
bool executed = false;
};

// Check if there are still processes pending in any queue
bool notComplete(queues q[]) {
bool pending = false;
int countCompleted = 0;
for (int i = 0; i < 3; i++) {
countCompleted = 0;
for (int j = 0; j < q[i].length; j++) {
if (q[i].p[j].burst_time != 0) {
pending = true;
} else {
countCompleted++;
}
}
if (countCompleted == q[i].length) {
q[i].executed = true;
}
}
return pending;
}

// Sort for Priority Scheduling (Queue 2)
void sort_ps(queues &q) {
for (int i = 1; i < q.length; i++) {
for (int j = 0; j < q.length - 1; j++) {
if (q.p[j].priority < q.p[j + 1].priority) {
process temp = q.p[j + 1];
q.p[j + 1] = q.p[j];
q.p[j] = temp;
}
}
}
}

int main() {
queues q[3];
q[0].priority_start = 7; q[0].priority_end = 9; // High
q[1].priority_start = 4; q[1].priority_end = 6; // Medium
q[2].priority_start = 1; q[2].priority_end = 3; // Low

int no_of_processes, priority_of_process, burst_time_of_process;

cout << "--- Multilevel Queue Scheduler Simulation ---\n";
cout << "Enter the number of processes: ";
cin >> no_of_processes;

process *input_processes = new process[no_of_processes];

for (int i = 0; i < no_of_processes; i++) {
input_processes[i].pid = i + 1;
cout << "\nProcess P" << input_processes[i].pid << "\n";
cout << "Enter Priority (1-9): ";
cin >> priority_of_process;
cout << "Enter Burst Time: ";
cin >> burst_time_of_process;

input_processes[i].priority = priority_of_process;
input_processes[i].burst_time = burst_time_of_process;
input_processes[i].initial_burst_time = burst_time_of_process;

for (int j = 0; j < 3; j++) {
if (q[j].priority_start <= priority_of_process && priority_of_process <= q[j].priority_end) {
q[j].length++;
}
}
}

for (int i = 0; i < 3; i++) {
if(q[i].length > 0) q[i].p = new process[q[i].length];
else q[i].p = nullptr;
}

int c0 = 0, c1 = 0, c2 = 0;
for (int j = 0; j < no_of_processes; j++) {
int prio = input_processes[j].priority;
if (prio >= q[0].priority_start && prio <= q[0].priority_end) q[0].p[c0++] = input_processes[j];
else if (prio >= q[1].priority_start && prio <= q[1].priority_end) q[1].p[c1++] = input_processes[j];
else if (prio >= q[2].priority_start && prio <= q[2].priority_end) q[2].p[c2++] = input_processes[j];
}

delete[] input_processes;

// Simulation Variables
int global_timer = 0; // Total simulation time
int timer = 0; // 10-second switch timer
int current_q = -1;
int rr_timer = 4;

while (notComplete(q)) {
if (timer == 10) {
timer = 0;
}

current_q++;
if (current_q >= 3) current_q = 0;

if (q[current_q].executed || q[current_q].length == 0) {
if(q[0].executed && q[1].executed && q[2].executed) break;
continue;
}

cout << "\n>>> Switching to Queue " << current_q + 1 << " <<<\n";

// Queue 1: Round Robin (Q=4)
if (current_q == 0) {
rr_timer = 4;
for (int i = 0; i < q[current_q].length; i++) {
if (timer == 10) break;
if (q[current_q].p[i].burst_time == 0) continue;

while (rr_timer > 0 && q[current_q].p[i].burst_time > 0 && timer < 10) {
cout << "[Time " << global_timer << "] Executing P" << q[current_q].p[i].pid << " (Queue 1)\n";
q[current_q].p[i].burst_time--;
global_timer++; // Increment global clock
timer++;
rr_timer--;

// Capture Completion Time immediately when burst becomes 0
if (q[current_q].p[i].burst_time == 0) {
q[current_q].p[i].completion_time = global_timer;
}
}
if (rr_timer == 0) rr_timer = 4;
}
}

// Queue 2: Priority Scheduling
else if (current_q == 1) {
sort_ps(q[current_q]);
for (int i = 0; i < q[current_q].length; i++) {
if (timer == 10) break;
if (q[current_q].p[i].burst_time == 0) continue;

while (q[current_q].p[i].burst_time > 0 && timer < 10) {
cout << "[Time " << global_timer << "] Executing P" << q[current_q].p[i].pid << " (Queue 2)\n";
q[current_q].p[i].burst_time--;
global_timer++;
timer++;

if (q[current_q].p[i].burst_time == 0) {
q[current_q].p[i].completion_time = global_timer;
}
}
}
}

// Queue 3: FCFS
else {
for (int i = 0; i < q[current_q].length; i++) {
if (timer == 10) break;
if (q[current_q].p[i].burst_time == 0) continue;

while (q[current_q].p[i].burst_time > 0 && timer < 10) {
cout << "[Time " << global_timer << "] Executing P" << q[current_q].p[i].pid << " (Queue 3)\n";
q[current_q].p[i].burst_time--;
global_timer++;
timer++;

if (q[current_q].p[i].burst_time == 0) {
q[current_q].p[i].completion_time = global_timer;
}
}
}
}
}

// Calculation and Printing
cout << "\n\n--- Final Statistics ---\n";
cout << "PID\tPriority\tBurst Time\tTurnaround Time\tWaiting Time\n";

float total_tt = 0, total_wt = 0;

for (int i = 0; i < 3; i++) {
for (int j = 0; j < q[i].length; j++) {
// TAT = Completion Time - Arrival Time (Assumption: Arrival is 0)
int tat = q[i].p[j].completion_time;

// WT = TAT - Initial Burst
int wt = tat - q[i].p[j].initial_burst_time;

cout << "P" << q[i].p[j].pid << "\t"
<< q[i].p[j].priority << "\t\t"
<< q[i].p[j].initial_burst_time << "\t\t"
<< tat << "\t\t" << wt << "\n";

total_tt += tat;
total_wt += wt;
}
}

if (no_of_processes > 0) {
cout << "\nAverage Turnaround Time: " << total_tt / no_of_processes << endl;
cout << "Average Waiting Time: " << total_wt / no_of_processes << endl;
}

for(int i=0; i<3; i++) {
if(q[i].p != nullptr) delete[] q[i].p;
}

return 0;
}
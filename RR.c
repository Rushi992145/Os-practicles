#include <stdio.h>

struct Process {
    int id;             // Process ID
    int arrival_time;    // Arrival time of the process
    int burst_time;      // Burst time of the process
    int remaining_time;  // Remaining burst time
    int start_time;
    int completion_time; // Completion time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
};

int main() 
{
    int n, tq, time = 0, completed = 0, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
    }

    // Input time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Process queue management
    int queue[100], front = 0, rear = 0;
    int is_in_queue[n]; // To track if a process is already in the queue
    for (i = 0; i < n; i++) is_in_queue[i] = 0;

    // Push first process to the queue if it arrives at time 0
    for (i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear++] = i;
            is_in_queue[i] = 1;
        }
    }

    // Round Robin Execution
    while (completed < n) {
        if (front < rear) {
            // Dequeue the first process
            int current = queue[front++];
            int exec_time = (processes[current].remaining_time <= tq) ? processes[current].remaining_time : tq;

            // Process executes
            if(processes[current].remaining_time == processes[current].burst_time) processes[current].start_time = time;
            time += exec_time;
            processes[current].remaining_time -= exec_time;

            // Check if the process is completed
            if (processes[current].remaining_time == 0) {
                completed++;
                processes[current].completion_time = time;
                processes[current].turnaround_time = time - processes[current].arrival_time;
                processes[current].waiting_time = processes[current].turnaround_time - processes[current].burst_time;
            }

            // Add newly arrived processes to the queue
            for (i = 0; i < n; i++) {
                if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && !is_in_queue[i]) {
                    queue[rear++] = i;
                    is_in_queue[i] = 1;
                }
            }

            // Requeue the current process if not completed
            if (processes[current].remaining_time > 0) {
                queue[rear++] = current;
            }
        } else {
            // CPU idle, increment time and check for new arrivals
            time++;
            for (i = 0; i < n; i++) {
                if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && !is_in_queue[i]) {
                    queue[rear++] = i;
                    is_in_queue[i] = 1;
                }
            }
        }
    }

    // Output results
    printf("PID | AT  | BT  | ST  | ET  | WT  | TWT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- \n"); 

    float total_tat = 0, total_wt = 0;
    for (i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d \n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
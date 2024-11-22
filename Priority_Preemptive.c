#include <stdio.h>
#define MAX 100

void find_highest_priority_process(int current_time, int *cur_ind, int *cur_prio, int arrival[], int burst[], int priority[], int completed[], int n) {
    *cur_ind = -1;
    *cur_prio = 101; 

    for (int i = 0; i < n; i++) {
        if (arrival[i] <= current_time && completed[i] == 0) {
            if (priority[i] < *cur_prio) {
                *cur_prio = priority[i];
                *cur_ind = i;
            }
        }
    }
}



void PP(int id[], int arrival[], int burst[], int priority[], int n) {
    int start[MAX] = {0}, end[MAX] = {0}, turnaround[MAX] = {0}, waiting[MAX] = {0};
    int remaining_time[MAX];
    int completed[MAX] = {0};
    int current_time = 0;
    int total_executed = 0;
    int cur_prio;
    int cur_ind = -1;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst[i];
    }

    while (total_executed < n) {
        find_highest_priority_process(current_time, &cur_ind, &cur_prio, arrival, burst, priority, completed, n);

        if (cur_ind == -1) {
            printf("%d -> -1\n", current_time);
        } else {
            if (remaining_time[cur_ind] == burst[cur_ind]) {
                start[cur_ind] = current_time;
            }
            printf("%d -> P%d\n", current_time, id[cur_ind]);
            remaining_time[cur_ind]--;

            if (remaining_time[cur_ind] == 0) {
                end[cur_ind] = current_time + 1;
                completed[cur_ind] = 1;
                total_executed++;
                turnaround[cur_ind] = end[cur_ind] - arrival[cur_ind];
                waiting[cur_ind] = turnaround[cur_ind] - burst[cur_ind];
            }
        }
        current_time++;
    }

    
     printf("PID | AT  | BT  | PR  | ST  | ET  | WT  | TAT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- | --- \n"); 
    for (int i = 0; i < n; i++) { 
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d | %3d \n",id[i],arrival[i], burst[i],priority[i], start[i], end[i], waiting[i], turnaround[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        turnaround[i] = end[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
        total_wt += waiting[i];
        total_tat += turnaround[i];
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    int id[MAX], arrival[MAX], burst[MAX], priority[MAX];

    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &arrival[i], &burst[i], &priority[i]);
        id[i] = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n ; j++) {
            if (arrival[i] > arrival[j]) {
                int temp;

                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = id[i];
                id[i] = id[j];
                id[j] = temp;
            }
        }
    }

    PP(id, arrival, burst, priority, n);
    return 0;
}
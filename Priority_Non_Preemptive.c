#include <stdio.h>
#include <stdbool.h>

void display2(int n, int pid[], int at[], int bt[], int priority[], int st[], int et[], int wt[], int tat[]) {
    printf("PID | AT  | BT  | PR  | ST  | ET  | WT  | TAT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- | --- \n"); 
    for (int i = 0; i < n; i++) { 
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d | %3d \n", pid[i], at[i], bt[i], priority[i], st[i], et[i], wt[i], tat[i]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// void sort_according_to_priority(int n, int pid[], int at[], int bt[], int priority[], int start, int end) {
//     for (int i = start; i < end - 1; i++) {
//         for (int j = start; j < end - (i - start) - 1; j++) {
//             if (priority[j] > priority[j + 1]) {
//                 swap(&at[j], &at[j + 1]);
//                 swap(&bt[j], &bt[j + 1]);
//                 swap(&pid[j], &pid[j + 1]);
//                 swap(&priority[j], &priority[j + 1]);
//             }
//             else if(priority[j]==priority[j+1]) {
//                 if(bt[j] > bt[j + 1]) {
//                     swap(&at[j], &at[j + 1]);
//                     swap(&bt[j], &bt[j + 1]);
//                     swap(&pid[j], &pid[j + 1]);
//                     swap(&priority[j], &priority[j + 1]);
//                 }
//                 else if(bt[j]==bt[j+1]) {
//                     if(at[j]>at[j+1]) {
//                         swap(&at[j], &at[j + 1]);
//                         swap(&bt[j], &bt[j + 1]);
//                         swap(&pid[j], &pid[j + 1]);
//                         swap(&priority[j], &priority[j + 1]);
//                     }
//                 }
//             }
//         }
//     }
// }

void sort_according_to_at(int n, int pid[], int at[], int bt[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                swap(&pid[j], &pid[j + 1]);
                swap(&priority[j], &priority[j + 1]);
            }else if(at[j]==at[j+1]){
                if(priority[j]>priority[j+1]){
                swap(&at[j],&at[j+1]);
                swap(&bt[j],&bt[j+1]);
                swap(&pid[j],&pid[j+1]);
                swap(&priority[j],&priority[j+1]);
                }
            }
        }
    }
}

void calculate_schedule(int n, int pid[], int at[], int bt[], int priority[]) {
    int st[n], et[n], wt[n], tat[n];
    for (int i = 0; i < n; i++) {
        st[i] = 0;
        et[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    // Initial Scheduling
    st[0] = at[0];
    et[0] = at[0] + bt[0];

    for (int i = 1; i < n; i++) {
        int min_priority_index = i;
        for (int j = i; j < n; j++) {
            if (at[j] <= et[i - 1] && priority[j] < priority[min_priority_index]) {
                min_priority_index = j;
            }
        }

        // Swap to bring the highest priority process to current position
        swap(&at[i], &at[min_priority_index]);
        swap(&bt[i], &bt[min_priority_index]);
        swap(&pid[i], &pid[min_priority_index]);
        swap(&priority[i], &priority[min_priority_index]);

        // Schedule the selected process
        if (et[i - 1] > at[i]) {
            st[i] = et[i - 1];
        } else {
            st[i] = at[i];
        }
        et[i] = st[i] + bt[i];
    }

    // Calculate Turnaround Time and Waiting Time
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = et[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Display Results
    display2(n, pid, at, bt, priority, st, et, wt, tat);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], priority[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
    }

    sort_according_to_at(n, pid, at, bt, priority);
    calculate_schedule(n, pid, at, bt, priority);

    return 0;
}

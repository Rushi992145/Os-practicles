#include<stdio.h>
#include<stdbool.h>

void display(int n, int pid[], int at[], int bt[], int st[], int et[], int wt[], int tat[]) {
    printf("PID | AT  | BT  | ST  | ET  | WT  | TWT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- \n"); 
    for(int i = 0; i < n; i++) { 
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d \n",  pid[i], at[i], bt[i], st[i], et[i], wt[i], tat[i]);
    }
}

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_according_to_at(int pid[], int at[], int bt[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (at[i] > at[j]) {
                Swap(&at[i], &at[j]);
                Swap(&bt[i], &bt[j]);
                Swap(&pid[i], &pid[j]);
            }
            else if(at[i] == at[j] && bt[i]>bt[j]) {
                Swap(&at[i], &at[j]);
                Swap(&bt[i], &bt[j]);
                Swap(&pid[i], &pid[j]);
            }
        }
    }
}


void answer(int n, int pid[], int at[], int bt[], int st[], int et[], int wt[], int tat[]) {
    st[0] = at[0];
    et[0] = at[0] + bt[0];

    for (int i = 1; i < n; i++) {
        int min_brust_index = i;
        for (int j = i; j < n; j++) {
            if (at[j] <= et[i - 1] && bt[j] < bt[min_brust_index]) {
                min_brust_index = j;
            }
        }

        Swap(&at[i], &at[min_brust_index]);
        Swap(&bt[i], &bt[min_brust_index]);
        Swap(&pid[i], &pid[min_brust_index]);

        if (et[i - 1] >= at[i]) {
            st[i] = et[i - 1];
        } else {
            st[i] = at[i]; 
        }
        et[i] = st[i] + bt[i];
    }


    float avgWt = 0, avgTat = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = et[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgWt += wt[i];
        avgTat += tat[i];
    }

    display(n, pid, at, bt, st, et, wt, tat);
    printf("\nAverage Waiting Time -> %.2f\n", avgWt / n);
    printf("Average Turnaround Time -> %.2f\n", avgTat / n);
}

int main() {
    printf("Enter number of processors: ");
    int n;
    scanf("%d", &n);
    int pid[n], at[n], bt[n], st[n], et[n], wt[n], tat[n];

    printf("Enter  Arrival Time, and Burst Time\n");
    for (int i = 0; i < n; i++) {
        pid[i]=i;
        scanf("%d %d", &at[i], &bt[i]);
    }


    for (int i = 0; i < n; i++) {
        st[i] = 0;
        et[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    sort_according_to_at(pid, at, bt, n);
    answer(n, pid, at, bt, st, et, wt, tat);

    return 0;
}
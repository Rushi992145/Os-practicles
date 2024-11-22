#include<stdio.h>
#include <stdbool.h>
#include<limits.h>

void display2(int n,int pid[],int at[],int bt[],int st[],int et[],int wt[],int tat[]){
    printf("PID | AT  | BT  | ST  | ET  | WT  | TWT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- \n"); 
    for(int i = 0; i < n; i++) { 
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d \n",  pid[i], at[i], bt[i], st[i], et[i], wt[i], tat[i]);
    }
}

void Swap(int *a ,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void SJRF(int n, int pid[], int at[], int bt[], int rt[]){
    int st[n];
    int et[n];
    int wt[n];
    int tat[n]; 
    int curr_time = 0;
    int total_completed = 0;
    int min_rem_time = INT_MAX;
    int shortest = 0;
    bool check = false;

    for(int i=0;i<n;i++){
        st[i] = -1; 
        et[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    while (total_completed != n) {
        for (int i = 0; i < n; i++) {
            if (at[i] <= curr_time && rt[i] > 0 && rt[i] < min_rem_time) {
                min_rem_time = rt[i];
                shortest = i;
                check = true;
            }
        }

        if (check == false) {
            curr_time++;
            continue;
        }

        if (st[shortest] == -1) st[shortest] = curr_time;

        rt[shortest]--;

        if (rt[shortest] == 0) {
            total_completed++;
            et[shortest] = curr_time + 1;
            min_rem_time = INT_MAX;
        }

        curr_time++;
        check = false;
    }

    float avgWt=0,avgTat=0;
    for (int i = 0; i < n; i++) {
        tat[i] = et[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgWt=avgWt+wt[i];
        avgTat=avgTat+tat[i];
    }

    display2(n, pid, at, bt, st, et, wt, tat);
    printf("\nAverage WaitingTime -> %.2f",avgWt/n);
    printf("\nAverage TurnAroundTime -> %.2f",avgTat/n);
}




void sort_according_to_at(int n,int pid[],int at[],int bt[],int rt[]){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(at[j]>at[j+1]){
                Swap(&at[j],&at[j+1]);
                Swap(&bt[j],&bt[j+1]);
                Swap(&rt[j],&rt[j+1]);
                Swap(&pid[j],&pid[j+1]);
            }else if(at[j]==at[j+1]){
                if(bt[j]>bt[j+1]){
                Swap(&at[j],&at[j+1]);
                Swap(&bt[j],&bt[j+1]);
                Swap(&pid[j],&pid[j+1]);
                Swap(&rt[j],&rt[j+1]);
                }
            }
        }
    }
    printf("\n After sorting according to Arrival time\n");
}

int main(){
    int n;
    printf("Enter total number of processors: ");
    scanf("%d",&n);

    int pid[n];
    int at[n];
    int bt[n];
    int rt[n];


    printf("Enter arrival time ,burst time :\n");
    for(int i=0;i<n;i++){
        pid[i] = i;
        scanf("%d",&at[i]);
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
    }

    sort_according_to_at(n, pid, at, bt,rt);
    SJRF(n, pid, at, bt,rt);
    return 0;
}

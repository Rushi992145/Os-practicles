#include<stdio.h> 
void bubbleSort(int a[],int b[],int ind[],int n) { 
    for(int i=0;i<n;i++) { 
        for(int j=i+1;j<n;j++) { 
            if(a[i] > a[j]) { 
 
                int t = a[i]; 
                a[i] = a[j]; 
                a[j] = t; 
 
                int p = b[i]; 
                b[i] = b[j]; 
                b[j] = p; 
 
                int q = ind[i]; 
                ind[i] = ind[j]; 
                ind[j] = q; 
            } 
        } 
    } 
} 
 
 
int main() { 
    int n; 
 
    // Ask for the number of processes 
    printf("Enter the number of processes : "); 
    scanf("%d", &n); 
 
    // Check if the number of processes is within the allowed range 
    if (n < 1) { 
        printf("Invalid number of processes. Please enter a number between 1 and \n"); 
        return 1; 
    } 
 
    // Declare arrays with fixed size 
    int arrivalTime[n]; 
    int burstTime[n]; 
    int startTime[n]; 
    int endTime[n]; 
    int turnaroundTime[n]; 
    int waitingTime[n]; 
    int processNo[n]; 
 
    // Input arrival times and burst times 
    for (int i = 0; i < n; i++) { 
        printf("Arrival time of process P%d: ", i + 1); 
        scanf("%d", &arrivalTime[i]); 
 
        printf("Burst time of process P%d: ", i + 1); 
        scanf("%d", &burstTime[i]); 
 
        processNo[i] = i; 
    } 
 
    bubbleSort(arrivalTime,burstTime,processNo,n); 
 
    int stime = 0; 
    int ctime = 0; 
    for(int i = 0;i<n;i++) { 
        // Check if start time  is less than arrival time  if less then update it to arrival time 
        if(stime < arrivalTime[i]) stime = arrivalTime[i]; 
        startTime[i] = stime; 
        ctime = stime+burstTime[i]; 
        endTime[i] = ctime; 
        stime = ctime; 
    } 
 
    int copy[n]; 
    for(int i=0;i<n;i++) copy[i] = processNo[i]; 
 
    bubbleSort(processNo,arrivalTime,burstTime,n); 
    bubbleSort(copy,startTime,endTime,n); 
 
 
    for(int i=0;i<n;i++) { 
        waitingTime[i] = startTime[i] - arrivalTime[i]; 
        turnaroundTime[i] = endTime[i] - arrivalTime[i]; 
    } 
 
    //Displayig the table 
    printf("PID | AT  | BT  | ST  | ET  | WT  | TWT \n"); 
    printf("--- | --- | --- | --- | --- | --- | --- \n"); 
    for(int i = 0; i < n; i++) { 
        printf(" %2d | %3d | %3d | %3d | %3d | %3d | %3d \n", 
            processNo[i], arrivalTime[i], burstTime[i], startTime[i], endTime[i], waitingTime[i], 
turnaroundTime[i]); 
    } 
 
    printf("\n"); 
 
    int sumWT = 0; 
    int sumTWT = 0; 
    for(int i=0;i<n;i++) { 
        sumTWT += turnaroundTime[i]; 
        sumWT += waitingTime[i]; 
    } 
 
    float avgWT = (float)(sumWT)/n; 
    float avgTWT = (float)(sumTWT)/n; 
 
    printf("Average Waiting time : %f \n" , avgWT ); 
    printf("Average Turnaround time : %f \n" , avgTWT ); 
 
    return 0; 
} 
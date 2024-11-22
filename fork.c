#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int arr[100];
int n;

void assending_sort(int p, int n) { 
    printf("\t\t\t\tAscending sort Child process\n");
    for (int i = 1; i < n; ++i) { 
        int key = arr[i];
        int j = i - 1; 
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key;  
    } 
    for (int i = 0; i < n; i++) { 
        // sleep(5); orphan
        sleep(1)
        printf("\t\t\t\ti = %d ,p = %d ,PID = %d ,PPID = %d\n",arr[i],p,getpid(),getppid());
    } 
} 

void descending_sort(int p, int n) { 
    // sleep(20) zoombie creation
    wait(NULL) // zoombie prevention
    printf("Descending sort Parent Process\n"); 
    for (int i = 0; i < n; i++) { 
        for (int j = i; j < n; j++) { 
            if (arr[i] < arr[j]) { 
                int t = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = t; 
            } 
        } 
    } 
    for (int i = 0; i < n; i++) { 
        // sleep(1); orphan
        sleep(1);
        printf("i=%d , p=%d , pid=%d , ppid=%d \n", arr[i], p, getpid(), getppid()); 
    } 
} 


int main() { 
    int p = 1000;
    printf("Enter the size of the array?\n"); 
    scanf("%d", &n);
 
    printf("Enter the elements:\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &arr[i]); 
    } 

    printf("\nMy Process ID = %d , Parent ID = %d\n",getpid(),getppid());

    p = fork();
    if(p<0) {
        printf("Error occured !");
    }
    else if (p == 0) { 
        assending_sort(p, n); 
    } else { 
        descending_sort(p, n); 
    } 
}
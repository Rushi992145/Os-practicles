#include <stdio.h> 
 
int queue[100];  // Array to represent the page frame 
int qsize;  // Size of the queue (number of frames) 
 
void Optimal(int psize, int page[]) { 
    int ii = 0, fault = 0, hit = 0; 
 
    for(int i=0;i<psize;i++) {
        int cheak = 0;
        for(int j=0;j<ii;j++) {
            if(page[i]==queue[j]){
                cheak=1;
                break;
            }
        }
        if(cheak==1) {
            hit++;
        }
        else {
            if(ii<qsize) {
                queue[ii]=page[i];
                ii++;
            }
            else{
                // finding optimal element
                int position, lru_ind = -1;
                for(int j=0;j<qsize;j++) {
                    int k;
                    for( k=i;k<psize;k++) {
                        if(page[k]==queue[j]) {
                            if(lru_ind<k) {
                                lru_ind=k;
                                position = j;
                            }
                            break;
                        }
                    } 
                    if(k==psize) {
                        position = j;
                        break;
                    }
                }
                queue[position] = page[i];
            }
            fault++;
        }
        printf("Current Queue: "); 
        for (int j = 0; j < ii && j < qsize; j++) { 
            printf("%d ", queue[j]); 
        } 
        printf("\n"); 

    }
      
 
    printf("Total Page Faults: %d\n", fault); 
    printf("Total Page Hits: %d\n", hit); 
    float aph = (float)hit/psize , apf = (float)fault/psize; 
     
    printf("Average Page Faults: %.2f\n", apf); 
    printf("Average Page Hits: %.2f\n", aph); 
} 
 
int main() { 
    int psize; 
    printf("Enter number of pages: "); 
    scanf("%d", &psize); 
    int page[psize]; 
     
    printf("Enter page references: "); 
    for (int i = 0; i < psize; i++) { 
        scanf("%d", &page[i]); 
    } 
 
    printf("Enter the size of queue: "); 
    scanf("%d", &qsize); 
    Optimal(psize, page); 
    return 0;  
}
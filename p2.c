#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main()
{
    char s[300],send[300];
    int num, fd1,fd2,sig,k=0,i,wordcnt=1,charcnt=0,linecnt=0,vowelCnt=0;
    mknod("pipe1", S_IFIFO | 0666, 0);
    mknod("pipe2", S_IFIFO | 0666, 0);
    printf("fifo 2nd side connected,waiting for other process to connect to the 1st end of fifo pipe...\n");
    fd1 = open("pipe1", O_RDONLY);
    fd2 = open("pipe2", O_WRONLY);
    printf("established connection\n");

    
        if ((num = read(fd1, s, 300)) == -1)
            perror("read");
        else {
            s[num] = '\0';
            printf("read %d bytes: \"%s\"\n", num, s);
            wordcnt=1;
            vowelCnt=0;
            for(i=0;i<num;i++)
            {
            	if(s[i]=='a' ||s[i]=='e' ||s[i]=='i' ||s[i]=='o' ||s[i]=='u' || s[i]=='A' || s[i]=='E' || s[i]=='I' || s[i]=='O' || s[i]=='U'){
		    	vowelCnt++;
            	}
            	if((s[i]==' '&&s[i+1]!=' ') || (s[i]=='.' && s[i+1]!='\0'))
            	{
            		wordcnt++;
            	}
            	if(s[i]=='.' || (s[i]!='.' && s[i+1]=='\0'))
            	linecnt++;
            	else if(s[i]!='.'&&s[i]!=' ')
            	charcnt++;
            }

sprintf(send,"for the given sentence the word count is %d\n volwel cnt is%d \n charachter count is%d \n lines are%d\n",wordcnt,vowelCnt,charcnt,linecnt);            
            
           // strcat(send,vowel); 
            if((sig=write(fd2,send,strlen(send)))!=-1)
            printf("\nwriten successfully to file 2");
            else
            printf("\nerror in writing to file2");
        }
  

    return 0;
}
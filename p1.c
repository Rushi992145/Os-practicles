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
    char s1[300],s2[300];
    int num, fd1,fd2,byt;
	//printf("producer");	
    mknod("pipe1", S_IFIFO | 0666, 0);
    mknod("pipe2", S_IFIFO | 0666, 0);
    printf("fifo 1st side connected,waiting for other process to connect to the 2nd end of fifo pipe...\n");
    fd1 = open("pipe1", O_WRONLY);
    fd2 = open("pipe2", O_RDONLY);
    printf("established connection--type some stuff\n");
    gets(s1);	
 	if ((num = write(fd1, s1, strlen(s1))) == -1)
        perror("write");
    else
    {
        printf("wrote %d bytes to file1\n", num);
       
        byt=read(fd2, s2, 300);
        s2[byt]='\0';
        printf(" %s\n",s2);
        
	}
    
    return 0;
}
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int main(void) 
{
	int pipefd1[2],pipefd2[2];
	int pid;
	int ar[15],buffer[15];
	int n=10,t1=0,t2=1;
	int limit;
	int next=t1+t2;
	pipe(pipefd1);
	pipe(pipefd2);
	pid = fork();
	if(pid == 0 ) 
	{
		clock_t ct = clock();
		fflush(stdin);
		printf("unamed_pipe [INFO] Child Process\n");
		write(pipefd1[1],&n,4);
		printf("Fibonacci Series");
		for(int i=0; i <10;i++)
		{
			printf("%d, ",buffer[i]) ;
		}
		read(pipefd2[0],buffer,sizeof(buffer));
		ct = clock() - ct;
        	float time_taken = (float)ct / CLOCKS_PER_SEC;
      	       printf("\nChild process time: %f\n", time_taken);    
	}
	else if(pid > 0)
	{
		sleep(5);
		clock_t pt = clock();
		fflush(stdin);
		printf("unamed_pipe [INFO] Parent Process\n");
		read(pipefd1[0],&limit,4);
		ar[0]=0;
		ar[1]=1;
		for (int i = 2; i < n; i++) 
		{
      		  //printf("%d, ", nextTerm);
       	  t1 = t2;
       	  t2 = next;
        	  next= t1 + t2;
        	  ar[i]=next;
     		}
		write(pipefd2[1],ar, sizeof(ar));
		printf("\n");	
               float time_taken = (float)pt / CLOCKS_PER_SEC;
		pt = clock() - pt;
               printf("\nParent process time: %f\n", time_taken);
	}
	else {
		printf("unamed_pipe [ERROR] Error in creating child process\n");	
	}
	if(pid > 0) {wait(0);}
	return 0;
}
	

# include <stdlib.h>
# include <stdio.h>
#include<sys/ipc.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include<time.h>

int main()
{
    clock_t ct = clock();
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    int *ar = (int*) shmat(shmid,(void*)0,0);
    int n = 8; //fibonacci sequence till 10
    int buffer[8];
    ar[0]=8;
    ar[1]=6;
    ar[2]=5;
    ar[3]=0;
    ar[4]=3;
    ar[5]=1;
    ar[6]=2;
    ar[7]=4;
    
     for (int c=0 ;c<n-1;c++)
  	{
    	  for (int d=0;d<n-c-1;d++)
    	   {
             if (ar[d] > ar[d+1]) /* For decreasing order use '<' instead of '>' */
              {
        	int swap = ar[d];
        	ar[d]   = ar[d+1];
        	ar[d+1] = swap;
      	       }
            }
         }
    printf("Data written in memory!\n");
    ct = clock() - ct;
    float time_taken = (float)ct / CLOCKS_PER_SEC;
    printf("\nChild process time: %f\n", time_taken);
    shmdt(ar);
    return 0;
} 

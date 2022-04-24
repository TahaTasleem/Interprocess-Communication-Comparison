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
   
    int  n=10, t1 = 0, t2 = 1;
    ar[0]=0;
    ar[1]=1;
    for (int i = 2; i <10; i++) 
    {
    	int nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
        ar[i]=nextTerm;
    }
    printf("Data written in memory!\n");
        ct = clock() - ct;
        float time_taken = (float)ct / CLOCKS_PER_SEC;
        printf("\nChild process time: %f\n", time_taken);
    shmdt(ar);
    
    return 0;
} 


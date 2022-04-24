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
    int mtx1[2][2] ;
    int mtx2[2][2] ;
    int row1 = 2, row2 = 2, col1 = 2, col2 = 2;
    mtx1[0][0]=1;mtx1[0][1]=2;
    mtx1[1][0]=3;mtx1[1][1]=4;

    mtx2[0][0]=2;mtx2[0][1]=0;
    mtx2[1][0]=1;mtx2[1][1]=2;
    for(int i = 0; i < row1; i++)
    {
        for(int j = 0; j < col1; j++, ar += sizeof(int))
        {
            *ar = 0;
            for (int k = 0; k < col1; k++)
             {
               *ar += (mtx1[i][k] * mtx2[k][j]);
      
              }printf("%d ",*ar);
        }
    }
     
    printf("Data written in memory!\n");
    ct = clock() - ct;
    float time_taken = (float)ct / CLOCKS_PER_SEC;
    printf("\nChild process time: %f\n", time_taken);
    shmdt(ar);
    return 0;
} 

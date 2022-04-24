#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
 #include <time.h>
int main()
{
    clock_t pt = clock();
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    int *ar = (int*) shmat(shmid,(void*)0,0);
    printf("Data after Sorting Is: ");
    for(int i=0;i<8;i++)
    {
    printf("%d, ",ar[i]);
    }
    pt = clock() - pt;
    float time_taken = (float)pt / CLOCKS_PER_SEC;
    printf("\nParent process time: %f\n", time_taken);
    shmdt(ar);
    shmctl(shmid,IPC_RMID,NULL);    
    return 0;
}

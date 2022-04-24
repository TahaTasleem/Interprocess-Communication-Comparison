#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>

void main()
{
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int pid = fork();
if(!pid)
{
        clock_t ct = clock();
        int mtx1[2][2] ;
        int mtx2[2][2] ;

        mtx1[0][0]=1;mtx1[0][1]=2;
        mtx1[1][0]=3;mtx1[1][1]=4;

        mtx2[0][0]=2;mtx2[0][1]=0;
        mtx2[1][0]=1;mtx2[1][1]=2;
        
        write(fd1[1], mtx1, sizeof(int) *2 *2);
        write(fd2[1], mtx2, sizeof(int) *2 *2);

        sleep(1);
        
        int result[2][2];
        read(fd1[0], result, sizeof(int) *2 *2);
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
        ct = clock() - ct;
        double time_taken = (double)ct / CLOCKS_PER_SEC;
        printf("\nChild process time: %f\n", time_taken);
}
else
{
        clock_t pt = clock();
        int matrix1[2][2], matrix2[2][2];
        read(fd1[0], matrix1, sizeof(int) *2 *2);
        read(fd2[0], matrix2, sizeof(int) *2 *2);

        int result2[2][2] = {0};
        printf("\nMultiplying Matrix\n");
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 2; k++){
                    result2[i][j] += (matrix1[i][k] * matrix2[k][j]);
                }
            }
        }
        write(fd1[1],result2,sizeof(result2));
        wait(NULL);
        pt = clock() - pt;
        double time_taken = (double)pt / CLOCKS_PER_SEC;
        printf("\nParent process time: %f\n", time_taken);
}
    return;
}
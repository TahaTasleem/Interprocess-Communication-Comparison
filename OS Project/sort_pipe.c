#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
void main()
{
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int n = 8; 
    int limit, ar[8]={5,6,3,8,2,1,0,4},buffer[8];
    int pid= fork();
    if(!pid){
        clock_t ct = clock();
        write(fd1[1], &n, 8);
        read(fd2[0], buffer, sizeof(buffer));
        printf("\nSorted list of %d numbers are:", n);
        for(int i = 0; i < n; i++)
            printf("%d ", buffer[i]);
        ct = clock() - ct;
        float time_taken = (float)ct / CLOCKS_PER_SEC;
        printf("\nChild process time: %f", time_taken);
    }
    else{
       sleep(5);
        clock_t pt = clock();
        read(fd1[0],&limit,8);
        printf("\nParent doing sorting...");
        for (int c = 0 ; c < n - 1; c++)
  	{
    	  for (int d = 0 ; d < n - c - 1; d++)
    	   {
             if (ar[d] > ar[d+1]) /* For decreasing order use '<' instead of '>' */
              {
        	int swap    = ar[d];
        	ar[d]   = ar[d+1];
        	ar[d+1] = swap;
      	       }
            }
         }
        write(fd2[1],ar,sizeof(ar));
        pt = clock() - pt;
        float time_taken = (float)pt / CLOCKS_PER_SEC;
        printf("\nParent process time: %f\n", time_taken);
    }
    printf("\n");
}   

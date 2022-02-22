/******************************************************************************
* FILE: omp_mm.c
* DESCRIPTION:  
*   OpenMp Example - Matrix Multiply - C Version
*   Demonstrates a matrix multiply using OpenMP. Threads share row iterations
*   according to a predefined chunk size.
* AUTHOR: Blaise Barney
* LAST REVISED: 06/28/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define multiplier 16
#define NRA 62 * multiplier                /* number of rows in matrix A */
#define NCA 15 * multiplier               /* number of columns in matrix A */
#define NCB 7 * multiplier                 /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB];           /* result matrix C */

chunk = 10;                    /* set loop iteration chunk size */

/*** Spawn a parallel region explicitly scoping all variables ***/
int t;
sscanf(argv[1], "%d", &t);
omp_set_num_threads(t);
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();// @ what thread 
  if (tid == 0)
    {
    nthreads = omp_get_num_threads(); // total number of threads
    //printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Multiplier = %d\n", multiplier);
    //printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  //#pragma omp for schedule (static, chunk) 
  #pragma omp for schedule (dynamic, chunk) 
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  //#pragma omp for schedule (static, chunk)
  #pragma omp for schedule (dynamic, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  //#pragma omp for schedule (static, chunk)
  #pragma omp for schedule (dynamic, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  //printf("Thread %d starting matrix multiply...\n",tid);
  //#pragma omp for schedule (static, chunk)
  #pragma omp for schedule (dynamic, chunk)

  for (i=0; i<NRA; i++)    
    {
    //printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<NCB; j++)       
    {
      //for (k=0; k<NCA; k++)
      int j;
      j = 0;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 1;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 2;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 3;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 4;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 5;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 6;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 7;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 8;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 9;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 10;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 11;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 12;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 13;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];
      j = 14;
      c[i][j] += a[i][0] * b[0][j];
      c[i][j] += a[i][1] * b[1][j];
      c[i][j] += a[i][2] * b[2][j];
      c[i][j] += a[i][3] * b[3][j];
      c[i][j] += a[i][4] * b[4][j];
      c[i][j] += a[i][5] * b[5][j];
      c[i][j] += a[i][6] * b[6][j];

    }
   }
  }   // End of parallel region
 
  /*
  for(j=0; j<NCB; j++)       
    {
    for (i=0; i<NRA; i++)    
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   // End of parallel region
  */

/*** Print results ***/
/*
printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }
printf("******************************************************\n");
printf ("Done.\n");

*/
    printf("cost time = %lfs\n", (double)clock() / CLOCKS_PER_SEC);
}

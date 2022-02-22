#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define multiplier 16
#define NRA 62 * multiplier                /* number of rows in matrix A */
#define NCA 15 * multiplier               /* number of columns in matrix A */
#define NCB 7 * multiplier                 /* number of columns in matrix B */



int main (int argc, char *argv[]){

	double	a[NRA][NCA];           /* matrix A to be multiplied */
	double  final_c[NRA][NCB];
	int my_rank, comm_sz, local_n;
	// generate a
	for (int i=0; i<NRA; i++)
    	for (int j=0; j<NCA; j++)
      		a[i][j]= i+j;
    // parallize
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	int local_col_sz = (NCB + comm_sz - 1) / comm_sz;
	if(my_rank == comm_sz - 1)
		local_n = NCB - my_rank * local_col_sz;
	else
		local_n = local_col_sz;

	//printf("local_n = %d, rank = %d\n", local_n, my_rank);

	// generate B
	//generate fake b to simulate 
	double *fb = NULL;

	double *b = NULL;
	if (local_n > 0)
		b = (double *)malloc(sizeof(double) * NCA * local_n);
	for (int i =0; i<NCA; i++)
    	for (int j=0; j<local_n; j++)
	{
      		b[i + j*NCA]= i * (my_rank * local_col_sz + j);

	}
	fb = (double *)malloc(sizeof(double) * NCA * NCB);
	if(my_rank == 0)
	{
		for(int i = 0; i < NCA; i++)
			for(int j = 0; j < NCB; j++)
				fb[i + j*NCA] = i * j;
	}
	MPI_Bcast(fb, NCA * NCB, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double *c = (double *)malloc(sizeof(double) * NRA * local_col_sz);
    for(int i = 0; i < NRA * local_col_sz; i++)
    	c[i] = 0;
    for (int i=0; i<NRA; i++)    
    {
    	for(int j=0; j<local_n; j++)       
    		for (int k=0; k<NCA; k++)
        		c[i + j*NRA] += a[i][k] * b[k + j*NCA];
    }
    double *gather_c = NULL;
    if(my_rank == 0)
    	gather_c = (double *)malloc(NRA * local_col_sz * comm_sz * sizeof(double));
    int count = NRA * local_col_sz;
    MPI_Gather(c, count, MPI_DOUBLE, gather_c, count, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(my_rank == 0)
    {
    	for(int i = 0; i < NRA; i++)
    		for(int j = 0; j < NCB; j++)
    			final_c[i][j] = gather_c[i + j*NRA];
	//printf("multiplier = %d\n", multiplier);
    }
	MPI_Finalize();
	return 0;
	
}

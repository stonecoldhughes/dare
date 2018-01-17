/* 
    Never run more than 1 iteration! Doing so will cause a Cholesky
    factorization to be attempted on a matrix that is very likely not to
    be positive definite!
*/
#include "plasma.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/mman.h"
#include "fcntl.h"

#define ELEMENT_MAX 256
#define BOTTOM_ROW_MAX 10
#define PRINT 0

void print_matrix(double *matrix, int n)
{
    if(PRINT)
    {
        int i;
        int j;

        printf("matrix:\n");

        for(i = 0; i < n; ++i)
        {
            for(j = 0; j < n; ++j)
            {
                printf(" %4lf", matrix[ i * n + j ]);
            }

            printf("\n");
        }

        printf("\n");
    }
    
    return;
}

void gen_symmetric_2(double *matrix, int n)
{
    int i;
    int j;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            if(i < j)
            {
                double val = (double)((rand() % ELEMENT_MAX) + 1) / ELEMENT_MAX;  

                matrix[ i * n + j ] = val;
            }

            else if(i == j)
            {
                double val = (double)(rand() % ELEMENT_MAX + 1) + n;

                matrix[i * n + j ] = val;
            }

            else matrix[i * n + j] = matrix[j * n + i];
        }
    }

    return;
}

int dim_rand(int m_low, int m_add)
{
    return m_low + ((rand() % m_add) + 1);
}

int main (int argc, char *argv[]) 
{
  int i;
  int n;
  int nb;
  int seed;
  double *a;
  int n_low;
  int n_add;
  int n_total;
  int len_bytes;
  int iterations;

  /* Command line arguments should be m_low, m_high, n_low, n_high, iterations */ 
  if(argc < 6) 
  {
    printf(
            "wrong number of arguments.\n"
            "Expected n_low, n_add, iter, seed, tile_size\n"
            "set seed to -1 to use time(NULL) for seed value\n"
            "set tile_size to -1 to use default\n"
          );
    
    exit(0);
  }

  n_low = atoi(argv[1]);
  n_add = atoi(argv[2]);
  iterations = atoi(argv[3]);

  /* Initialize the random number generator */
  seed = atoi(argv[4]);
  if(seed != -1) srand(seed);
  else srand(time(NULL));

  plasma_init();

  /* Set PlasmaNb */
  nb = atoi(argv[5]);
  if(nb != -1) plasma_set(PlasmaNb, nb);
  
  n_total = n_low + n_add;

  /* allocate enough space to accomodate the largest possible matrix */
  len_bytes = n_total * n_total * sizeof(double);

  /* Main testing loop */
  for(i = 0; i < iterations; ++i)
  {
    a = (double *)malloc(len_bytes);
    
    gen_symmetric_2(a, n_total);

    /* randomize the access pattern a little */
    if(n_add != 0) n = dim_rand(n_low, n_add);
    
    else n = n_total;
    
    if(PRINT) printf("running with n = %d\n", n);

    /* Decompose the square Hermitian with a Cholesky factorization */
    int r = plasma_dpotrf
    (
         PlasmaUpper
         ,n
         ,a
         ,n_total
    );
  
    free(a);

    if(PRINT) printf("iteration %d return val: %d\n", i, r);
    else if(r != 0) printf("iteration %d failed with return val: %d\n",
                           i, r);
  }


  plasma_finalize();

  return 0;
}

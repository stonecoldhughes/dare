#include "plasma.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/mman.h"
#include "fcntl.h"

#define ELEMENT_MAX 256
#define PRINT 1


void gen_hermitian(double *matrix, int n)
{
    int i;
    int j;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            if(i <= j)
            {
                double val = (double)((rand() % ELEMENT_MAX) + 1);  

                matrix[ i * n + j ] = val;
            }

            else matrix[i * n + j] = matrix[j * n + i];
        }
    }

    return;
}

void print_matrix(double *matrix, int n)
{
    int i;
    int j;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            printf(" %3.lf", matrix[ i * n + j ]);
        }

        printf("\n");
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
  int seed;
  double *a;
  int n_low;
  int n_add;
  int n_total;
  int len_bytes;
  int iterations;

  /* Command line arguments should be m_low, m_high, n_low, n_high, iterations */ 
  if(argc < 5) 
  {
    printf(
            "wrong number of arguments.\n"
            "Expected n_low, n_add, iter, seed\n"
            "set seed to -1 to use time(NULL) for seed value\n"
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

  n_total = n_low + n_add;

  /* allocate enough space to accomodate the largest possible matrix */
  len_bytes = n_total * n_total * sizeof(double);

  a = (double *)malloc(len_bytes);

  gen_hermitian(a, n_total);

  /*
  printf("hermitian matrix to factor:\n");
  print_matrix(a, n_total);
  printf("\n");
  */
  
  plasma_init();

  /* Main testing loop */
  for(i = 0; i < iterations; ++i)
  {
    if(n_add != 0) n = dim_rand(n_low, n_add);
    
    else n = n_total;
    
    if(PRINT)
    {
        printf("running with n = %d\n", n);
    }

    /* Decompose the square Hermitian with a Cholesky factorization */
    int r = plasma_dpotrf
    (
         PlasmaUpper
         ,n
         ,a
         ,n_total
    );
  }


  plasma_finalize();

  free(a);

  return 0;
}

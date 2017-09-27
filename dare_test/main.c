#include "plasma.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/mman.h"
#include "fcntl.h"

#define ELEMENT_MAX 256
#define PRINT 1

/* 
randomly generates an m by n matrix of elements between
1 and ELEMENT_MAX
*/
void gen(double *matrix, int m, int n)
{
    int i;
    int j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[ j * n + i ] = (double)((rand() % ELEMENT_MAX) + 1);
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
  int m;
  int n;
  int seed;
  double *a;
  double *c;
  int m_low;
  int m_add;
  int n_low;
  int n_add;
  int m_total;
  int n_total;
  int len_bytes;
  int iterations;

  /* Command line arguments should be m_low, m_high, n_low, n_high, iterations */ 
  if(argc < 7) 
  {
    printf(
            "wrong number of arguments.\n"
            "Expected m_low, m_add, n_low, n_add, iter, seed\n"
            "set seed to -1 to use time(NULL) for seed value\n"
          );
    
    exit(0);
  }

  m_low = atoi(argv[1]);
  m_add = atoi(argv[2]);
  n_low = atoi(argv[3]);
  n_add = atoi(argv[4]);
  iterations = atoi(argv[5]);

  /* Initialize the random number generator */
  seed = atoi(argv[6]);
  if(seed != -1) srand(seed);
  else srand(time(NULL));

  m_total = m_low + m_add;

  n_total = n_low + n_add;

  /* allocate enough space to accomodate the largest possible matrix */
  len_bytes = m_total * n_total * sizeof(double);

  a = (double *)malloc(len_bytes);
  gen(a, m_total, n_total);
  
  /* create a new buffer for the result  */
  c = (double *)malloc(len_bytes);
  
  plasma_init();

  /* Main testing loop */
  for(i = 0; i < iterations; ++i)
  {
    if(m_add != 0)
    {
        m = dim_rand(m_low, m_add);

        n = dim_rand(n_low, n_add);
    }

    else
    {
        m = m_total;

        n = n_total;
    }

    if(PRINT)
    {
        printf("running with m = %d, n = %d\n", m, n);
    }

    /* Multiply "a" by its transpose to create square Hermitian */
    plasma_dgemm
        (
         PlasmaNoTrans 
         ,PlasmaTrans
         ,m
         ,n
         ,n
         ,1.0
         ,a 
         ,m_total
         ,a
         ,n_total
         ,0.0
         ,c
         ,m_total
        );

    /* Decompose the square Hermitian with a Cholesky factorization */
    int r = plasma_dpotrf
    (
         PlasmaUpper
         ,m
         ,c
         ,m_total
    );
  }


  plasma_finalize();

  free(a);
  free(c);

  return 0;
}

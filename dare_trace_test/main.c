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

double row_prod(double *m, int r, int c, int n)
{
    double prod = 0;
    int i;
    int r_offset = r * n;
    int c_offset = c * n;
    int min = c < r ? c : r;

    for(i = 0; i <= min; ++i)
    {
        prod += (m[r_offset + i] * m[c_offset + i]);
    }

    return prod;
}

/* generate a Hermitian, positive-definite matrix to Cholesky factorize */
void gen_hermitian(double *matrix, int n)
{
    double *tmp = malloc(n * n * sizeof(double)); 
    int i;
    int j;
    
    /* create a lower triangular matrix in tmp */
    for(i = 0; i < n; ++i)
    {
        /* 
        Maximum value for row i. This formula keeps the matrix values
        somewhat well conditioned
        */
        int max_value = n / (i + 1) * BOTTOM_ROW_MAX;
        int row_offset = i * n;

        for(j = 0; j <= i; ++j)
        {
            tmp[ row_offset + j ] = (double)(rand() % max_value + 1);
        }
    }

    /* Multiply the matrix by its transpose and store in "matrix" */
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
           matrix[ i * n + j ] = row_prod(tmp, i, j, n); 
        }
    }
    
    /* test */
    print_matrix(tmp, n);

    print_matrix(matrix, n);
    
    free(tmp);

    return;
}

void gen_symmetric(double *matrix, int n)
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

void gen_identity(double *matrix, int n)
{
    int i;
    int j;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            if(i == j)
            {
                matrix[ i * n + j ] = 0;
            }

            else
            {
                matrix[ i * n + j ] = 1.0;
            }
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
            "Expected n_low, n_add, iter, seed, nb\n"
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

  /* Get nb, but it can't be set until after plasma_init() */
  nb = atoi(argv[5]);

  printf("nb from command line: %d\n", nb);

  n_total = n_low + n_add;

  /* allocate enough space to accomodate the largest possible matrix */
  len_bytes = n_total * n_total * sizeof(double);

  a = (double *)malloc(len_bytes);

  gen_symmetric_2(a, n_total);

  //gen_identity(a, n_total);

  plasma_init();
  
  plasma_set(PlasmaNb, nb);

  /* Main testing loop */
  for(i = 0; i < iterations; ++i)
  {
    if(n_add != 0) n = dim_rand(n_low, n_add);
    
    else n = n_total;
    
    printf("running with n = %d\n", n);

    /* Decompose the square Hermitian with a Cholesky factorization */
    int r = plasma_dpotrf
    (
         PlasmaUpper
         ,n
         ,a
         ,n_total
    );

    printf("return val: %d\n", r);
  }


  plasma_finalize();

  /* Final result */
  print_matrix(a, n);

  printf("freeing \"a\"\n");
  free(a);
  printf("freed \"a\"\n");

  return 0;
}

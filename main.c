#include "plasma.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/mman.h"
#include "fcntl.h"

void gen(double *matrix, int n)
{
    int i;
    int j;

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[j*n+i] = (double)((rand()%256)+1);
        }
    }

    return;
}

int main (int argc, char *argv[]) 
{
  int tid;
  int n;
  double *a;
  double *b;
  double *c;
  double one = 1.0;
  double zero = 0.0;
  plasma_enum_t p = PlasmaNoTrans;
  int len_bytes;

  printf("enter n: ");
  scanf("%d", &n);
  len_bytes = n*n*sizeof(double);

  /* create a new buffer for the result  */
  a = (double *)malloc(len_bytes);
  gen(a, n);
  
  b = (double *)malloc(len_bytes);
  gen(b, n);
  
  c = (double *)malloc(len_bytes);
  gen(c, n);
  
  plasma_init();

  /*Multiply two triangular matrices*/
  plasma_dgemm
  (
   p 
  ,p
  ,n
  ,n
  ,n
  ,one
  ,a 
  ,n
  ,b
  ,n
  ,zero
  ,c
  ,n
  );
  
  /*Decompose the product with a Cholesky factorization*/
  plasma_dpotrf
  (
   PlasmaUpper
  ,n
  ,c
  ,n
  );

  plasma_finalize();

  /* write the contents of the multiplication to a file  */
  free(a);
  free(b);
  free(c);

  return 0;
}

#include <cstdio>

#include "omp.h"
#include "core_blas.h"

#define ELEMENT_MAX 256

using namespace std;

void print_matrix(double *matrix, int n)
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
    
    return;
}

void gen_symmetric_2(double *matrix, int n, int stride)
{
    int i;
    int j;

    for(i = 0; i < stride; ++i)
    {
        for(j = 0; j < stride; ++j)
        {
            if((i < n) && (j < n))
            {
                double val = -1;

                if(i < j)
                {
                    val = (double)((rand() % ELEMENT_MAX) + 1) / ELEMENT_MAX;  

                    matrix[ i * stride + j ] = val;
                }

                else if(i == j)
                {
                    val = (double)(rand() % ELEMENT_MAX + 1) + n;

                    matrix[i * stride + j ] = val;
                }

                else
                {
                    val = matrix[j * stride + i];

                    matrix[i * stride + j] = val;
                }
            }

            else
            {
                matrix[i * stride + j] = 0;
            }
        }
    }

    return;
}

void run(int n, double *matrix, int stride)
{
    double t1 = omp_get_wtime();

    int ret_val = core_dpotrf(
            PlasmaLower,
            n,
            matrix,
            stride
            );

    double t2 = omp_get_wtime();

    double elapsed = t2 - t1;

    printf("ret_val: %d n: %d stride: %d time: %lf\n",
            ret_val, n, stride, elapsed);

    return;
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Wrong number of arguments. Expected: <n> <stride>\n");

        exit(0);
    }

    int n = atoi(argv[1]);

    int stride = atoi(argv[2]);

    int len_bytes = stride * stride * sizeof(double);

    double *matrix = new double[len_bytes];

    /* generate the matrix */
    gen_symmetric_2(matrix, n, stride);

    //print_matrix(matrix, stride);

    printf("with stride:\n");

    run(n, matrix, stride);

    delete[] matrix;

    len_bytes = n * n * sizeof(double);

    matrix = new double[len_bytes];

    gen_symmetric_2(matrix, n, n);

    printf("without stride:\n");

    run(n, matrix, n);

    return 0;
}

#include <cstring>
#include <cstdlib>
#include "fake_data.h"

#define ELEMENT_MAX 256
#define CLIP_SIZE 100

using namespace std;

fake_dpotrf_data::fake_dpotrf_data(int tile_size)
    :
    clip_size(CLIP_SIZE),
    clip_index(0),
    tile_size(tile_size),
    reload_time(0)
{
    
    srand(time(NULL));

    reference_matrix = gen_matrix(tile_size);

    matrix_clip = new double*[clip_size];

    for(int i = 0; i < clip_size; ++i)
    {
       matrix_clip[i] = new double[tile_size * tile_size]; 
    }

    //printf("constructor before reload:\n");
    //print_matrix_clip();
    reload();
    //printf("constructor after reload:\n");
    //print_matrix_clip();

    return;
}

fake_dpotrf_data::~fake_dpotrf_data()
{
     
    for(int i = 0; i < clip_size; ++i)
    {
        delete[] matrix_clip[i];
    }
    
    delete[] matrix_clip;

    delete[] reference_matrix;
    
    return;
}

double *fake_dpotrf_data::tile()
{
    if(clip_index == clip_size) return NULL;

    return matrix_clip[clip_index++];
}

void fake_dpotrf_data::print_matrix_clip()
{
    for(int i = 0; i < clip_size; ++i)
    {
        printf("matrix %d:\n", i);
        
        for(int j = 0; j < tile_size; ++j)
        {
            printf("\n");

            for(int k = 0; k < tile_size; ++k)
            {
                printf(" %3.lf", matrix_clip[i][ j * tile_size + k]);
            }
        }
        printf("\n");
    }

    return;
}

/* 
Once each matrix in the matrix clip has been Cholesky decomposed
in-place or empty, reload the clip with copies of it.
*/
void fake_dpotrf_data::reload()
{
    double t1 = omp_get_wtime();

    clip_index = 0;

    for(int i = 0; i < clip_size; ++i)
    {
        memcpy(
              matrix_clip[i],
              reference_matrix,
              tile_size * tile_size * sizeof(double)
              );
    }

    double t2 = omp_get_wtime();

    reload_time = t2 - t1;

    return;
}

double fake_dpotrf_data::get_reload_time()
{
    return reload_time;
}

double *fake_dpotrf_data::gen_matrix(int n)
{
    double *matrix = new double[ n * n ];

    /* matrix is in row major order */
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
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

    return matrix;
}

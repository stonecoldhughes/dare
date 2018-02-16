#include <cstring>
#include <cstdlib>
#include "fake_data.h"

#include <thread>
#include <chrono>

#define ELEMENT_MAX 256

using namespace std;

/* Base class fake_data object methods */
fake_data::fake_data()
{
    return;
}

fake_data::fake_data(int _clip_size, int _tile_size, int _winsize)
    :
    clip_size(_clip_size),
    clip_index(0),
    tile_size(_tile_size),
    t_index(-1),
    start(1),
    max_window_size(_winsize),
    window_size(0)
{
    srand(time(NULL));

    clip_times = new double[clip_size];
    
    return;
}

fake_data::~fake_data()
{
    delete[] clip_times;

    return;
}

int fake_data::get_max_window_size()
{
    return max_window_size;
}

int fake_data::get_tile_size()
{
    return tile_size;
}

int fake_data::get_clip_size()
{
    return clip_size;
}

int fake_data::clip_empty()
{
    return (clip_index == clip_size);
}

int fake_data::tile_times_empty()
{
    return (clip_index < 2);
}

double fake_data::tile_time()
{
    if(++t_index == window_size) t_index = 0;

    return clip_times[t_index + start];
}

void fake_data::busy_wait(double t)
{
    double end = omp_get_wtime() + t;
    
    while(omp_get_wtime() < end);

    return;
}

/* This function is meant to be called after tile() */
void fake_data::append_time(double t)
{
    /* Subtract 1 to get the index of the round that was just expended */
    int i = clip_index - 1;

    clip_times[i] = t;

    if(i <= max_window_size)
    {
        window_size = i;
    }

    else start++;

    return;
}

/* Concrete class fake_dpotrf_data object methods */

fake_dpotrf_data::fake_dpotrf_data(int _clip_size,
                                   int _tile_size,
                                   int _winsize,
                                   void *core_dpotrf_ptr)
    :
    fake_data(_clip_size, _tile_size, _winsize)
{
    matrix_clip = new double*[clip_size];

    for(int i = 0; i < clip_size; ++i)
    {
       matrix_clip[i] = new double[tile_size * tile_size]; 
    }

    load_matrix_clip();

    /* Obtain all tile times before any data dependent functions are
       invoked. This was an attempt to eliminate cache effects*/
    //waste_clip(core_dpotrf_ptr, 2);

    return;
}

/* Captain! Exhaust the clip preemptively to get accurate busy-wait times */
void fake_dpotrf_data::waste_clip(void *core_dpotrf_ptr, int waste_fraction)
{
    int half = get_clip_size() / waste_fraction;

    for(int i = 0; i < half; ++i)
    {
        double *ptr = tile();

        int size = get_tile_size();

        double t = omp_get_wtime();

        ((core_dpotrf_hook_type)core_dpotrf_ptr)(
                   PlasmaUpper,
                   size,
                   ptr,
                   size
                   );

        double elapsed = omp_get_wtime() - t;

        append_time(elapsed);
    }

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

/* Tile should not be called if clip_empty() returns true */
/* This check should always be performed */
double *fake_dpotrf_data::tile()
{
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
void fake_dpotrf_data::load_matrix_clip()
{
    reference_matrix = gen_matrix(tile_size);

    for(int i = 0; i < clip_size; ++i)
    {
        memcpy(
              matrix_clip[i],
              reference_matrix,
              tile_size * tile_size * sizeof(double)
              );
    }

    return;
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

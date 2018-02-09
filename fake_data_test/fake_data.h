#include <string>
#include "core_blas.h"
#include "omp.h"
#ifndef AUTOGEN_TYPES_H
#define AUTOGEN_TYPES_H
#include "autogen_types.h"
#endif

using namespace std;

/* Base class */

class fake_data
{
    public:
        
        fake_data();

        fake_data(int clip_size, int tile_size, int winsize);

        ~fake_data();
        
        int clip_empty();
        
        int tile_times_empty();

        double tile_time();
        
        void busy_wait(double t);
        
        void append_time(double t);

        int get_max_window_size();

        int get_clip_size();

        int get_tile_size();

        double init_time;

        int init_thread;
    
    protected:
        
        int clip_size;

        int tile_size;

        /* moving window of tile times out of clip_times to round robin from */
        int window_size;

        int max_window_size;

        /* state-dependent variables */
        int clip_index;
        
        int start;
        
        /* an array of the times it takes to factor each matrix */
        double *clip_times;
        
        int t_index;
};

/* Concrete object */
class fake_dpotrf_data : public fake_data
{
    public:

        fake_dpotrf_data(int clip_size,
                         int tile_size,
                         int winsize,
                         void *core_dpotrf_ptr);

        ~fake_dpotrf_data();

        /* Contains copies of the reference matrix to be factored */
        double **matrix_clip;

        /* Contains the matrix that is copied to make the clip */
        double *reference_matrix;

        /* Which matrix is next to be factored in the clip */
        /* when it reaches clip_size, a reload must occur if you want more
           matrices to factor */

        /* Generates a hermitian positive definite with given dimensions */
        double *gen_matrix(int n);
        
        void load_matrix_clip();

        double *tile();

        void print_matrix_clip();
    
    protected:

        /* Clip data is stored in memory that is likely not in cache.
           Thus, tile times from clip elements used in actual data-dependent
           core_function calls will be slower than actual.*/
        /* Tile times from clip elements used outside of actual core_function
           calls run too fast because the cache system is not handling large
           amounts of matrix data in addition to these tiles.*/
        /* The natural solution is to run a fraction too quickly and a fraction
            too slowly, then the average time could be more accurate */
        void waste_clip(void *core_dpotrf_ptr, int waste_fraction);
};

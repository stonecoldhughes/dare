#include <string>
#include "omp.h"

using namespace std;

/* Captain! Make this class an interface so hooks.cpp can easily use it */
/* You also may want to move some of this functionality into the base class */
class fake_dpotrf_data
{
    public:

        fake_dpotrf_data(int tile_size);

        ~fake_dpotrf_data();

        /* Contains copies of the reference matrix to be factored */
        double **matrix_clip;

        double *reference_matrix;

        /* Length of the matrix clip array */
        int clip_size;

        /* Which matrix is next to be factored in the clip */
        /* when it reaches clip_size, a reload must occur if you want more
           matrices to factor */
        int clip_index;

        /* Generates a hermitian positive definite with given dimensions */
        double *gen_matrix(int n);
        
        /* reloads the matrix clip */
        void reload();

        int tile_size;

        /* an array of the times it takes to factor each matrix */
        /* don't know how I'm going to fill this up */
        double *clip_times;

        /* Timing information */
        double reload_time;

        /* Prints clip times and reload time */
        double get_reload_time();

        /*
        returns the next valid matrix from matrix_clip or NULL if it needs
        to be reloaded
        */
        double *tile();

        /* returns whether or not the clip is expended */
        int empty();
        
        void print_matrix_clip();
};








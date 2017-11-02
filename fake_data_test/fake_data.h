#include <string>

#define CLIP_SIZE 50

using namespace std;

class fake_data
{
    public:

        fake_data();
        
        ~fake_data();

        /* virtual function to create m, n matrix. */
        virtual void gen_matrix(int m, int n) = 0;
};

/* Captain! Make this class an interface so hooks.cpp can easily use it */
/* You also may want to move some of this functionality into the base class */
class fake_dpotrf_data : public fake_data
{
    public:

        fake_dpotrf_data();

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

        int lda;

        /* Generates a hermitian positive definite with given dimensions */
        void gen_matrix(int m, int n);
        
        /* reloads the matrix clip */
        void reload();

        /* an array of the times it takes to factor each matrix */
        double *clip_times;

        /* Timing information */
        double reload_time;

        /* Prints clip times and reload time */
        void print_timing_data();
};








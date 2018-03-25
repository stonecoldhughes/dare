#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "plasma.h"
#include "omp.h"

#define ELEMENT_MAX 256

using namespace std;

/* Class for handling command line options */
class command_args
{
    public:

        command_args(int argc, char **argv, int n_args);
    
        /* which function is being tested */
        string function;

        /* matrix size */
        int m;
        
        int n;

        int iterations;

        /* randomizable addition to each matrix */
        int n_add;

        int m_add;

        /* random number generator seed */
        int seed;

        /* nb parameter for Plasma library */
        int tile_size;

        /* number of expected command line arguments */
        int n_args;     
};

/* Templated base class for generating matrices */
template<class T> class matrix_base
{
    public:
        
        matrix_base(int m, int m_add, int n, int n_add);

        ~matrix_base();

        T *matrix_0;

        int m;

        int m_add;

        int n;

        int n_add;

        int leading_dim;
        
        virtual void print_matrix() = 0;

    protected:
        
        virtual void gen_matrix() = 0;

        /* return a random dimension */
        static int dim_rand(int num, int rand_add);
};

/* Template specialization derived class for testing dpotrf */
class dpotrf_matrix_class : public matrix_base<double>
{
    public:
        
        dpotrf_matrix_class(int m, int m_add, int n, int n_add);

        ~dpotrf_matrix_class();

        void print_matrix();

    protected:
        
        void gen_matrix();
};

/* Template specialization derived class for testing dgeqrf */
class dgeqrf_matrix_class : public matrix_base<double>
{
    public:
        
        /* parts of this will remain */
        dgeqrf_matrix_class(int m, int m_add, int n, int n_add);

        /* keep the delete[] matrix part of this */
        ~dgeqrf_matrix_class();
        
        /* template specialize this */
        void print_matrix();

        /* pass down inheritance chain */
        plasma_desc_t desc_T;

    protected:
        
        /* this will have to be inherited */
        /* generate matrix data */
        void gen_matrix();
};

class dgemm_matrix_class : public matrix_base<double>
{
    public:
        
        dgemm_matrix_class(
                          int m,
                          int m_add,
                          int n,
                          int n_add,
                          int fastest_n,
                          int iterations
                          );

        ~dgemm_matrix_class();

        void run_dgemm_iterations();

        void print_matrix();

        double *matrix_1;

        double *matrix_2;

    protected:
        
        void gen_matrix();
        
        void insert(int tile_size);

        void output_fastest();

        map<double, int> fastest_n_map;

        int fastest_n;

        int iterations;
};

/* All functions to carry out the test */
/* 
This must be put here, after the class command_args is defined
otherwise the compiler thinks command_args is a class defined
somewhere within run_iterations
*/
namespace run_iterations
{
    void run_dgeqrf_iterations(class command_args &cmd_args);

    void run_dpotrf_iterations(class command_args &cmd_args);
    
    void run_dgemm_iterations(class command_args &cmd_args);

    extern int fastest_n;
}

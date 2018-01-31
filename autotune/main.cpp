#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include "plasma.h"

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

command_args::command_args(int argc, char **argv, int n_args)
{
    if(argc != n_args)
    {
        printf("Wrong number of arguments. Got %d, expected %d:\n"
               "./autotune.bin function, m, m_add, "
               "n, n_add, iterations, seed, tile_size\n", argc, n_args);

        exit(0);
    }

    function = argv[1];

    m = stoi(argv[2]);

    m_add = stoi(argv[3]);

    n = stoi(argv[4]);

    n_add = stoi(argv[5]);

    iterations = stoi(argv[6]);

    seed = stoi(argv[7]);

    tile_size = stoi(argv[8]);

    return;
}

/* Templated base class for generating matrices */
template<class T> class matrix_base
{
    public:
        
        matrix_base(int m, int m_add, int n, int n_add);

        ~matrix_base();

        T *matrix;

        int m;

        int m_add;

        int n;

        int n_add;

        int leading_dim;

    private:
        
        virtual void gen_matrix() = 0;

        virtual void print_matrix() = 0;
        
        /* return a random dimension */
        static int dim_rand(int num, int rand_add);
};

template<class T> matrix_base<T>::matrix_base(
                                             int _m,
                                             int _m_add,
                                             int _n,
                                             int _n_add
                                             )
    :
    m(dim_rand(_m, _m_add)),
    m_add(_m_add),
    n(dim_rand(_n, _n_add)),
    n_add(_n_add)
{
    leading_dim = m; 
    
    matrix = new T[m * n * sizeof(T)];

    return;
}

template<class T> matrix_base<T>::~matrix_base()
{
    delete[] matrix;

    return;
}

template<class T> int matrix_base<T>::dim_rand(int number, int rand_add)
{
    if(rand_add == 0) return number;

    else return number + (rand() % ++rand_add);
}

/* Template specialization derived class for testing dpotrf */
class dpotrf_matrix_class : public matrix_base<double>
{
    public:
        
        dpotrf_matrix_class(int m, int m_add, int n, int n_add);

        ~dpotrf_matrix_class();

        void print_matrix();

    private:
        
        void gen_matrix();
};

dpotrf_matrix_class::dpotrf_matrix_class(int _m, int _m_add, int _n, int _n_add)
    :
    matrix_base(_m, _m_add, _n, _n_add)
{
    if(m != n) {printf("dpotrf error: m != n\n"); exit(0);}

    gen_matrix();

    return;
}

dpotrf_matrix_class::~dpotrf_matrix_class()
{
    return;
}

/* creates symmetric, well-conditioned matrix for dpotrf */
void dpotrf_matrix_class::gen_matrix()
{
    for(int i = 0; i < m; ++i)
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

    return;
}

void dpotrf_matrix_class::print_matrix()
{
    printf("m: %d n: %d leading_dim: %d\n", m, n, leading_dim); 

    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            printf(" %-3.lf", matrix[ i * n + j ]);
        }

        printf("\n");
    }
    
    return;
}

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

    private:
        
        /* this will have to be inherited */
        /* generate matrix data */
        void gen_matrix();
};

dgeqrf_matrix_class::dgeqrf_matrix_class(int m, int m_add, int n, int n_add)
    :
    matrix_base(m, m_add, n, n_add)
{
    gen_matrix();

    return;
}

dgeqrf_matrix_class::~dgeqrf_matrix_class()
{
    plasma_desc_destroy(&desc_T);

    return;
}

void dgeqrf_matrix_class::gen_matrix()
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            double val = (double)((rand() % ELEMENT_MAX) + 1);

            matrix[ i * n + j ] = val;
        }
    }
    
    return;
}

void dgeqrf_matrix_class::print_matrix()
{
    printf("m: %d n: %d leading_dim: %d\n", m, n, leading_dim); 

    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            printf(" %-3.lf", matrix[ i * n + j ]);
        }

        printf("\n");
    }

    return;
}

/* All functions to carry out the test */
namespace run_iterations
{
    void run_dgeqrf_iterations(class command_args &cmd_args);

    void run_dpotrf_iterations(class command_args &cmd_args);
}

void run_iterations::run_dpotrf_iterations(class command_args &cmd_args)
{
    plasma_init();

    if(cmd_args.tile_size != -1) plasma_set(PlasmaNb, cmd_args.tile_size);

    for(int i =0; i < cmd_args.iterations; ++i)
    {
        class dpotrf_matrix_class matrix(
                                        cmd_args.m,
                                        cmd_args.m_add,
                                        cmd_args.n,
                                        cmd_args.n_add
                                        );
        
        int ret_val = plasma_dpotrf(
                                   PlasmaUpper,
                                   matrix.m,
                                   matrix.matrix,
                                   matrix.leading_dim
                                   );
        
        if(ret_val != 0)
        {
            printf(
                  "iteration %d failed with return value: %d\n",
                  i, ret_val
                  );

            exit(0);
        }
    }
    
    plasma_finalize();

    return;
}

/* Captain! Make a class for running different kinds of functions too */
void run_iterations::run_dgeqrf_iterations(class command_args &cmd_args)
{
    plasma_init();

    if(cmd_args.tile_size != -1) plasma_set(PlasmaNb, cmd_args.tile_size);

    for(int i = 0; i < cmd_args.iterations; ++i)
    {
        class dgeqrf_matrix_class matrix(
                                        cmd_args.m,
                                        cmd_args.m_add,
                                        cmd_args.n,
                                        cmd_args.n_add
                                        );

        int ret_val = plasma_dgeqrf(
                                   matrix.m,
                                   matrix.n,
                                   matrix.matrix,
                                   matrix.leading_dim,
                                   &matrix.desc_T
                                   );

        if(ret_val != 0) 
        {
            printf(
                  "iteration %d failed with return value: %d\n",
                  i, ret_val
                  );

            exit(0);
        }
    }

    plasma_finalize();

    return;
}

int main(int argc, char **argv)
{
    /* number of expected command line arguments */
    int n_args = 9;

    class command_args cmd_args(argc, argv, n_args);

    /* seed the random number generator */
    if(cmd_args.seed == -1) srand(time(NULL));
    else srand(cmd_args.seed);

    /* run iterations of the function you are testing */
    if(cmd_args.function == "dgeqrf")
    {
        run_iterations::run_dgeqrf_iterations(cmd_args);
    }

    else if(cmd_args.function == "dpotrf")
    {
        run_iterations::run_dpotrf_iterations(cmd_args);
    }

    else
    {
        printf("Unrecognized function. Exiting.");

        exit(0);
    }

    return 0;
}

#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include "plasma.h"

#define ELEMENT_MAX 256

using namespace std;

class command_args
{
    public:

        command_args(int argc, char **argv, int n_args);
    
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
               "./dgeqrf_test.bin m, m_add, "
               "n, n_add, iterations, seed, tile_size\n", argc, n_args);

        exit(0);
    }

    m = stoi(argv[1]);

    m_add = stoi(argv[2]);

    n = stoi(argv[3]);

    n_add = stoi(argv[4]);

    iterations = stoi(argv[5]);

    seed = stoi(argv[6]);

    tile_size = stoi(argv[7]);

    return;
}

template<class T> class matrix_base
{
        

};

class matrix_class
{
    public:
        
        /* parts of this will remain */
        matrix_class(int m, int m_add, int n, int n_add);

        /* keep the delete[] matrix part of this */
        ~matrix_class();
        
        /* template specialize this */
        void print_matrix();

        /* template specialize */
        double *matrix;
        
        int leading_dim;
       
        int m;
        
        int m_add;
        
        int n;
        
        int n_add;

        /* pass down inheritance chain */
        plasma_desc_t desc_T;

    private:
        
        /* this will have to be inherited */
        /* generate matrix data */
        void gen_matrix();

        /* return a random dimension */
        static int dim_rand(int num, int rand_add);
};

matrix_class::matrix_class(int _m, int _m_add, int _n, int _n_add)
    :
    m(dim_rand(_m, _m_add)),
    m_add(_m_add),
    n(dim_rand(_n, _n_add)),
    n_add(_n_add)
{
    leading_dim = m; 
    
    matrix = new double[m * n * sizeof(double)];

    gen_matrix();

    return;
}

matrix_class::~matrix_class()
{
    delete[] matrix;

    plasma_desc_destroy(&desc_T);

    return;
}

void matrix_class::gen_matrix()
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

void matrix_class::print_matrix()
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

int matrix_class::dim_rand(int number, int rand_add)
{
    if(rand_add == 0) return number;

    else return number + (rand() % ++rand_add);
}

void run_iterations(class command_args &cmd_args)
{
    plasma_init();

    if(cmd_args.tile_size != -1) plasma_set(PlasmaNb, cmd_args.tile_size);

    for(int i = 0; i < cmd_args.iterations; ++i)
    {
        class matrix_class matrix(
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

        if(ret_val != 0) printf("iteration %d failed with return value: %d\n",
                                i, ret_val
                               );
    }

    plasma_finalize();

    return;
}

int main(int argc, char **argv)
{
    /* number of expected command line arguments */
    int n_args = 8;

    class command_args cmd_args(argc, argv, n_args);

    /* seed the random number generator */
    if(cmd_args.seed == -1) srand(time(NULL));
    else srand(cmd_args.seed);

    run_iterations(cmd_args);

    return 0;
}

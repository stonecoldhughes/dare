#include <iostream>
#include "matrix_classes.h"

using namespace std;

int run_iterations::fastest_n = 1;

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
                                   matrix.matrix_0,
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
                                   matrix.matrix_0,
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

void run_iterations::run_dgemm_iterations(class command_args &cmd_args)
{
    class dgemm_matrix_class matrix(
                                   cmd_args.m,
                                   cmd_args.m_add,
                                   cmd_args.n,
                                   cmd_args.n_add,
                                   run_iterations::fastest_n,
                                   cmd_args.iterations
                                   );

    matrix.run_dgemm_iterations();

    return;
}

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
    
    matrix_0 = new T[m * n * sizeof(T)];

    return;
}

template<class T> matrix_base<T>::~matrix_base()
{
    delete[] matrix_0;

    return;
}

template<class T> int matrix_base<T>::dim_rand(int number, int rand_add)
{
    if(rand_add == 0) return number;

    else return number + (rand() % ++rand_add);
}

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
                
                matrix_0[ i * n + j ] = val;
            }
            
            else if(i == j)
            {
                double val = (double)(rand() % ELEMENT_MAX + 1) + n;

                matrix_0[i * n + j ] = val;
            }

            else matrix_0[i * n + j] = matrix_0[j * n + i];
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
            printf(" %-3.lf", matrix_0[ i * n + j ]);
        }

        printf("\n");
    }
    
    return;
}

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

            matrix_0[ i * n + j ] = val;
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
            printf(" %-3.lf", matrix_0[ i * n + j ]);
        }

        printf("\n");
    }

    return;
}

dgemm_matrix_class::dgemm_matrix_class(
                                      int m,
                                      int m_add,
                                      int n,
                                      int n_add,
                                      int fastest_n,
                                      int iterations
                                      )
    :
    matrix_base(m, m_add, n, n_add),
    fastest_n(fastest_n),
    iterations(iterations)
{
    matrix_1 = new double[m * n * sizeof(double)];

    matrix_2 = new double[m * n * sizeof(double)];

    return;
}

dgemm_matrix_class::~dgemm_matrix_class()
{
    fastest_n_map.clear();

    delete[] matrix_1;

    delete[] matrix_2;

    return;
}

void dgemm_matrix_class::print_matrix()
{
    return;
}

void dgemm_matrix_class::gen_matrix()
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            double val = (double)(rand() % ELEMENT_MAX + 1);

            int index = i * n + j;

            matrix_0[ index ] = val;

            matrix_1[ index ] = val;

            matrix_2[ index ] = val;
        }
    }

    return;
}

/* Needs to take input from stdin */
void dgemm_matrix_class::run_dgemm_iterations()
{
    int tile_size = -1;

    while(cin >> tile_size) insert(tile_size);

    output_fastest();

    return;
}

void dgemm_matrix_class::output_fastest()
{
    map<double, int>::iterator iter;

    for(iter = fastest_n_map.begin(); iter != fastest_n_map.end(); ++iter)
    {
        cout << iter->second << endl;;
    }

    return;
}

void dgemm_matrix_class::insert(int tile_size)
{
    plasma_init();
    
    plasma_set(PlasmaNb, tile_size);
    
    double t = omp_get_wtime();

    int i;

    for(i = 0; i < iterations; ++i)
    {
        plasma_dgemm(
                    PlasmaNoTrans,
                    PlasmaNoTrans,
                    m,
                    n,
                    n,
                    1.0,
                    matrix_0,
                    m,
                    matrix_1,
                    n,
                    0,
                    matrix_2,
                    m
                    );
    }

    double elapsed = (omp_get_wtime() - t) / i;

    plasma_finalize();

    fastest_n_map.emplace(elapsed, tile_size);
    
    if(fastest_n_map.size() > run_iterations::fastest_n) 
    {
        fastest_n_map.erase(--fastest_n_map.end());
    }

    return;
}

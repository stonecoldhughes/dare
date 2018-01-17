#include <iostream>
#include "fake_data.h"
#include "core_blas.h"

using namespace std;

int n_args = 6;

double global = 0;

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

void run(class fake_dpotrf_data &fake_dpotrf_data)
{
    double *m = fake_dpotrf_data.tile();

    if(m != NULL)
    {
        double t1 = omp_get_wtime();

        int ret_val = core_dpotrf(
                PlasmaLower,
                fake_dpotrf_data.get_tile_size(),
                m,
                fake_dpotrf_data.get_tile_size()
                );

        double t2 = omp_get_wtime();

        double elapsed = t2 - t1;

        /* Captain! This is for testing */
        printf("core_dpotrf %lf\n", global);
        fake_dpotrf_data.append_time(global);

        global += 0.001;
    }

    return;
}

void busy_wait(class fake_dpotrf_data &fake_dpotrf_data)
{
    double t = fake_dpotrf_data.tile_time();

    double t1 = omp_get_wtime();
    fake_dpotrf_data.busy_wait(t);
    double t2 = omp_get_wtime();

    printf("busy-wait for: %lf actual: %lf\n", t, t2 - t1);

    return;
}

int main(int argc, char **argv)
{
    if(argc != n_args)
    {
        printf(
              "wrong number of arguments!\n"
              "expected tile_size, iterations, window_size, clip_size, counter\n"
              );

        exit(0);
    }

    int tile_size = atoi(argv[1]);
    
    int iterations = atoi(argv[2]);

    int window_size = atoi(argv[3]);

    int clip_size = atoi(argv[4]);

    int counter = atoi(argv[5]);

    int count = counter;

    double t1 = omp_get_wtime();
    class fake_dpotrf_data fake_dpotrf_data(
                                           clip_size,
                                           tile_size,
                                           window_size
                                           );
    double init_time = omp_get_wtime() - t1;
    
    printf(
          "fake_data init time: %lf\n", 
          init_time
          );

    fake_dpotrf_data.init_time = init_time;

    /* print title lines */
    printf("clip_size %d\n", fake_dpotrf_data.get_clip_size());

    printf("tile_size %d\n", fake_dpotrf_data.get_tile_size());

    printf("window_size %d\n", fake_dpotrf_data.get_max_window_size());

    printf("counter %d\n", counter);

    /* Make this simulate a core_blas kernel being called over and over again */
    for(int i = 0; i < iterations; ++i)
    {
        /* Clip time isn't full enough */
        if(fake_dpotrf_data.tile_times_empty())
        {
            /* get a fake data matrix and run */
            printf("not full enough ");
            run(fake_dpotrf_data);
        }

        else if(fake_dpotrf_data.clip_empty())
        {
            /* busy wait */
            printf("clip full ");
            busy_wait(fake_dpotrf_data);
        }

        else
        {
            /* Captain! Change to get_max_window_size */
            if(count == counter)
            {
                /* get fake data matrix and run */
                printf("random data run ");
                run(fake_dpotrf_data);
                count = 0;
            }

            else
            {
                /* busy wait */
                printf("random busy wait ");
                busy_wait(fake_dpotrf_data);
                count++;
            }
        }
    }

    return 0;
}

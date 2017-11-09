#include <iostream>
#include "fake_data.h"
#include "core_blas.h"

using namespace std;

int n_args = 4;

int main(int argc, char **argv)
{
    if(argc != n_args)
    {
        printf(
              "wrong number of arguments!\n"
              "expected tile_size, iterations, seed\n"
              "set seed to -1 to use time(NULL) for seed value\n"
              );

        exit(0);
    }

    int tile_size = atoi(argv[1]);
    
    int iterations = atoi(argv[2]);

    class fake_dpotrf_data fake_dpotrf_data(tile_size);

    /* print the title line */
    printf("clip_size %d\n", fake_dpotrf_data.clip_size);

    printf("tile_size %d\n", fake_dpotrf_data.tile_size);

    printf("core_dpotrf <time>\n");

    printf("reload <time>\n");

    for(int i = 0; i < iterations; ++i)
    {
        double *m = fake_dpotrf_data.tile();

        if(m != NULL)
        {
            double t1 = omp_get_wtime();

            int ret_val = core_dpotrf(
                    PlasmaLower,
                    fake_dpotrf_data.tile_size,
                    m,
                    fake_dpotrf_data.tile_size
                    );

            double t2 = omp_get_wtime();

            printf("core_dpotrf %lf\n", t2 - t1);
        }

        else
        {
            fake_dpotrf_data.reload();

            printf(
                  "reload %lf\n", 
                  fake_dpotrf_data.get_reload_time()
                  );
        }
    }

    return 0;
}

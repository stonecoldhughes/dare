#include "matrix_classes.h"

using namespace std;

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

    else if(cmd_args.function == "dgemm")
    {
        run_iterations::run_dgemm_iterations(cmd_args);
    }

    else
    {
        printf("Unrecognized function. Exiting.");
    }

    return 0;
}

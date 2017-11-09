#include "dare_base.h"

using namespace std;

class Profile : public dare_base
{
    public:
        
        Profile();

        ~Profile();

        void time_kernel(uint64_t kernel, uint64_t task_id);

        void track_kernel(uint64_t kernel_type, uint64_t invokation_id, double t);

        /* 
        if you want to run 10 out of every 100 kernels,
        you give 10:100 as the xml config's "kernel_fraction"
        where kernel_run:kernel_stride = 10:100
        */
        int kernel_run;

        int kernel_stride;

        int tile_size;
};

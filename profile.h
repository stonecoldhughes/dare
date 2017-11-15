#include "dare_base.h"

using namespace std;

class Profile : public dare_base
{
    public:
        
        Profile();

        ~Profile();

        void track_kernel(uint64_t kernel_type, uint64_t invocation_id, double t);

        /* 
        if you want to run 10 out of every 100 kernels,
        you give 10:100 as the xml config's "kernel_fraction"
        where kernel_run:kernel_stride = 10:100
        */
        /* Captain! Move this into autotune class */
        
        /* returns execution time of the last kernel run by a given thread */
        double last_kernel_time(int thread_num);
        
        int kernel_run;

        int kernel_stride;

        int tile_size;
};

#ifndef DARE_BASE_H
#define DARE_BASE_H
#include "dare_base.h"
#endif

using namespace std;

class Profile : public dare_base
{
    public:
        
        Profile();

        ~Profile();

        void track_kernel(uint64_t kernel_type, double t);
        
        /* returns execution time of the last kernel run by a given thread */
        double last_kernel_time(int thread_num);
};

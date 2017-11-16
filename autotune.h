#ifndef DARE_BASE_H
#define DARE_BASE_H
#include "dare_base.h"
#endif

#include <unordered_map>
#include "fake_data.h"

using namespace std;

class Autotune : public dare_base
{
    public:

        Autotune();

        ~Autotune();
        
        /* 
        if you want to run 10 out of every 100 kernels,
        you give 10:100 as the xml config's "kernel_fraction"
        where kernel_run:kernel_stride = 10:100
        */
        int kernel_run;

        int kernel_stride;

        int tile_size;
    
        /* each thread has a counter for each kernel type */
        unsigned int **iterations;

        /* containers for fake_data. Each is num_threads long */
        /* don't initialize this until within plasma_in*/
        unordered_map<int, class fake_data> **data;
};

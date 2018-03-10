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
        you give 10:100 as the xml config's execution ratio
        where numerator : denominator = 10:100
        */
        int numerator;

        /* How often a data dep core_function is run for sampling */
        int autotune_counter;

        int denominator;

        int tile_size;

        int clip_size;

        /* How large of a consecutive subset of sampled times will be used
           for busy-wait simulations for data dependent kernels */
        int max_window_size;
    
        /* each thread has a counter for each kernel type. When it reaches
           the value of autotune_counter, it resets to 0 and samples that
           core_function if it is a data dep core_function. */
        unsigned int **iterations;

        /* pointer to num_threads unordered maps */
        /* data[thread_num][CORE_TYPE] = fake_data class for that core type */
        unordered_map<int, class fake_data*> **data;
};

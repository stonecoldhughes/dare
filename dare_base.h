#include <map>
#include <mutex>
#include <string>
#include <atomic>
#include <vector>
#include "omp.h"
#include "dlfcn.h"
#include "stdio.h"
#include "stdint.h"
#ifndef AUTOGEN_TYPES_H
#define AUTOGEN_TYPES_H
#include "autogen_types.h"
#endif

using namespace std;

class kernel_node
{
    public:
        double t_start;
        double t_end; 
        uint64_t thread_id;
        int kernel_type;
};


class dare_base
{
    public:
    
        dare_base();

        ~dare_base();
        
        /* Contains function pointers to core_blas cores */
        void (*core[TABLE_SIZE])();

        /* The location where plasma symbols can be read from */
        void (*plasma_init_ptr)();
        
        int num_threads;

    /* functions */
    protected:
        
        /* dump data to a file */
        void dump_data();

        /* Contains a vector of kernel_nodes for each thread */
        vector<class kernel_node> **kernel_vec;

        /* 
        Same length as kernel_vec. if add_node[i] == 1, then the next
        access to kernel_vec[i] needs to add another kernel_node.
        if add_node[i] == 0, next access needs to update the last
        kernel_node already there
        */
        int *add_node;
        
        /* Whether or not the tracer is set to the default case */
        int default_output;

        string output_file_name;
};

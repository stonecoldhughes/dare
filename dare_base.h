#include <map>
#include <mutex>
#include <string>
#include <atomic>
#include <vector>
#include "omp.h"
#include "dlfcn.h"
#include "stdio.h"
#include "stdint.h"
#include "autogen_types.h"

using namespace std;

class kernel_node
{
    public:
        double t_start;
        double t_end; 
        uint64_t task_id;
        uint64_t thread_id;
        int kernel_type;
        string kernel;
};


class dare_base
{
    public:
    
        dare_base();

        ~dare_base();
        
        /* Contains function pointers to core_blas cores */
        void (*core[TABLE_SIZE])();

        /* Contains unique identifiers for each kernel invocation */
        atomic<unsigned long> core_count[TABLE_SIZE];
        
        /* The location where plasma symbols can be read from */
        void (*plasma_init_ptr)();

    /* functions */
    protected:
        
        /* Writes the kernel contents to a text file */
        void kernel_to_file();
        
        /* Protection for the kernel_data map */
        mutex kernel_mut;        
        
        /* Contains a kernel_node class for each kernel invocation */
        map<string, map<uint64_t, class kernel_node*> > kernel_data;

        /* Captain! This will replace kernel_to_file */
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

        int num_threads;
        
};

#include <map>
#include <mutex>
#include <string>
#include <atomic>
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
        
        /* The location where the core_blas symbols can be read from */
        void *core_blas_file;

        /* The location where plasma symbols can be read from */
        void (*plasma_init_ptr)();

    /* functions */
    protected:
        
        /* Writes the kernel contents to a text file */
        void kernel_to_file();

        /* Whether or not the tracer is set to the default case. Change to an enum later */
        int default_output;
    
        /* Contains a kernel_node class for each kernel invocation */
        map<string, map<uint64_t, class kernel_node*> > kernel_data;
        
        /* Protection for the kernel_data map */
        mutex kernel_mut;        
};

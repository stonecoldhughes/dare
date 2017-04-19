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
        /* Captain! Is this right? */
        uint64_t thread_id;
        string kernel;
};

class Profile
{
    public:
        
        Profile();
        ~Profile();

        static void time_kernel(uint64_t kernel, uint64_t task_id);

        /* Captain! These can be replaced with an array of length TABLE_SIZE */
        void (*core[TABLE_SIZE])();
        static atomic<unsigned long> core_count[TABLE_SIZE];

    /* functions  */
    protected:

        void kernel_to_file();
        void dump_files();
        bool default_output;

    /* variables  */
    protected:    

        static map<string, map<uint64_t, class kernel_node*> > kernel_data;
        static mutex kernel_mut;
        void *core_blas_file;
};

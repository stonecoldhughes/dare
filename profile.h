#include <map>
#include <mutex>
#include <string>
#include <atomic>
#include "omp.h"
#include "dlfcn.h"
#include "stdio.h"
#include "stdint.h"
#include "autogen_types.h"
#include "plasma_trace.h"

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

        /* Captain! These can be done away with and replaced by an array of length
           TABLE_SIZE in which each entry corresponds to a function pointer.*/
        void call_core_dgemm(
                plasma_enum_t transA,
                plasma_enum_t transB,
                int m,
                int n,
                int k,
                double alpha,
                const double *A,
                int lda,
                const double *B,
                int ldb,
                double beta,
                double *C,
                int ldc
                );

        void call_core_dsyrk(
                            plasma_enum_t uplo,
                            plasma_enum_t trans,
                            int n,
                            int k,
                            double alpha,
                            const double *A,
                            int lda,
                            double beta,
                            double *C,
                            int ldc
                            );

        void call_core_dtrsm(
                            plasma_enum_t side,
                            plasma_enum_t uplo,
                            plasma_enum_t transA,
                            plasma_enum_t diag,
                            int m,
                            int n,
                            double alpha,
                            const double *A,
                            int lda,
                            double *B,
                            int ldb
                            );

        void call_core_dpotrf(
                             plasma_enum_t uplo,
                             int n,
                             double *A,
                             int lda
                             );
        
        static void time_kernel(uint64_t kernel, uint64_t task_id);

        /* Captain! These can be replaced with an array of length TABLE_SIZE */
        void (*core[TABLE_SIZE])();
        static atomic<unsigned long> core_count[TABLE_SIZE];

    /* functions  */
    protected:

        void kernel_to_file();
        void dump_files();

    /* variables  */
    protected:    

        static map<string, map<uint64_t, class kernel_node*> > kernel_data;
        static mutex kernel_mut;
        void *plasma_file;
        void *core_blas_file;
        
        /* Delete below */
        core_dgemm_hook_type core_dgemm_hook;
        core_dsyrk_hook_type core_dsyrk_hook;
        core_dtrsm_hook_type core_dtrsm_hook;
        core_dpotrf_hook_type core_dpotrf_hook;
};

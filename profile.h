#include <map>
#include <mutex>
#include <string>
#include <atomic>
#include "omp.h"
#include "ompt.h"
#include "dlfcn.h"
#include "stdio.h"
#include "stdint.h"
#include "autogen_types.h"

using namespace std;

/* Captain! Put functions_enum and kernel_table can be put in a generated header file */
/*Data structures*/
class kernel_node
{
    public:
        double t_start;
        double t_end; 
        ompt_task_id_t task_id;
        ompt_thread_id_t thread_id;
        string kernel;
};

class Profile
{
    public:
        
        Profile();
        ~Profile();
        ompt_task_id_t get_task_id(int depth = 0);
        static ompt_thread_id_t get_thread_id();
        ompt_parallel_id_t get_parallel_id(int ancestor_level = 0);

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

        static void ompt_initialize(ompt_function_lookup_t, const char*, unsigned int);
        
        /* Captain! These can be replaced with an array of length TABLE_SIZE */
        static atomic<unsigned long> core_dgemm_count;
        static atomic<unsigned long> core_dpotrf_count;
        static atomic<unsigned long> core_dsyrk_count;
        static atomic<unsigned long> core_dtrsm_count;
        void (*core[TABLE_SIZE])();
        static atomic<unsigned long> core_count[TABLE_SIZE];

    /* functions  */
    protected:

        static void ompt_control_cb(uint64_t kernel, uint64_t task_id);
        void kernel_to_file();
        void dump_files();

    /* variables  */
    protected:    

        static map<string, map<ompt_task_id_t, class kernel_node*> > kernel_data;
        static mutex kernel_mut;
        void *plasma_file;
        void *core_blas_file;
        
        /*Function pointers*/
        static ompt_get_thread_id_t get_thread_id_ptr;
        static ompt_get_task_id_t get_task_id_ptr;
        static ompt_get_parallel_id_t get_parallel_id_ptr;
        /* Delete below */
        core_dgemm_hook_type core_dgemm_hook;
        core_dsyrk_hook_type core_dsyrk_hook;
        core_dtrsm_hook_type core_dtrsm_hook;
        core_dpotrf_hook_type core_dpotrf_hook;
};

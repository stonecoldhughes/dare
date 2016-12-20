#include <map>
#include <mutex>
#include <string>
#include <atomic>
#include "omp.h"
#include "ompt.h"
#include "dlfcn.h"
#include "stdio.h"
#include "stdint.h"
#include "profile_types.h"

using namespace std;

extern bool append;

extern class Profile profile;

//extern const string kernel_table[];

typedef enum functions_enum
{
    CBLAS_DGEMM = 0,
    CBLAS_DSYRK = 1,
    CORE_DTRSM = 2,
    CORE_DPOTRF = 3,
    
    TABLE_SIZE
} functions_enum;

/*Enumerated types*/
const string kernel_table[] =
{
    "cblas_dgemm",
    "cblas_dsyrk",
    "core_dtrsm",
    "core_dpotrf"
};


/*Data structures*/
struct kernel_node
{
    double t_start;
    double t_end; 
    ompt_task_id_t task_id;
    ompt_thread_id_t thread_id;
    string kernel;
};

class Profile
{
    public:
        
        void setup();
        void finish();
        ompt_task_id_t get_task_id(int depth = 0);
        static ompt_thread_id_t get_thread_id();
        ompt_parallel_id_t get_parallel_id(int ancestor_level = 0);
        void call_plasma_init();
        void call_plasma_finalize();
        /* core functions to hook */

        void call_cblas_dgemm(
                             const  CBLAS_LAYOUT Layout,
                             const  CBLAS_TRANSPOSE TransA,
                             const  CBLAS_TRANSPOSE TransB,
                             const MKL_INT M,
                             const MKL_INT N,
                             const MKL_INT K,
                             const double alpha,
                             const double *A,
                             const MKL_INT lda,
                             const double *B,
                             const MKL_INT ldb,
                             const double beta,
                             double *C,
                             const MKL_INT ldc
                             );

        void call_cblas_dsyrk(
                             const  CBLAS_LAYOUT Layout,
                             const  CBLAS_UPLO Uplo,
                             const  CBLAS_TRANSPOSE Trans,
                             const MKL_INT N,
                             const MKL_INT K,
                             const double alpha,
                             const double *A,
                             const MKL_INT lda,
                             const double beta,
                             double *C,
                             const MKL_INT ldc
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
        
        static atomic<unsigned long> cblas_dgemm_count;
        static atomic<unsigned long> core_dpotrf_count;
        static atomic<unsigned long> cblas_dsyrk_count;
        static atomic<unsigned long> core_dtrsm_count;

    /* functions  */
    protected:

        static void ompt_control_cb(uint64_t kernel, uint64_t task_id);
        void kernel_to_file();
        void dump_files();

    /* variables  */
    protected:    

        static map<string, map<ompt_task_id_t, struct kernel_node*> > kernel_data;
        static mutex kernel_mut;
        void *plasma_file;
        
        /*Function pointers*/
        static ompt_get_thread_id_t get_thread_id_ptr;
        static ompt_get_task_id_t get_task_id_ptr;
        static ompt_get_parallel_id_t get_parallel_id_ptr;
        plasma_init_hook_type plasma_init_hook;
        plasma_finalize_hook_type plasma_finalize_hook;
        cblas_dgemm_hook_type cblas_dgemm_hook;
        cblas_dsyrk_hook_type cblas_dsyrk_hook;
        core_dtrsm_hook_type core_dtrsm_hook;
        core_dpotrf_hook_type core_dpotrf_hook;
};

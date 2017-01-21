#include "profile.h"

using namespace std;

/*Declaration of static member variables*/
map<string, map<ompt_task_id_t, struct kernel_node*> > Profile::kernel_data;

mutex Profile::kernel_mut;

atomic<unsigned long> Profile::core_dgemm_count;
atomic<unsigned long> Profile::core_dpotrf_count;
atomic<unsigned long> Profile::cblas_dsyrk_count;
atomic<unsigned long> Profile::core_dtrsm_count;

/* Declare static class variables  */
ompt_get_thread_id_t Profile::get_thread_id_ptr;

ompt_get_task_id_t Profile::get_task_id_ptr;

ompt_get_parallel_id_t Profile::get_parallel_id_ptr;

/*This will obtain function pointers to hooks in the PLASMA library*/
void Profile::setup()
{
    /*Obtain a handle to the plasma library*/
    plasma_file = dlopen("/Users/hhughe11/plasma/lib/libplasma.so", RTLD_LAZY);

    if(plasma_file == NULL) {printf("plasma_file null\n"); exit(0);};

    /*hook plasma_init()*/
    plasma_init_hook = (plasma_init_hook_type)dlsym(plasma_file, "plasma_init");
    if(plasma_init_hook == NULL) {printf("plasma_init() hook NULL\n"); exit(0);}

    /*hook plasma_finalize()*/
    plasma_finalize_hook = (plasma_finalize_hook_type)dlsym(plasma_file, "plasma_finalize");
    if(plasma_finalize_hook == NULL) {printf("plasma_finalize() hook NULL\n"); exit(0);}

    /* hook core_dgemm() */
    core_dgemm_hook = (core_dgemm_hook_type)dlsym(plasma_file, "core_dgemm");
    if(core_dgemm_hook == NULL) {printf("core_dgemm() hook NULL\n"); exit(0);}
        
    /* hook cblas_dsyrk() */
    cblas_dsyrk_hook = (cblas_dsyrk_hook_type)dlsym(plasma_file, "cblas_dsyrk");
    if(cblas_dsyrk_hook == NULL) {printf("cblas_dsyrk() hook NULL\n"); exit(0);}
    
    /* hook core_dtrsm() */
    core_dtrsm_hook = (core_dtrsm_hook_type)dlsym(plasma_file, "core_dtrsm");
    if(core_dtrsm_hook == NULL) {printf("core_dtrsm() hook NULL\n"); exit(0);}

    /* hook core_dpotrf() */
    core_dpotrf_hook = (core_dpotrf_hook_type)dlsym(plasma_file, "core_dpotrf");
    if(core_dpotrf_hook == NULL) {printf("core_dpotrf() hook NULL\n"); exit(0);}

    /*set atomic counters*/
    core_dgemm_count = 0;
    cblas_dsyrk_count = 0;
    core_dtrsm_count = 0;
    core_dpotrf_count = 0;
    
    return;
}

void Profile::finish()
{
    dump_files();

    dlclose(plasma_file);

    return;
}

/*Captain!!! Investigate the effect of returning the pointer or just calling it from here*/
ompt_task_id_t Profile::get_task_id(int depth)
{
    return (*get_task_id_ptr)(depth);
}

ompt_thread_id_t Profile::get_thread_id()
{
    return (*get_thread_id_ptr)();
}

ompt_parallel_id_t Profile::get_parallel_id(int ancestor_level)
{
    return (*get_parallel_id_ptr)(ancestor_level);
}

void Profile::call_plasma_init()
{
    (*plasma_init_hook)();

    return;
}

void Profile::call_plasma_finalize()
{
    (*plasma_finalize_hook)();

    return;
}

void Profile::dump_files()
{
    kernel_to_file();

    return;
}

void Profile::kernel_to_file()
{
    FILE *file;
    map<string, map<ompt_task_id_t, struct kernel_node*> >::iterator iter1;
    map<ompt_task_id_t, struct kernel_node*>::iterator iter2;

    /*Data must be appended to files after consecutive "plasma_init()" "plasma_finalize()" 
    invokation pairs*/
    if(append)
    {
        file = fopen("kernel_data.txt", "a");
    }
    
    else
    {
        file = fopen("kernel_data.txt", "w");
        append = false;
    }

    fprintf(file, "kernel t_start task_id thread_id\n");

    for(iter1 = kernel_data.begin(); iter1 != kernel_data.end(); iter1++)
    {
        fprintf(file, "%s\n", iter1->first.c_str());
        for(iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++)
        {   
            fprintf(
                    file
                    ,"  %s %lf %lf %llu %llu\n"
                    ,iter2->second->kernel.c_str()
                    ,iter2->second->t_start
                    ,iter2->second->t_end
                    ,iter2->second->task_id
                    ,iter2->second->thread_id
                   );  
            free(iter2->second);
        }   
        iter1->second.clear();
    }

    fclose(file);

    kernel_data.clear();

    return;
}

void Profile::call_core_dgemm(
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
                        )
{
    (*core_dgemm_hook)(
                      transA,
                      transB,
                      m,
                      n,
                      k,
                      alpha,
                      A,
                      lda,
                      B,
                      ldb,
                      beta,
                      C,
                      ldc
                      );

    return;
}

void Profile::call_cblas_dsyrk(
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
                              )
{
    (*cblas_dsyrk_hook)(
                       Layout,
                       Uplo,
                       Trans,
                       N,
                       K,
                       alpha,
                       A,
                       lda,
                       beta,
                       C,
                       ldc
                       );

    return;
}

void Profile::call_core_dtrsm(
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
                             )
{
    (*core_dtrsm_hook)(
                      side,
                      uplo,
                      transA,
                      diag,
                      m,
                      n,
                      alpha,
                      A,
                      lda,
                      B,
                      ldb
                      );
    return;
}


void Profile::call_core_dpotrf(
                              plasma_enum_t uplo,
                              int n,
                              double *A,
                              int lda
                              )
{
    (*core_dpotrf_hook)(
                       uplo,
                       n,
                       A,
                       lda
                       );

    return;
}

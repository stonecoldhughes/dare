#include "profile.h"

extern bool append;

using namespace std;

/*Declaration of static member variables*/
map<string, map<ompt_task_id_t, struct kernel_node*> > Profile::kernel_data;

mutex Profile::kernel_mut;

/* Declare static class variables  */
ompt_get_thread_id_t Profile::get_thread_id_ptr;

ompt_get_task_id_t Profile::get_task_id_ptr;

ompt_get_parallel_id_t Profile::get_parallel_id_ptr;

Profile::~Profile()
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

    fprintf(file, "kernel t_start t_end kernel_identifier thread_id\n");

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

            /* This is the kernel_node */
            delete iter2->second;
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

void Profile::call_core_dsyrk(
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
                             )
{
    (*core_dsyrk_hook)(
                      uplo,
                      trans,
                      n,
                      k,
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

#include "profile.h"

extern bool append;

using namespace std;

/*Declaration of static member variables*/
map<string, map<uint64_t, struct kernel_node*> > Profile::kernel_data;

mutex Profile::kernel_mut;

Profile::~Profile()
{
    dump_files();

    dlclose(plasma_file);

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
    map<string, map<uint64_t, struct kernel_node*> >::iterator iter1;
    map<uint64_t, struct kernel_node*>::iterator iter2;

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

void Profile::time_kernel(uint64_t kernel, uint64_t task_id)
{
    map<string, map<uint64_t, class kernel_node*> >::iterator iter1;
    map<uint64_t, class kernel_node*>::iterator iter2;
    class kernel_node *knode;

    iter1 = kernel_data.find(kernel_table[kernel]);

    /*first time the kernel is invoked*/
    if(iter1 == kernel_data.end())
    {
        knode = new class kernel_node;
        knode->kernel = kernel_table[kernel];
        knode->t_start = omp_get_wtime();
        knode->t_end = -1;
        knode->task_id = task_id;

        /*can you trust this call below because it's called here and not in the hooked function?*/
        knode->thread_id = omp_get_thread_num();

        /*Insert into map*/
        kernel_mut.lock();
        kernel_data[kernel_table[kernel]][task_id] = knode;
        kernel_mut.unlock();
    }

    else
    {
        iter2 = iter1->second.find(task_id);

        /*kernel has been invoked, but this is a new task*/
        if(iter2 == iter1->second.end())
        {
            knode = new class kernel_node;
            knode->kernel = kernel_table[kernel];
            knode->t_start = omp_get_wtime();
            knode->t_end = -1;
            knode->task_id = task_id;

            /*Captain! Can you really trust this call below because it's called here and not in the hooked function?*/
            knode->thread_id = omp_get_thread_num();

            /*Insert into map*/
            kernel_mut.lock();
            kernel_data[kernel_table[kernel]][task_id] = knode;
            kernel_mut.unlock();
        }

        /*kernel has been invoked, task exists*/
        else
        {
            kernel_mut.lock();
            kernel_data[kernel_table[kernel]][task_id]->t_end = omp_get_wtime();
            kernel_mut.unlock();
        }
    }

    return;
}

/*Global Variables*/

/*
If there are multiple plasma_init()/plasma_finalize() sections, this indicates
whether a new output file must be created or if an existing file should be
appended to. plasma_finalize() should set the value to "false" if it is currently
"true"
*/
bool append = false;

/* The constructor for this class should run before "main" because it is a global object */
class Profile profile;

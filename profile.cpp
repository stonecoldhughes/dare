#include "profile.h"

using namespace std;

/* Empty constructor and destructor */
Profile::Profile()
{
}

Profile::~Profile()
{
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

/* The constructor for this class should run before "main" because it is a global object */
class Profile profile;

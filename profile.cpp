#include "profile.h"

using namespace std;

/* Empty constructor and destructor */
Profile::Profile()
{
}

Profile::~Profile()
{
}

/* 
Remove the "t" parameter once you've stabilized this code, replace with
omp_get_wtime() - do it in the function call so you don't waste time jumping
*/
void Profile::track_kernel(uint64_t kernel_type, uint64_t invokation_id, double t)
{
    int thread_id = omp_get_thread_num();

    if(add_node[thread_id])
    {
        
        printf(
              "Thread %d: adding %s %d to kernel_vec[%d] at time %lf\n",
              thread_id,
              kernel_table[kernel_type].c_str(),
              invokation_id,
              thread_id,
              t
              );

        fflush(stdout);
        
        class kernel_node knode;
        /* resolve the string representation later */
        knode.kernel_type = kernel_type;
        knode.t_start = t;
        knode.t_end = -1;
        knode.task_id = invokation_id;
        knode.thread_id = thread_id;
        kernel_vec[thread_id]->push_back(std::move(knode));
        printf("Thread %d: finished adding\n", thread_id);
    }
    
    else
    {
        printf("Thread %d: About to complete! step 1\n", thread_id);
        class kernel_node &knode = kernel_vec[thread_id]->back();
        printf("Thread %d: About to complete! step 2\n", thread_id);

        printf(
              "Thread %d: completing %s %d to kernel_vec[%d] at time %lf\n",
              thread_id,
              kernel_table[knode.kernel_type].c_str(),
              knode.task_id,
              knode.thread_id,
              t
              );
        
        knode.t_end = t;
        printf("Thread %d: completed\n", thread_id);
    }
    
    add_node[thread_id] = !add_node[thread_id];

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

        /* insert into kernel_vec */
        track_kernel(kernel, task_id, knode->t_start);
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

            knode->thread_id = omp_get_thread_num();

            /*Insert into map*/
            kernel_mut.lock();
            kernel_data[kernel_table[kernel]][task_id] = knode;
            kernel_mut.unlock();

            /* insert into kernel_vec */
            track_kernel(kernel, task_id, knode->t_start);
        }

        /*kernel has been invoked, task exists*/
        else
        {
            kernel_mut.lock();
            double t = omp_get_wtime();
            kernel_data[kernel_table[kernel]][task_id]->t_end = t;
            kernel_mut.unlock();

            /* insert into kernel_vec */
            track_kernel(0, 0, t);
        }
    }

    return;
}

/* The constructor for this class should run before "main" because it is a global object */
class Profile profile;

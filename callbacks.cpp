/*Captain! Add a "calling task_id" and "finishing task_id" field for ompt_control_cb to verify
  your assumption that a given kernel is only ever assigned one task id.*/
/*Captain! Will abstracting away the kernel calls cause different tasks to be spawned off?*/
#include "profile.h"

using namespace std;

/*Register event handlers*/
void Profile::ompt_initialize
    (
    ompt_function_lookup_t lookup, 
    const char *runtime_version,
    unsigned int ompt_version
    )
{
    ompt_interface_fn_t ompt_set_callback_ptr = (ompt_interface_fn_t)lookup("ompt_set_callback");
    ompt_event_t ompt_event;

    get_thread_id_ptr = (ompt_get_thread_id_t)lookup("ompt_get_thread_id");
    get_task_id_ptr = (ompt_get_task_id_t)lookup("ompt_get_task_id");
    get_parallel_id_ptr = (ompt_get_parallel_id_t)lookup("ompt_get_parallel_id");

    /*Register ompt_control event callback*/
    ompt_event = ompt_event_control;
    ((callback_typecast)(*ompt_set_callback_ptr))(ompt_event, ((ompt_callback_t)ompt_control_cb));

    return;
}

/*Captain! You can't pass the thread_id to this function because all parameters
  are used for "kernel" and "task_id". Get the thread ID in the function. But... is this the
  same thread that called it?!*/
void Profile::ompt_control_cb(uint64_t kernel, uint64_t task_id)
{
    map<string, map<ompt_task_id_t, struct kernel_node*> >::iterator iter1;
    map<ompt_task_id_t, struct kernel_node*>::iterator iter2;
    struct kernel_node *knode;

    iter1 = kernel_data.find(kernel_table[kernel]);

    /*first time the kernel is invoked*/
    if(iter1 == kernel_data.end())
    {
        knode = (struct kernel_node*)malloc(sizeof(struct kernel_node));
        knode->kernel = kernel_table[kernel];
        knode->t_start = omp_get_wtime();
        knode->t_end = -1;
        knode->task_id = task_id;

        /*can you trust this call below because it's called here and not in the hooked function?*/
        knode->thread_id = get_thread_id();

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
            knode = (struct kernel_node*)malloc(sizeof(struct kernel_node));
            knode->kernel = kernel_table[kernel];
            knode->t_start = omp_get_wtime();
            knode->t_end = -1;
            knode->task_id = task_id;

            /*Captain! Can you really trust this call below because it's called here and not in the hooked function?*/
            knode->thread_id = (*get_thread_id_ptr)();

            /*Insert into map*/
            kernel_mut.lock();
            kernel_data[kernel_table[kernel]][task_id] = knode;
            kernel_mut.unlock();
        }

        /*kernel has been invoked, task exists*/
        else
        {
            kernel_data[kernel_table[kernel]][task_id]->t_end = omp_get_wtime();
        }
    }

    return;
}

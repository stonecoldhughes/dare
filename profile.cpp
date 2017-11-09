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
void Profile::track_kernel(uint64_t kernel_type, uint64_t invocation_id, double t)
{
    int thread_id = omp_get_thread_num();

    if(add_node[thread_id])
    {
        class kernel_node knode;
        
        /* resolve the string representation later */
        knode.kernel_type = kernel_type;
        
        knode.t_start = t;
        
        knode.t_end = -1;
        
        knode.task_id = invocation_id;
        
        knode.thread_id = thread_id;
        
        kernel_vec[thread_id]->push_back(std::move(knode));
    }
    
    else
    {
        class kernel_node &knode = kernel_vec[thread_id]->back();

        knode.t_end = t;
    }
    
    add_node[thread_id] = !add_node[thread_id];

    return;
}

/* The constructor for this class should run before "main" because it is a global object */
class Profile profile;

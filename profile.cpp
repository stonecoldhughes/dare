#include "profile.h"

using namespace std;

/* Empty constructor and destructor */
Profile::Profile()
{
}

Profile::~Profile()
{
}

/* returns the time for the last kernel that was run */
double Profile::last_kernel_time()
{
    int thread_id = omp_get_thread_num();

    class kernel_node &knode = kernel_vec[thread_id]->back();

    return knode.t_end - knode.t_start;
}

/* 
Remove the "t" parameter once you've stabilized this code, replace with
omp_get_wtime() - do it in the function call so you don't waste time jumping
*/
void Profile::track_kernel(uint64_t kernel_type, double t)
{
    int thread_id = omp_get_thread_num();

    if(add_node[thread_id])
    {
        class kernel_node knode;
        
        /* resolve the string representation later */
        knode.kernel_type = kernel_type;
        
        knode.t_start = t;
        
        knode.t_end = -1;
        
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

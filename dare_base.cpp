#include "dare_base.h"

extern bool append;

using namespace std;

/* This function also clears the data structure so that it can be called
multiple times if there's tons of data
*/
void dare_base::dump_data()
{
    FILE *file;
    
    /* Change the output file name to be a configurable option */
    if(append)
    {
        file = fopen("kernel_data.txt", "a");
    }
    
    else
    {
        file = fopen("kernel_data.txt", "w");

        append = false;
    }
    
    fprintf(file, "kernel t_start t_end t_elapsed kernel_identifier thread_id\n");

    /* transfer contents of kernel_vec to the file */
    for(int i = 0; i < num_threads; ++i)
    {
        vector<class kernel_node> *v = kernel_vec[i];
        for(int j = 0; j < v->size(); ++j)
        {
            class kernel_node &k = (*v)[j];
            fprintf(
                   file,
                   "%s %lf %lf %lf %llu %llu\n",
                   kernel_table[k.kernel_type].c_str(),
                   k.t_start,
                   k.t_end,
                   k.t_end - k.t_start,
                   k.task_id,
                   k.thread_id
                   );
        }

        v->clear();
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

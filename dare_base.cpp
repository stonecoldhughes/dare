#include "dare_base.h"

extern bool append;

using namespace std;

dare_base::~dare_base()
{
    if(default_output)
    {
        kernel_to_file();
    }

    return;
}

void dare_base::kernel_to_file()
{
    FILE *file;
    map<string, map<uint64_t, class kernel_node*> >::iterator iter1;
    map<uint64_t, class kernel_node*>::iterator iter2;

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

/*Global Variables*/

/*
If there are multiple plasma_init()/plasma_finalize() sections, this indicates
whether a new output file must be created or if an existing file should be
appended to. plasma_finalize() should set the value to "false" if it is currently
"true"
*/
bool append = false;

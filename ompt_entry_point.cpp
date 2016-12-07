#include "profile.h"

using namespace std;

/*Global Variables*/

/*
If there are multiple plasma_init()/plasma_finalize() sections, this indicates
whether a new output file must be created or if an existing file should be
appended to. plasma_finalize() should set the value to "false" if it is currently
"true"
*/

bool append = false;

class Profile profile;

/*Enumerated types*/
const string kernel_table[] =
{
    "cblas_dgemm",
    "cblas_dsyrk",
    "cblas_dtrsm",
    "LAPACKE_dpotrf"
};

/*Entry point for the OMPT interface*/
ompt_initialize_t ompt_tool(void)
{
  //return &(profile.ompt_initialize);
  return profile.ompt_initialize;
}

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

/* The constructor for this class should run before "main" because it is a global object */
class Profile profile;

/*Entry point for the OMPT interface*/
ompt_initialize_t ompt_tool(void)
{
  return profile.ompt_initialize;
}

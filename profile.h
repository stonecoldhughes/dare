#include "dare_base.h"

using namespace std;

class Profile : public dare_base
{
    public:
        
        Profile();
        ~Profile();

        void time_kernel(uint64_t kernel, uint64_t task_id);
};

#include "autotune.h"

using namespace std;

Autotune::Autotune()
{
    /* initialize iterations counters */
    iterations = new unsigned int*[num_threads];

    for(int i = 0; i < num_threads; ++i)
    {
        iterations[i] = new unsigned int[TABLE_SIZE];

        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            iterations[i][j] = 0;
        }
    }

    data = new unordered_map<int, class fake_data*>*[num_threads];
    
    for(int i = 0; i < num_threads; ++i)
    {
        data[i] = new unordered_map<int, class fake_data*>;
    }

    return;
}

Autotune::~Autotune()
{
    /* delete iterations */
    for(int i = 0; i < num_threads; ++i)
    {
        delete[] iterations[i];
    }

    delete[] iterations;

    /* delete fake data */
    for(int i = 0; i < num_threads; ++i)
    {
        for(
           unordered_map<int, class fake_data*>::iterator iter = data[i]->begin();
           iter != data[i]->end();
           ++iter
           )
        {
            delete iter->second;
        }

        delete data[i];
    }

    delete[] data; 

    return;
}

class Autotune autotune;

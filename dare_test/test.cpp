#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    stringstream ss;
    string str;

    printf("command line args:\n");
    for(int i = 0; i < argc; ++i)
    {
        printf(" %s", argv[i]);
    }
    printf("\n");

    getline(cin, str);

    cout << "From stdin: " << str << endl;

    return 0;
}

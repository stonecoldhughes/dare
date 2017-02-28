from pathlib import Path
import sys
import re

header_includes = '#include "mkl_cblas.h"\n' \
                  +'#include "plasma.h"\n' \
                  +'#include "mkl_lapacke.h"\n' \
                  +'\nusing namespace std;\n'

cpp_includes = '#include "profile.h"\n' \
               + '\nusing namesapce std;\n\n'

class core_class:
    
    def __init__(self, rtype, name, args):
        self.rtype = rtype
        self.name = name
        self.args = args

def write_lookup_tables(f, core_kernel_list):
    string_table = []
    enum_table = []

    #Create lookup tables 
    for c in core_kernel_list:
        string_table.append(c.name)
        enum_table.append(c.name.upper())

    f.write('typedef enum functions_enum\n{\n')
    i = 0
    for s in enum_table:
        f.write('    ' + s + ' = {0}'.format(i) + '\n')
        i += 1
    f.write('\n' + '    ' + 'TABLE_SIZE\n')
    f.write('}\n\n')

    f.write('const string kernel_table[] =\n{\n')
    for s in string_table:
        f.write('    \"{0}\",\n'.format(s))
    f.write('}\n\n')

def breakup(l, spaces):
    words = l.split(',')
    arg_str = ''
    for i in range(0, len(words)-1):
        arg_str += spaces + words[i].strip() + ',\n'
    arg_str += spaces + words[-1].strip()
    return arg_str

def dump_file(string):
    f = open(string, 'r')
    file_list = list(f)
    f.close()
    file_string = ''
    for line in file_list:
        file_string = file_string + ' ' + line.strip()
    return file_string

def write_typedefs(f, core_kernel_list):
    for i in range(0, len(core_kernel_list)-1):
        hook_str = 'typedef ' \
                   + core_kernel_list[i].rtype \
                   + ' (*' + core_kernel_list[i].name + '_hook_type' \
                   + ')(\n'
        spaces = (len(hook_str)-2) * ' '
        arg_str = breakup(core_kernel_list[i].args, spaces)
        hook_str += arg_str \
                    + '\n' + spaces + ');\n\n'
        f.write(hook_str)

    hook_str = 'typedef ' \
               + core_kernel_list[-1].rtype \
               + ' (*' + core_kernel_list[-1].name + '_hook_type' \
               + ')(\n'
    spaces = (len(hook_str)-2) * ' '
    arg_str = breakup(core_kernel_list[-1].args, spaces)
    hook_str += arg_str \
                + '\n' + spaces + ');\n'
    f.write(hook_str)

def write_header(f, core_kernel_list):
    #Write header
    f.write(header_includes)

    #Write lookup tables
    write_lookup_tables(f, core_kernel_list)

    #Next, write function hook typedefs
    write_typedefs(f, core_kernel_list)

def parse(file_string):
    #Regex to match core_blas function declarations
    core_kernel_list = []
    core_pattern = r'\s*(\w*\n?)\s+(core_(?!omp)\w+)\s*\(([^;]*)\)'
    regex = re.compile(core_pattern)
    matches = regex.finditer(file_string)
    for m in matches:
        core_kernel_list.append(core_class(m.group(1), m.group(2), m.group(3)))
    return core_kernel_list
    
def write_autogen_cpp(f, core_kernel_list):
    f.write( \
    '''#include "profile.h"

using namespace std;

atomic<unsigned long> Profile::core_count[TABLE_SIZE];

/*This will obtain function pointers to hooks in the PLASMA library*/
Profile::Profile()
{{
    void (*fptr)();

    /* Obtain a handle to the core_blas library */
    core_blas_file = dlopen("{0}libcoreblas.so", RTLD_LAZY);
    if(core_blas_file == NULL) {{printf("core_blas_file null\\n"); exit(0);}}
    '''.format(sys.argv[1]) \
    )

    for c in core_kernel_list:
        f.write( \
    '''
    /* hook {0}() */
    fptr = (void (*)())dlsym(core_blas_file, "{0}");
    if(fptr == NULL) {{printf("{0}() hook NULL\\n"); exit(0);}}
    core[{1}] = fptr;
    '''.format(c.name, c.name.upper()) \
               )

    #Captain! Write the rest of the shit in here
    f.write( \
    '''
    /*set atomic counters*/
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        core_count[i] = 0;
    }
    
    return;
}''' \
           )

def arg_strip(string, spaces):
    pattern = r'(.*) \**(.*)'
    regex = re.compile(pattern)
    matches = list(regex.finditer(string))
    arg_str = ''
    for i in range(0, len(matches)):
        arg_str += (spaces + matches[i].group(2) + '\n')

    return arg_str

def write_hooks_cpp(f, core_kernel_list):
    f.write( \
    '''#include "profile.h"

extern class Profile profile;

using namespace std;

''' \
           )

    for c in core_kernel_list:
        string = 'extern "C" {0} {1}(\n'.format(c.rtype, c.name)
        spaces = (len(string) - 2) * ' '
        arg_str = breakup(c.args, spaces)
        string += arg_str + '\n' + spaces + ')\n'

        #Create the function call
        if(c.rtype == 'void'):
            call = '(({0}_hook_type)profile.core[{1}])(\n'.format(c.name, c.name.upper())
            spaces = (len(call) + 2) * ' '
        else:
            call = 'retval = (({0}_hook_type)profile.core[{1}])(\n'.format(c.name, c.name.upper())
            spaces = (len(call) + 2) * ' '
            call = '{0} ret_val;\n\n'.format(c.rtype) + '    ' + call

        call += arg_strip(arg_str, spaces) + spaces + ');'
        string += \
        '''{{
    int count = profile.core_count[{0}]++;

    ompt_control((unsigned long){0}, count);
    
    {1}

    ompt_control((unsigned long){0}, count);\n\n'''.format(c.name.upper(), call)

        if(c.rtype == 'void'):
            string += '    return;\n}\n\n'
        else:
            string += '    return ret_val;\n}\n\n'

        f.write(string) 

#Open autogen_types.h
autogen_types_h = open('autogen_types.h', 'w')

#Open files containing core_blas declarations
file_string = ''
file_pattern = r'core_blas_\w.h'
file_regex = re.compile(file_pattern)
p = Path(sys.argv[1])
for f in p.iterdir():
    if(f.is_file() and file_regex.fullmatch(f.name)):
        file_string += dump_file(str(f))

#Create kernel list
core_kernel_list = parse(file_string)

#All header files are concatenated into the same string. Header is written in one pass.
write_header(autogen_types_h, core_kernel_list)

#Close autogenerated header file
autogen_types_h.close()

#Create autogenerated cpp file
autogen_cpp = open('autogen.cpp', 'w')

write_autogen_cpp(autogen_cpp, core_kernel_list)

autogen_cpp.close()

#Autogenerage the hooks.cpp file
hooks_cpp = open('hooks.cpp', 'w')

write_hooks_cpp(hooks_cpp, core_kernel_list)

hooks_cpp.close()

import xml.etree.ElementTree as xml
import subprocess
from pathlib import Path
import argparse
import sys
import re

header_includes = '#include "mkl_cblas.h"\n' \
                  +'#include "plasma.h"\n' \
                  +'#include "mkl_lapacke.h"\n' \
                  +'\nusing namespace std;\n'

cpp_includes = '#include "profile.h"\n' \
               + '\nusing namesapce std;\n\n'

four_space = '    '

autotune_header_str = \
'''
#include "profile.h"

extern class Profile profile;

using namespace std;
'''

class core_class:
    
    def __init__(self, rtype, name, args):
        self.rtype = rtype
        self.name = name
        self.args = args

class rgx_obj_class:
    def __init__(self):
        self.file_regex = re.compile(r'core_blas_\w\.h')
        self.core_regex = re.compile(r'\s*(\w*\n?)\s+(core_(?!omp)\w+)\s*\(([^;]*)\)')
        self.arg_regex = re.compile(r'(.*) \**(.*)')

class wrap_class:
    def __init__(self, wrap_above, wrap_below):
        self.above = wrap_above
        self.below = wrap_below

class wrap_func:
    def __init__(self, name, arg_list, filex, decl):
        self.name = name
        self.arg_list = arg_list
        self.filex = filex
        self.decl = decl

#Each element of the arg list contains 'None' or a dictionary that tells the value of
#the positional argument for the above or below wrapper depending on the core kernel
#in question
class config_class:
    def __init__( \
                 self, \
                 above_func, \
                 above_args, \
                 above_filex, \
                 above_decl, \
                 below_func, \
                 below_args, \
                 below_filex, \
                 below_decl, \
                 use_default, \
                 default_color_map, \
                 ):
        self.wrap_above_func = above_func
        self.wrap_below_func = below_func
        self.below_arg_list = below_args
        self.above_arg_list = above_args
        self.use_default = use_default
        self.default_color_map = default_color_map
        self.above_filex = above_filex
        self.above_decl = above_decl
        self.below_filex = below_filex
        self.below_decl = below_decl

def list_args(args, root):
    #Each configurable arg has a set of possible choices it could be.
    #A dictionary will relate kernel to choice for a particular arg. This dict
    #Will be in a list that maintains the same positional order of the args specified in
    #The file
    arg_list = []
    
    for arg in args:
        
        arg_map = dict()

        if(arg.get('configurable') == 'True'):
            
            #Find the list of choices for this arg and create a dict out of it
            arg_set = root.find(arg.text.strip())

            if(arg_set != None):

                pairs = arg_set.findall('pair')

                for pair in pairs:
                    val_str = pair.find('value').text.strip()
                    arg_map[pair.find('key').text.strip()] = val_str
                        
            #If it isn't configurable, just set default to the argument specified
        else:
            arg_map['default'] = arg.text.strip()

        arg_list.append(arg_map)
    
    return arg_list

def name_and_args(tag, root):
    if(tag != None):
        name_tag = tag.find('name')
        if(name_tag != None):
            name = name_tag.text.strip()
        else:
            name = None

        arg_tag = tag.find('args')
        if(arg_tag != None):
            arg_list = list_args(arg_tag.findall('arg'), root)
        else:
            arg_list = None

        filex_tag = tag.find('file_extension')
        if(filex_tag != None):
            filex = filex_tag.text.strip()
        else:
            filex = None

        decl_tag = tag.find('declaration')
        if(decl_tag != None):
            decl = decl_tag.text.strip()
        else:
            decl = None

        return wrap_func(name, arg_list, filex, decl)
        
    else:
        return None

def default_colors(root, use_default_tag):
    
    default_color_map = {}

    color_str = use_default_tag.get('kernel_colors')
    
    pairs = root.find(color_str).findall('pair')
    
    for pair in pairs:
        
        val_str = pair.find('value').text.strip()
        
        default_color_map[pair.find('key').text.strip()] = val_str

    return default_color_map

def trace_config(root):
    
    #Determine whether or not to use default behavior
    use_default_tag = root.find('use_default')
    if(use_default_tag != None):
        if(int(use_default_tag.text.strip()) == 1):
            use_default = 1
        else:
            use_default = 0
    else:
        use_default = 0

    #Obtain the calling conventions for the wrapper functions
    if(use_default == 0):
        wrap_below_func = name_and_args(root.find('wrap_below_func'), root)
        wrap_above_func = name_and_args(root.find('wrap_above_func'), root)
        default_color_map = {}
    else:
        default_color_map = default_colors(root, use_default_tag)
        wrap_below_func = wrap_func('', [], '', '')
        wrap_above_func = wrap_func('', [], '', '')

    c = config_class(\
                    wrap_above_func.name, \
                    wrap_above_func.arg_list, \
                    wrap_above_func.filex, \
                    wrap_above_func.decl,
                    wrap_below_func.name, \
                    wrap_below_func.arg_list, \
                    wrap_below_func.filex, \
                    wrap_below_func.decl, \
                    use_default, \
                    default_color_map, \
                    )
        
    return c

def write_lookup_tables(f, core_kernel_list):
    string_table = []
    enum_table = []

    #Create lookup tables 
    for c in core_kernel_list.values():
        string_table.append(c.name)
        enum_table.append(c.name.upper())

    f.write('enum functions_enum\n{\n')
    i = 0
    for s in enum_table:
        f.write(four_space + s + ' = {0},'.format(i) + '\n')
        i += 1
    f.write('\n' + four_space + 'TABLE_SIZE\n')
    f.write('};\n\n')

    f.write('const string kernel_table[] =\n{\n')
    for s in string_table:
        f.write(four_space + '\"{0}\",\n'.format(s))
    f.write('};\n\n')

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
    ckl = list(core_kernel_list.values())
    for i in range(0, len(ckl)-1):
        hook_str = 'typedef ' \
                   + ckl[i].rtype \
                   + ' (*' + ckl[i].name + '_hook_type' \
                   + ')(\n'
        spaces = (len(hook_str)-2) * ' '
        arg_str = breakup(ckl[i].args, spaces)
        hook_str += arg_str \
                    + '\n' + spaces + ');\n\n'
        f.write(hook_str)

    hook_str = 'typedef ' \
               + ckl[-1].rtype \
               + ' (*' + ckl[-1].name + '_hook_type' \
               + ')(\n'
    spaces = (len(hook_str)-2) * ' '
    arg_str = breakup(ckl[-1].args, spaces)
    hook_str += arg_str \
                + '\n' + spaces + ');\n'
    f.write(hook_str)

def write_header(f, core_kernel_list):

    #Write header
    f.write(header_includes)

    #Write lookup tables
    write_lookup_tables(f, core_kernel_list)

    #Write plasma_init hook typedef
    f.write('typedef int (*plasma_init_hook_type)();\n\n')

    #Next, write function hook typedefs
    write_typedefs(f, core_kernel_list)

def parse_hdr(hdr_file_string):
    core_kernel_list = {}

    matches = rgx_obj.core_regex.finditer(hdr_file_string)

    for m in matches:

        if(m.group(2) not in core_kernel_list):
            core_kernel_list[m.group(2)] = core_class(m.group(1), m.group(2), m.group(3))

    return core_kernel_list
    
def write_autogen_cpp(f, core_kernel_list, root, mode_str):
    
    #Check for default case
    use_default_tag = root.find('use_default')
    
    if(use_default_tag != None):
        if(int(use_default_tag.text.strip()) == 1):
            use_default = 1
        else:
            use_default = 0 
    else:
        use_default = 0 
    
    #Obtain the top-level directory for PLASMA
    plasma_dir = root.find('plasma_dir').text.strip()
    
    #Write the constructor
    f.write( \
    '''#include "dare_base.h"

using namespace std;

/*This will obtain function pointers to hooks in the PLASMA library*/
dare_base::dare_base()
{{
    void (*fptr)();

    void *plasma_file;

    /* Set the default output flag */
    default_output = {default_output};

    /* Obtain a handle to the core_blas library */
    core_blas_file = dlopen(
                            "{prefix}libcoreblas.so", 
                            RTLD_LAZY
                           );

    if(core_blas_file == NULL) {{printf("core_blas_file null\\n"); exit(0);}}
    
    /* Obtain a handle to the plasma library */
    plasma_file = dlopen(
                        "{prefix}libplasma.so",
                        RTLD_LAZY
                        );

    if(plasma_file == NULL) {{printf("plasma_file null\\n"); exit(0);}}

    /* hook plasma_init() */
    fptr = (void (*)())dlsym(plasma_file, "plasma_init");
    if(fptr == NULL) {{printf("plasma_init() hook NULL\\n"); exit(0);}}
    plasma_init_ptr = fptr;
    '''.format(prefix = plasma_dir + '/lib/', default_output = use_default) \
    )

    for c in core_kernel_list.values():
        f.write( \
    '''
    /* hook {0}() */
    fptr = (void (*)())dlsym(core_blas_file, "{0}");
    if(fptr == NULL) {{printf("{0}() hook NULL\\n"); exit(0);}}
    core[{1}] = fptr;
    '''.format(c.name, c.name.upper()) \
               )

    f.write( \
    '''
    /*set atomic counters*/
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        core_count[i] = 0;
    }
    
    return;
}
''' \
           )

    #write the destructor. It must call kernel_to_file if default behavior
    #is invoked in trace mode
    f.write( \
    '''
dare_base::~dare_base()
{
    if(default_output)
    {
        kernel_to_file();
    }

    return;
}''' \
    )

def arg_strip(string, spaces):

    matches = list(rgx_obj.arg_regex.finditer(string))

    arg_str = ''
    
    for i in range(0, len(matches)):
        
        arg_str += (spaces + matches[i].group(2) + '\n')

    return arg_str

def function_call(c, arg_str, spaces):
    
    #Create the function call
    
    arg_spaces = ''

    if(c.rtype == 'void'):
        
        call = '{sp}(({name}_hook_type)profile.core[{upper}])(\n'\
        .format(sp = spaces, name = c.name, upper = c.name.upper())
        
        spaces = (len(call) + 2) * ' '
    
    else:
        
        call = '{sp}ret_val = (({name}_hook_type)profile.core[{upper}])(\n'\
        .format(sp = spaces, name = c.name, upper = c.name.upper())
        
        arg_spaces = (len(call) + 2) * ' '
        
    call += arg_strip(arg_str, arg_spaces) + arg_spaces + ');'

    return call

def gen_wrapper(c, config):
    
    if(config.wrap_above_func != ''):
        
        wrap_above = four_space + config.wrap_above_func + '('
        
        if(config.above_arg_list):
            
            for i in range(0, len(config.above_arg_list) - 1):
                
                d = config.above_arg_list[i]
                
                if(c.name in d):
                    
                    name = d[c.name]
                
                else:
                    
                    name = d['default']
                
                wrap_above += name + ', '

            d = config.above_arg_list[-1]
            
            if(c.name in d):
                
                name = d[c.name]
            else:
                
                name = d['default']
            
            wrap_above += name + ')'

        else:
            
            wrap_above += ')'
    else:
        
        wrap_above = ''
    
    if(config.wrap_below_func):
        
        wrap_below = four_space + config.wrap_below_func + '('
        
        if(config.below_arg_list):
            
            for i in range(0, len(config.below_arg_list) - 1):
                
                d = config.below_arg_list[i]
                
                if(c.name in d):
                    
                    name = d[c.name]
                
                else:
                   
                    name = d['default']
                
                wrap_below += name + ', '

            d = config.below_arg_list[-1]
            
            if(c.name in d):
                
                name = d[c.name]
            
            else:
                
                name = d['default']
            
            wrap_below += name + ')'
        
        else:
            
            wrap_below += ')'
    else:
        
        wrap_below = ''

    return wrap_class(wrap_above, wrap_below)

def profile_wrap(c, spaces):
        
    wrap_above = '''int count = profile.core_count[{name}]++;

    {sp}profile.time_kernel((unsigned long){name}, count)'''\
    .format(sp = spaces, name = c.name.upper())

    wrap_below = \
    '''
    {sp}profile.time_kernel((unsigned long){name}, count)'''\
    .format(sp = spaces, name = c.name.upper())

    wrap = wrap_class(wrap_above, wrap_below)

    return wrap

def trace_wrap_call(c, call, config):
    
    #If the default behavior is invoked
    if(config.use_default == 1):
        
        wrap = profile_wrap(c, four_space)
    
    #Customize the wrapper for each kernel
    else:

        wrap = gen_wrapper(c, config)
        
    string = '\n{0};\n\n{1}\n{2};\n' \
             .format(wrap.above, call, wrap.below)

    return string

def autotune_wrap_call(c, call, root):

    wrap = profile_wrap(c, four_space)

    #Function call enclosed in default profile-class timing wrappers
    inner = '{0};\n\n{1}\n{2};\n' \
             .format(wrap.above, call, wrap.below)

    #Get the kernel fraction and stride
    kf_tag = root.find('kernel_fraction')

    if(kf_tag == None):
        
        print('kernel_fraction tag not found.')

        sys.exit()

    ratio = kf_tag.text.strip().split(':')

    kernel_run = int(ratio[0])

    kernel_stride = int(ratio[1])

    #Enclose "inner" within autotune conditional
    string = '''\
    int random_n = rand() % {stride} + 1;

    if(random_n <= {run})
    {{
        {inside_conditional}
    }}
    '''.format(stride = kernel_stride, \
               run = kernel_run, \
               inside_conditional = inner \
              )

    return string


def trace_header(config): 

    #Obtain the list of .h files for the tracing wrappers
    trace_h = root.find('trace_h').findall('h')

    start = '#include "profile.h"'

    between = ''
    
    #If it's a .cpp file, just include the header files
    if(config.above_filex == '.cpp' and config.below_filex == '.cpp'):
        
        between += '\n'
        
        for h in trace_h:
        
            between += '#include "{h_file}"\n'.format(h_file = h)

    #If it's a .c file, you have to declare the trace functions as extern
    if(config.above_filex == '.c' and config.below_filex == '.c'):
        
        between += '\n'
        
        between += 'extern "C" {decl};\n'.format(decl = config.above_decl)
        
        between += 'extern "C" {decl};\n'.format(decl = config.below_decl)

    end = 'extern class Profile profile;' + '\n\n' \
          + 'using namespace std;' + '\n\n'

    return start + '\n' + between + '\n' + end

def plasma_init_hook(root):

    tag = root.find('tile_size')

    tile_size = ''

    if(tag != None):
        
        tile_size = tag.text.strip()
    
    else:
        
        print('No tile size specified in config file')
        
        sys.exit()

    if(tile_size == 'stdin'):

        plasma_init_str = \
'''\
#include "profile.h"
#include <sstream>
#include <iostream>
#include <string>

extern class Profile profile;

using namespace std;

extern "C" int plasma_init()
{
    int ret_val;

    int tile_size;
    
    string input;
    
    string tag;
    
    stringstream ss;

    ret_val = ((plasma_init_hook_type)profile.plasma_init_ptr)();

    getline(cin, input);

    ss.str(input);

    ss >> tag;
    
    if(tag == "tile_size")
    {
        ss >> tile_size;
        
        plasma_set(PlasmaNb, tile_size);

        plasma_get(PlasmaNb, &tile_size);

        printf("Tile size successfully set to %d\\n", tile_size);
    }

    else
    {
        printf(
              "unrecognized or missing label on stdin.\\n"
              "should be: tile_size <value>\\n"
              );
    }

    return ret_val;
}

'''
    else:

        plasma_init_str = \
'''\
#include "profile.h"

extern class Profile profile;

using namespace std;

extern "C" int plasma_init()
{{
    int ret_val;

    int tile_size;

    ret_val = ((plasma_init_hook_type)profile.plasma_init_ptr)();

    plasma_set(PlasmaNb, {tile_size_arg});

    plasma_get(PlasmaNb, &tile_size);

    printf("Tile size successfully set to %d\\n", tile_size);

    return ret_val;
}}

'''.format(tile_size_arg = tile_size)
    
    return plasma_init_str

def write_hooks_cpp(f, core_kernel_list, root, mode_str):

    if(mode_str == 'trace'):
        
        print('trace mode')

        config = trace_config(root)

        f.write(trace_header(config))

    elif(mode_str == 'autotune'):

        print('autotune mode')

    #Captain! Put in the plasma_init() hook here
    f.write(plasma_init_hook(root))

    #Write all the extern "C" kernels. Same for both trace and autotune mode.
    for c in core_kernel_list.values():
        
        #The hook definition
        string = 'extern "C" {0} {1}(\n'.format(c.rtype, c.name)
        
        spaces = (len(string) - 2) * ' '
        
        arg_str = breakup(c.args, spaces)
        
        string += arg_str + '\n' + spaces + ')\n{\n'

        if(c.rtype != 'void'):
            
            #call = four_space + '{0} ret_val;\n\n'.format(c.rtype) + four_space + call
            string += four_space + '{data_type} ret_val;\n\n'.format(data_type = c.rtype)

        #The actual function call within the hook
        call = function_call(c, arg_str, four_space)

        #Wrap the call in trace wrappers
        if(mode_str == 'trace'):

            string += trace_wrap_call(c, call, config)

        elif(mode_str == 'autotune'):

            string += autotune_wrap_call(c, call, root)

        #Conclude the function body with the proper return statement and bracket
        if(c.rtype == 'void'):
            
            string += ('\n' + four_space + 'return;\n}\n\n')
        
        else:
            
            string += ('\n' + four_space + 'return ret_val;\n}\n\n')

        f.write(string)

def cmake_add_library(root):

    start = '''add_library(
                          profile_lib SHARED'''

    end =  '''
           hooks.cpp
           autogen.cpp
           profile.cpp
           dare_base.cpp
           )'''
    
    spaces = len('add_library') * ' '
    
    #Obtain the list of .c or .cpp files for the tracing wrappers
    trace_c_tag = root.find('trace_c')

    trace_files = ''

    if(trace_c_tag):
        
        trace_c = trace_c_tag.findall('c')
        
        for f in trace_c:
            
            trace_files += spaces + f.text.strip() + '\n'

    call = start + '\n' + trace_files + spaces + end

    return call

def include_directories(root):
    
    #Obtain the top-level directory for PLASMA
    plasma_dir_tag = root.find('plasma_dir')

    if(plasma_dir_tag != None):

        plasma_dir = plasma_dir_tag.text.strip()

        #Obtain the include directories for PLASMA
        include_dirs = root.find('include_dirs').findall('dir')

        start = 'include_directories(' + '\n'
        
        spaces = (len(start)-2) * ' '
        
        end = ')'
        
        between = spaces + plasma_dir + '/include' + '\n'
        
        if(include_dirs != None):
            
            for d in include_dirs:
             
                between += spaces + d.text.strip() + '\n'

    return start + between + spaces + end

def write_cmake_lists(cmake_lists, root):
    

    #Open files containing core_blas declarations
    plasma_dir = root.find('plasma_dir').text.strip()

    cmake_lists.write(
    """set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
    set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)
        
    {include_dirs}

    project(optimize C CXX)

    {add_library}

    target_link_libraries(
                         profile_lib
                         {plasma_dir}/lib/libcoreblas.so
                         {plasma_dir}/lib/libplasma.so
                         -fopenmp
                         -flat_namespace
                         -g
                         )
    """.format(include_dirs = include_directories(root), \
        plasma_dir = plasma_dir, \
        add_library = cmake_add_library(root)))


#Start of main code

#Create an argument parser
parser = argparse.ArgumentParser(description='Create a CMakeLists.txt file and run CMake for PLASMA Tracer')

parser.add_argument('-c', '--config', help = 'Specify the XML config file', required = True)

tree = xml.parse(parser.parse_args().config)

root = tree.getroot()

#Open autogen_types.h
autogen_types_h = open('autogen_types.h', 'w')

#Create a regex object
rgx_obj = rgx_obj_class()

#Open files containing core_blas declarations
plasma_dir = root.find('plasma_dir').text.strip()

hdr_file_string = ''

p = Path(plasma_dir + '/include')

for f in p.iterdir():
    
    if(f.is_file() and rgx_obj.file_regex.fullmatch(f.name)):
        
        hdr_file_string += dump_file(str(f))

#Create kernel list
core_kernel_list = parse_hdr(hdr_file_string)

#Determine operating mode
mode_tag = root.find('mode')

if(mode_tag != None):

    mode_str = mode_tag.text.strip()

else:

    print("No mode tag found. Exiting.")
    
    sys.exit()

#All header files are concatenated into the same string. Header is written in one pass.
write_header(autogen_types_h, core_kernel_list)

#Close autogenerated header file
autogen_types_h.close()

#Create autogenerated cpp file
autogen_cpp = open('autogen.cpp', 'w')

write_autogen_cpp(autogen_cpp, core_kernel_list, root, mode_str)

autogen_cpp.close()

#Autogenerate the hooks.cpp file
hooks_cpp = open('hooks.cpp', 'w')

write_hooks_cpp(hooks_cpp, core_kernel_list, root, mode_str)

hooks_cpp.close()

#Autogenerate the CMakeLists.txt file
cmake_lists = open('CMakeLists.txt', 'w')

write_cmake_lists(cmake_lists, root)

cmake_lists.close()

subprocess.run(['cmake', '.'])

subprocess.run(['make'])

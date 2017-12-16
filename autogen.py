#For autotune mode, stdin arguments must be in the format:
#num_args kernel_fraction 10:100 tile_size 128 (for example)
#use_stdin must be indicated in the config file.
#all arguments that use stdin must say "stdin" as their text field
#in the config file
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

class core_class:
    
    def __init__(self, rtype, name, args):
        self.rtype = rtype
        self.name = name
        self.fake_data_class = ''
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
    
    if(use_default_tag == None):
        print('use default tag not found: exiting')
        sys.exit()

    use_default = int(use_default_tag.text.strip())
    
    if(use_default != 1 and use_default != 0):
        print('use default tag must be either 1 or 0: exiting')
        sys.exit()
    
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
    
    /* OpenMP returns 1 if this is called outside a parallel region */
    #pragma omp parallel
    {{
        num_threads = omp_get_max_threads();
    }}

    /* Set the default output flag */
    default_output = {default_output};

    /* Obtain a handle to the core_blas library */
    void *core_blas_file = dlopen(
                            "{prefix}libcoreblas.so", 
                            RTLD_LAZY
                           );

    if(core_blas_file == NULL) {{printf("core_blas_file null\\n"); exit(0);}}
    
    /* Obtain a handle to the plasma library */
    void *plasma_file = dlopen(
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
    /* allocate kernel_vec */
    kernel_vec = new vector<class kernel_node>*[num_threads];

    for(int i = 0; i < num_threads; ++i)
    {
        kernel_vec[i] = new vector<class kernel_node>();
    }

    /* allocate add_node */
    add_node = new int[num_threads];

    for(int i = 0; i < num_threads; ++i)
    {
        add_node[i] = 1;
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
    /* dump data to a file */
    /* these functions also clear the vector in case file is written to
    multiple times*/

    if(default_output)
    {
        dump_data();
    }

    /* free kernel_vec */
    for(int i = 0; i < num_threads; ++i)
    {
        kernel_vec[i]->clear();
        delete kernel_vec[i];
    }

    delete[] kernel_vec;

    /* free add_node */
    delete[] add_node;

    return;
}''' \
    )

def arg_strip(string, spaces):

    matches = list(rgx_obj.arg_regex.finditer(string))

    arg_str = ''
    
    for i in range(0, len(matches)):
        
        arg_str += (spaces + matches[i].group(2) + '\n')

    return arg_str

def function_call(c, arg_str, spaces, mode_str):
    
    #Create the function call
    
    arg_spaces = ''

    call = ''

    if(mode_str == 'trace'):

        if(c.rtype == 'void'):
        
            call = '{sp}(({name}_hook_type)profile.core[{upper}])(\n'\
            .format(sp = spaces, name = c.name, upper = c.name.upper())
        
            spaces = (len(call) + 2) * ' '
    
        else:
        
            call = '{sp}ret_val = (({name}_hook_type)profile.core[{upper}])(\n'\
            .format(sp = spaces, name = c.name, upper = c.name.upper())
        
            arg_spaces = (len(call) + 2) * ' '

    elif(mode_str == 'autotune'):

        if(c.rtype == 'void'):
        
            call = '{sp}(({name}_hook_type)autotune.core[{upper}])(\n'\
            .format(sp = spaces, name = c.name, upper = c.name.upper())
        
            spaces = (len(call) + 2) * ' '
    
        else:
        
            call = '{sp}ret_val = (({name}_hook_type)autotune.core[{upper}])(\n'\
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
        
    wrap_above = ''' 
    {sp}profile.track_kernel((unsigned long){name}, omp_get_wtime())'''\
    .format(sp = spaces, name = c.name.upper())

    wrap_below = \
    '''
    {sp}profile.track_kernel((unsigned long){name}, omp_get_wtime())'''\
    .format(sp = spaces, name = c.name.upper())

    wrap = wrap_class(wrap_above, wrap_below)

    return wrap

def trace_wrap_call(c, call, config):
    
    #If the default behavior is invoked
    if(config.use_default == 1):
        
        wrap = profile_wrap(c, four_space)
    
    #Customize the wrapper for each kernel
    #Captain!
    else:

        wrap = gen_wrapper(c, config)
        
    string = '\n{0};\n\n{1}\n{2};\n' \
             .format(wrap.above, call, wrap.below)

    return string

def autotune_wrap_call(c, call, root):

    wrap = profile_wrap(c, four_space)

    #Function call enclosed in default profile-class timing wrappers
    wrapped_call = '{0};\n\n{1}\n{2};\n' \
             .format(wrap.above, call, wrap.below)

    #Begin replacing things here
    #Enclose "wrapped_call" within autotune conditional
    string = '''\
    int random_n = rand() % autotune.kernel_stride + 1;

    if(random_n <= autotune.kernel_run)
    {{
        {inside_conditional}
    }}
    '''.format(inside_conditional = wrapped_call)

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

def stdin_version():
    
    string = \
'''#include "profile.h"
#include "autotune.h"
#include <sstream>
#include <iostream>
#include <string>

extern class Profile profile;

extern class Autotune autotune;

using namespace std;

/* Obtains variable number of arguments from stdin */
void parse_stdin()
{
    int num_args;

    string input;

    string tag;

    string kfrac;

    stringstream ss;

    getline(cin, input);

    ss.str(input);

    ss >> num_args;

    for(int i = 0; i < num_args; ++i)
    {
        ss >> tag;

        if(tag == "tile_size")
        {
            ss >> autotune.tile_size;
        }

        else if(tag == "kernel_fraction")
        {
            ss >> kfrac;

            int colon = kfrac.find(':');

            autotune.kernel_run = atoi(kfrac.substr(0, colon).c_str());

            autotune.kernel_stride = atoi(kfrac.substr(colon + 1).c_str());
        }

        else
        {
            printf("unrecognized stdin data tag\\n");

            exit(0);
        }
    }

    return;
}

extern "C" int plasma_init()
{
    int ret_val;

    int tile_size;
    
    ret_val = ((plasma_init_hook_type)profile.plasma_init_ptr)();

    /* get arguments from stdin. Not here if there aren't any */
    parse_stdin();

'''
    return string

def no_stdin_version():
    
    string = \
'''#include "profile.h"
#include "autotune.h"

extern class Profile profile;

extern class Autotune autotune;

using namespace std;

extern "C" int plasma_init()
{
    int ret_val;

    int tile_size;
    
    ret_val = ((plasma_init_hook_type)profile.plasma_init_ptr)();
'''

    return string

#Completes the last half of plasma_init() function
def last_half(root, core_kernel_list):

    tile_size = root.find('tile_size').text.strip()

    plasma_init_str = ''

    if(tile_size != 'stdin'):

        plasma_init_str = 'autotune.tile_size = {ts};\n'\
                           .format(ts = tile_size)

    kf = root.find('kernel_fraction').text.strip()

    if(kf != 'stdin'):

        ratio = kf.split(':')
    
        kernel_run = int(ratio[0])

        kernel_stride = int(ratio[1])

        plasma_init_str += \
        '''
        autotune.kernel_run = {krun};

        autotune.kernel_stride = {kstride};
        
        '''.format(krun = kernel_run, kstride = kernel_stride)

    plasma_init_str += \
    '''
    plasma_set(PlasmaNb, autotune.tile_size);

    plasma_get(PlasmaNb, &tile_size);

    printf(
          "tile_size: %d kernel_run: %d kernel_stride: %d\\n",
          tile_size, autotune.kernel_run, autotune.kernel_stride
          );

    {fake_init}

    return ret_val;
}}

'''.format(fake_init = init_fake_data(root, core_kernel_list))

    return plasma_init_str

#Populates "data" with all the fake data objects
def init_fake_data(root, core_kernel_list):
            
    kernel_list_tag = root.find('kernel_list')
    
    if(kernel_list_tag == None):
        
        return ''

    kernel_list_items = kernel_list_tag.findall('kernel')

    kernel_list = []

    #Obtain the list of items fake_data will be needed for
    for k in kernel_list_items:
        
        kernel_list.append(k.text.strip())
    
    #find the autotune fraction
    autotune_run_flag_tag = root.find('autotune_run_flag')

    #Autotune ratio determines when a real run or fake run will occur
    if(autotune_run_flag_tag == None):
    
        print('autotune_run_flag not found. Exiting.')
        
        sys.exit()
    
    autotune_run_flag = int(autotune_run_flag_tag.text.strip())

    #set autotune class's clip_size and max_window_size
    clip_size_tag = root.find('clip_size')

    if(clip_size_tag == None):
        
        print('clip_size not present. Exiting')

        sys.exit()

    clip_size = clip_size_tag.text.strip()

    max_window_size_tag = root.find('max_window_size')

    if(max_window_size_tag == None):

        print('max_window_size not present. Exiting')

        sys.exit()

    max_window_size = max_window_size_tag.text.strip()

    init_block = fake_data_classes(kernel_list, core_kernel_list)

    string = \
    '''
    autotune.clip_size = {clip_size};

    autotune.max_window_size = {max_window_size};

    autotune.autotune_run_flag = {autotune_run_flag};
    
    /* Populate each map with the kernels specified in the config file */
    for(int i = 0; i < autotune.num_threads; ++i)
    {{
        {init_block}
    }}
    '''.format(\
              init_block = init_block,\
              max_window_size = max_window_size,\
              clip_size = clip_size, \
              autotune_run_flag = autotune_run_flag\
              )

    return string

#Creates fake data classes
def fake_data_classes(kernel_list, core_kernel_list):
    
    string = ''

    for k in kernel_list:
        
        if(k not in core_kernel_list):
            
            print('unknown kernel_type detected. Update autogen.py. Exiting')

            sys.exit()

        elif(k == 'core_dpotrf'):
            
            print('creating fake_data for core_dpotrf...')

            string += init_fake_dpotrf_data(core_kernel_list)

    return string

#Create the constructor for fake_dpotrf_data initialization here
def init_fake_dpotrf_data(core_kernel_list):
    
    string = \
    '''
        autotune.data[i]->emplace(
                                 CORE_DPOTRF,
                                 new class fake_dpotrf_data(
                                                           autotune.clip_size,
                                                           autotune.tile_size,
                                                           autotune.max_window_size
                                                           )
                                 );
    '''

    core_kernel_list['core_dpotrf'].fake_data_class = 'fake_dpotrf_data'

    return string


def plasma_init_hook(root, core_kernel_list):

    stdin_tag = root.find('use_stdin')

    if(stdin_tag == None):
        
        print('use_stdin tag must be present')

        sys.exit()

        
    stdin_flag = int(stdin_tag.text.strip())

    if(stdin_flag == 1):
        
        plasma_init_str = stdin_version()

        plasma_init_str += last_half(root, core_kernel_list)


    elif(stdin_flag == 0):
        
        plasma_init_str = no_stdin_version()

        plasma_init_str += last_half(root, core_kernel_list)

    else:
        
        print('stdin_flag must be 1 or 0')

        sys.exit()

    return plasma_init_str

def write_hooks_cpp(f, core_kernel_list, root, mode_str):

    if(mode_str == 'trace'):
        
        print('trace mode')

        config = trace_config(root)

        f.write(trace_header(config))

    elif(mode_str == 'autotune'):

        print('autotune mode')

        f.write(plasma_init_hook(root, core_kernel_list))

    write_function_hooks(f, core_kernel_list, mode_str)

def hook_definition(c):
    
    #The hook definition
    string = 'extern "C" {0} {1}(\n'.format(c.rtype, c.name)
    
    spaces = (len(string) - 2) * ' '
    
    arg_str = breakup(c.args, spaces)
    
    string += arg_str + '\n' + spaces + ')\n{\n'
        
    if(c.rtype != 'void'):
        
        string += four_space + '{data_type} ret_val;\n\n'.format( \
                                                data_type = c.rtype)

    return string


def hook_trace_body(c, mode_str):
    
    arg_str = breakup(c.args, ' ')

    call = function_call(c, arg_str, four_space, mode_str)

    string = trace_wrap_call(c, call, config)
    
    #return statement and bracket
    if(c.rtype == 'void'):
        
        string += ('\n' + four_space + 'return;\n}\n\n')
    
    else:
        
        string += ('\n' + four_space + 'return ret_val;\n}\n\n')

    return string

def fake_data_run(c):
    
    string = ''

    if(c.name == 'core_dpotrf'):
        
        string = \
        '''
            profile.track_kernel({cname}, omp_get_wtime());
            int ret_val = core_dpotrf(
                    PlasmaLower,
                    ptr->get_tile_size(),
                    ptr->tile(),
                    ptr->get_tile_size()
                    );

            profile.track_kernel({cname}, omp_get_wtime());
            ptr->append_time(profile.last_kernel_time());
        '''.format(cname = c.name.upper())

    else:

        print('instructions to run \"{cname}\" with fake_data not found')

        print('check \"fake_data_run\" in autogen.py. Exiting')

        sys.exit()

    return string

def fake_data_busy_wait(c):

    string = ''
    
    if(c.name == 'core_dpotrf'):
        
        string = \
        '''
            double t = ptr->tile_time();
            profile.track_kernel({cname}, omp_get_wtime());
            ptr->busy_wait(t);
            profile.track_kernel({cname}, omp_get_wtime());
        '''.format(cname = c.name.upper())

    else:

        print('instructions to run \"{cname}\" with fake_data not found')

        print('check \"fake_data_run\" in autogen.py. Exiting')

        sys.exit()

    return string

def fake_data_framework(c):
    
    string = '''\
    int random_n = rand() % autotune.kernel_stride + 1;

    if(random_n <= autotune.kernel_run)
    {{
        int thread_num = omp_get_thread_num();

        {fake_data_type} *ptr = 
        (class {fake_data_type}*)((*autotune.data[thread_num])[{cname}]);

        if(ptr->tile_times_empty())
        {{
            {run}
        }}

        else if(ptr->clip_empty())
        {{
            {busy_wait}
        }}

        else
        {{
            if(++autotune.iterations[thread_num][{cname}] == 
               autotune.autotune_run_flag)
            {{
                autotune.iterations[thread_num][{cname}] = -1;

                {run}
            }}

            else
            {{
                {busy_wait}
            }}
        }}
    }}

    return PlasmaSuccess;
}}
    '''.format(
              fake_data_type = c.fake_data_class,\
              cname = c.name.upper(),\
              run = fake_data_run(c),\
              busy_wait = fake_data_busy_wait(c)\
              )

    return string
    
    

def hook_autotune_body(c, mode_str):

    arg_str = breakup(c.args, ' ')

    string = ''
    
    #Does this kernel need to access fake data or not?
    if(c.fake_data_class != ''):

        string += fake_data_framework(c)

    else:

        call = function_call(c, arg_str, four_space, mode_str)
    
        string += autotune_wrap_call(c, call, root)
        
        if(c.rtype == 'void'):
            
            string += ('\n' + four_space + 'return;\n}\n\n')
        
        else:
            
            string += ('\n' + four_space + 'return ret_val;\n}\n\n')

    return string

def write_function_hooks(f, core_kernel_list, mode_str):

    #Write all the extern "C" kernels. Same for both trace and autotune mode.
    for c in core_kernel_list.values():
        
        string = hook_definition(c)

        #Wrap the call in trace wrappers
        if(mode_str == 'trace'):

            string += hook_trace_body(c, mode_str)

        elif(mode_str == 'autotune'):

            string += hook_autotune_body(c, mode_str)

        f.write(string)

def cmake_add_library(root):

    use_default_tag = root.find('use_default')
    if(use_default_tag != None):
        if(int(use_default_tag.text.strip()) == 1):
            use_default = 1
        else:
            use_default = 0
    else:
        use_default = 0

    start = '''add_library(
                          profile_lib SHARED'''

    end =  '''
           hooks.cpp
           autogen.cpp
           profile.cpp
           autotune.cpp
           dare_base.cpp
           fake_data_test/fake_data.cpp
           )'''
    
    spaces = len('add_library') * ' '
    
    trace_files = ''

    if(use_default == 0):

        #Obtain the list of .c or .cpp files for the tracing wrappers
        trace_c_tag = root.find('trace_c')

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

    cpp_compiler = root.find('cpp_compiler').text.strip()

    c_compiler = root.find('c_compiler').text.strip()

    cmake_lists.write(
    """set(CMAKE_CXX_COMPILER {cpp})
    set(CMAKE_C_COMPILER {c})
        
    {include_dirs}

    project(optimize C CXX)

    {add_library}

    target_link_libraries(
                         profile_lib
                         {plasma_dir}/lib/libcoreblas.so
                         {plasma_dir}/lib/libplasma.so
                         -fopenmp
                         )
    """.format(include_dirs = include_directories(root), \
        plasma_dir = plasma_dir, \
        add_library = cmake_add_library(root), \
        c = c_compiler, \
        cpp = cpp_compiler))


#Start of main code

#Create an argument parser
parser = argparse.ArgumentParser(description='Create a CMakeLists.txt file and run CMake for PLASMA Tracer')

parser.add_argument('-c', '--config', \
                    help = 'Specify the XML config file', \
                    required = True)

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

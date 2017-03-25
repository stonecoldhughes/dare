import xml.etree.ElementTree as xml
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

#Each element of the arg list contains 'None' or a dictionary that tells the value of
#the positional argument for the above or below wrapper depending on the core kernel
#in question
class config_class:
    def __init__(self, above_func, below_func, above_args, below_args):
        self.wrap_above_func = above_func
        self.wrap_below_func = below_func
        self.below_arg_list = below_args
        self.above_arg_list = above_args

def list_args(args, root):
    #Each configurable arg has a set of possible choices it could be.
    #A dictionary will relate kernel to choice for a particular arg. This dict
    #Will be in a list that maintains the same positional order of the args specified in
    #The file
    arg_list = []
    
    for arg in args:
        
        if(arg.get('configurable') == 'True'):
            
            arg_map = dict()
            #Find the list of choices for this arg and create a dict out of it
            arg_element = root.find(arg.text.strip())

            if(arg_element):

                pairs = arg_element.findall('pair')

                for pair in pairs:
                    val_str = pair.find('value').text.strip()
                    if(arg.get('string') == 'True'):
                        val_str = '\"' + val_str + '\"'
                    
                    arg_map[pair.find('key').text.strip()] = val_str
                        

        else:
            arg_map = None

        arg_list.append(arg_map)
    
    return arg_list

def parse_config(cmd_args):

    #If an XML file was specified as the command line "wrapper" option...
    if(cmd_args.wrapper != 'time_kernel'):
        
        tree = xml.parse(cmd_args.wrapper)

        root = tree.getroot()

        wrap_below_func = root.find('wrap_below_func').text.strip()
        wrap_above_func = root.find('wrap_above_func').text.strip()
        wrap_above_args = root.find('wrap_above_args')
        wrap_below_args = root.find('wrap_below_args')

        below_arg_list = list_args(wrap_below_args.findall('arg'), root)
        above_arg_list = list_args(wrap_above_args.findall('arg'), root)

        c = config_class(wrap_above_func, wrap_below_func, above_arg_list, below_arg_list)
        
    else:
        c = config_class('', '', [], [])

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
    #Captain! Is this bad practice?
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

    #Next, write function hook typedefs
    write_typedefs(f, core_kernel_list)

def parse_hdr(hdr_file_string, cmd_args):
    core_kernel_list = {}

    matches = rgx_obj.core_regex.finditer(hdr_file_string)

    for m in matches:

        #core_kernel_list.append(core_class(m.group(1), m.group(2), m.group(3)))
        if(m.group(2) not in core_kernel_list):
            core_kernel_list[m.group(2)] = core_class(m.group(1), m.group(2), m.group(3))

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
    '''.format(cmd_args.dir + 'lib/') \
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
}''' \
           )

def arg_strip(string, spaces):
    matches = list(rgx_obj.arg_regex.finditer(string))
    arg_str = ''
    for i in range(0, len(matches)):
        arg_str += (spaces + matches[i].group(2) + '\n')

    return arg_str

def function_call(c, arg_str):
    #Create the function call
    if(c.rtype == 'void'):
        call = four_space + '(({0}_hook_type)profile.core[{1}])(\n'.format(c.name, c.name.upper())
        spaces = (len(call) + 2) * ' '
    else:
        call = 'ret_val = (({0}_hook_type)profile.core[{1}])(\n'.format(c.name, c.name.upper())
        spaces = (len(call) + 2) * ' '
        call = four_space + '{0} ret_val;\n\n'.format(c.rtype) + four_space + call

    call += arg_strip(arg_str, spaces) + spaces + ');'

    return call

def gen_wrapper(c, config):
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

    return wrap_class(wrap_above, wrap_below)

def wrap_the_call(c, call, config):
    
    #If the default behavior is invoked
    if(config.wrap_above_func == '' and config.wrap_below_func == ''):
        wrap_above = \
        '''
    int count = profile.core_count[{0}]++;

    profile.time_kernel((unsigned long){0}, count)'''.format(c.name.upper())

        wrap_below = \
        '''
    profile.time_kernel((unsigned long){0}, count)'''.format(c.name.upper())

        wrap = wrap_class(wrap_above, wrap_below)

    #Customize the wrapper for each kernel
    else:
        wrap = gen_wrapper(c, config)
        
    string = '{{\n{0};\n{1}\n{2};\n' \
             .format(wrap.above, call, wrap.below)

    if(c.rtype == 'void'):
        string += ('\n' + four_space + 'return;\n}\n\n')
    else:
        string += ('\n' + four_space + 'return ret_val;\n}\n\n')

    return string

    
def write_hooks_cpp(f, core_kernel_list, config):
    #Write the top section
    f.write( \
    '''#include "profile.h"

extern class Profile profile;

using namespace std;

''' \
           )

    #Write all the extern "C" kernels
    for c in core_kernel_list.values():
        string = 'extern "C" {0} {1}(\n'.format(c.rtype, c.name)
        spaces = (len(string) - 2) * ' '
        arg_str = breakup(c.args, spaces)
        string += arg_str + '\n' + spaces + ')\n'

        call = function_call(c, arg_str)
        string += wrap_the_call(c, call, config)
        f.write(string) 

#Start of main code

#Create an argument parser
parser = argparse.ArgumentParser(description='Options for autogeneration')
parser.add_argument('-d', '--dir', required=True)
parser.add_argument('-w', '--wrapper', default='time_kernel')

cmd_args = parser.parse_args()

#Open autogen_types.h
autogen_types_h = open('autogen_types.h', 'w')

#Create a regex object
rgx_obj = rgx_obj_class()

#Open files containing core_blas declarations
hdr_file_string = ''
p = Path(cmd_args.dir + '/include')
for f in p.iterdir():
    if(f.is_file() and rgx_obj.file_regex.fullmatch(f.name)):
        hdr_file_string += dump_file(str(f))

#Create kernel list
core_kernel_list = parse_hdr(hdr_file_string, cmd_args)

config = parse_config(cmd_args)

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

write_hooks_cpp(hooks_cpp, core_kernel_list, config)

hooks_cpp.close()

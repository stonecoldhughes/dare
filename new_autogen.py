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

#Static strings
header_includes = '#include "mkl_cblas.h"\n' \
                  +'#include "plasma.h"\n' \
                  +'#include "mkl_lapacke.h"\n' \
                  +'\nusing namespace std;\n'

cpp_includes = '#include "profile.h"\n' \
               + '\nusing namesapce std;\n\n'

#Classes
class rgx_obj_class:
    
    def __init__(self):
        
        self.file_regex = re.compile(r'core_blas_\w\.h')
        
        self.core_regex = re.compile(
        
        r'\s*(\w*\n?)\s+(core_(?!omp)\w+)\s*\(([^;]*)\)')
        
        self.arg_regex = re.compile(r'(.*) \**(.*)')

class core_class:
    
    def __init__(self, rtype, name, args):
        
        self.rtype = rtype
        
        self.name = name
        
        self.fake_data_class = '' 

        #Only a member variable for testing purposes
        self.typed_arg_list = self.extract_typed_args(args)

        #Only a member variable for testing purposes
        self.untyped_arg_list = self.extract_untyped_args(self.typed_arg_list)
        
        #Only a member variable for testing purposes
        self.typedef_string = self.generate_typedef_string()

        #Only a member variable for testing purposes
        self.definition_string = self.generate_definition_string()
        
        #Only a member variable for testing purposes
        self.function_call_string = self.generate_function_call_string()

    def generate_typedef_string(self):
        
        string = ''

        return string

    def generate_definition_string(self):

        string = ''

        return string

    def generate_function_call_string(self):
        
        string = ''

        return string

    #create each line of the function as a list element properly spaced
    #call_string is the output of one of the generate_string functions above
    def listify_function(arg_list, call_string):
        
        f = []

        f.append(call_string)

        return f
    
    def print_lists(self):

        print('typed_arg_list for {cname}:'.format(cname = self.name))

        for typed_arg in self.typed_arg_list:

            print('arg: {arg}'.format(arg = typed_arg))

        print('untyped_arg_list for {cname}'.format(cname = self.name))

        for untyped_arg in self.untyped_arg_list:
            
            print('arg: {arg}'.format(arg = untyped_arg))

        return

    #return a list of args with their data-types still attached
    def extract_untyped_args(self, arg_list):
        
        stripped = []

        for arg in arg_list:

            match = rgx_obj.arg_regex.fullmatch(arg)

            if(match == None):
                
                print('unrecognized pattern in function arguments. Exiting.')

                sys.exit()
            
            stripped.append(match.group(2).strip())

        return stripped
            

    #return a list of args without data types or dereference operators attached
    def extract_typed_args(self, args):

        raw_arg_list = args.split(',') 

        arg_list = []

        for arg in raw_arg_list:
            
            arg_list.append(arg.strip())

        return arg_list

#Methods
def dump_file(string):
    
    f = open(string, 'r')
    
    file_list = list(f)
    
    f.close()
    
    file_string = ''
    
    for line in file_list:
        
        file_string = file_string + ' ' + line.strip()
    
    return file_string

def parse_hdr(hdr_file_string):
    
    core_kernel_list = {}

    matches = rgx_obj.core_regex.finditer(hdr_file_string)

    for m in matches:

        if(m.group(2) not in core_kernel_list):
            
            core_kernel_list[m.group(2)] = core_class(m.group(1),\
                                                      m.group(2),\
                                                      m.group(3))

    return core_kernel_list

#Main code

#Create an argument parser
parser = argparse.ArgumentParser(description=\
            'Create an instance of the DARE runtime')

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

#Test code
for node in core_kernel_list.values():
   
   node.print_lists()

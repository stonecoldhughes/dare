import subprocess
import re
import argparse
import sys

def cmake_add_library(cmd_args):

    start = '''
add_library(
           profile_lib SHARED 
           hooks.cpp
           autogen.cpp
           profile.cpp '''
    end = ')'
    spaces = ' '*len('add_library')
    
    trace_files = ''
    if(cmd_args.trace_c):
        for f in cmd_args.trace_c:
            trace_files += spaces + f + '\n'

    call = start + '\n' + trace_files + spaces + end

    return call

parser = argparse.ArgumentParser(description='Create a CMakeLists.txt file and run CMake for PLASMA Tracer')

parser.add_argument('-d', '--dir', help = 'Specify the PLASMA directory', required = True)
parser.add_argument('-w', '--wrapper', help = 'Specify the XML wrapper config file', required = True)
parser.add_argument('-r', '--trace_h', help = 'Specify the directory containing the .h file for the two tracer functions')
parser.add_argument('-c', '--trace_c', help = 'Specify a list of .c/.cpp files to compile the two trace functions', nargs = '*')

cmd_args = parser.parse_args()

cmake_lists = open('CMakeLists.txt', 'w')

#Captain! Make the compiler executable location configurable
cmake_lists.write(
"""set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)
    
include_directories(
                   {0}/include
                   {1}
                   )

project(optimize C CXX)

add_custom_command(
                  OUTPUT autogen_types.h autogen.cpp hooks.cpp
                  COMMAND python autogen.py -d {0} -w {2}
                  DEPENDS {0}/include
                  )

{3}

target_link_libraries(
                     profile_lib
                     {0}/lib/libcoreblas.so
                     {0}/lib/libplasma.so
                     -fopenmp
                     -flat_namespace
                     -g
                     )
""".format(cmd_args.dir, cmd_args.trace_h, cmd_args.wrapper, cmake_add_library(cmd_args))
)

cmake_lists.close()

subprocess.run(['cmake', '.'])
subprocess.run(['make'])

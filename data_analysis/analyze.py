#The purpose of this file is to obtain data runs and then call
#another script to run a simple statistical analysis
import subprocess
import argparse
import sys
import os

#Globals
python_ex = '/Users/hhughe11/python/bin/python'

dare_dir = '/Users/hhughe11/research/dare'

test_dir = '/Users/hhughe11/research/dare/dare_autotune_test'

test_ex = './dpotrf_test.bin'

autogen_script = 'new_autogen.py'

this_dir = os.getcwd()

trace_config_xml = 'trace_config.xml'

autotune_config_xml = 'autotune_config.xml'

trace_test_output = 'trace_data.txt'

control_test_output = 'control_data.txt'

autotune_test_output = 'autotune_data.txt'

compare_script = 'compare.py'

def make_test_executable(config_xml):

    cmd = [args.python, autogen_script, '-c', config_xml]

    p = subprocess.Popen(cmd, cwd = dare_dir)

    p.communicate()

    #Build the test executable
    cmd = ['make']
        
    p = subprocess.Popen(cmd, cwd = test_dir)

    p.communicate()

    return

def run_executable(cmd, src, destination):
    
    p = subprocess.Popen(cmd, cwd = test_dir)

    p.communicate()

    #Save output to this directory
    os.rename(test_dir + '/' + src,\
              this_dir + '/' + destination)

    return

#Get command line arguments
parser = argparse.ArgumentParser()

parser.add_argument('-p', '--python',\
                    help = 'location of a python executable',\
                    default = python_ex)

parser.add_argument('--params', nargs = 5,\
                    help = 'n_low, n_add, iter, seed, tile_size',\
                    required = True)

args = parser.parse_args()

#Build the tracing library.
make_test_executable(trace_config_xml)

#Insert the executable before the params
args.params.insert(0, test_ex)

#Run a control test
run_executable(args.params, trace_test_output, control_test_output)

#Run the trace test 
run_executable(args.params, trace_test_output, trace_test_output)

#Build the autotune library
make_test_executable(autotune_config_xml)

tile_size = args.params[-1]

args.params[-1] = '-1'

stdin_args = '2 execution_ratio 2:2 tile_size {tile_size}'\
             .format(tile_size = tile_size).encode('utf-8')

#Run the autotune pass

p = subprocess.Popen(
                    args.params,\
                    cwd = test_dir,\
                    stdin = subprocess.PIPE,\
                    stdout = subprocess.PIPE)

out = p.communicate(stdin_args)

os.rename(test_dir + '/' + autotune_test_output,\
          this_dir + '/' + autotune_test_output)

#Output files are now ready for analysis
p = subprocess.Popen([args.python,\
                      compare_script,\
                      '-t',\
                      trace_test_output,\
                      '-c',\
                      control_test_output,\
                      '-a',\
                      autotune_test_output])

out = p.communicate()

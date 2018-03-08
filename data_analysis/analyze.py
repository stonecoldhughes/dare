#The purpose of this file is to obtain data runs and then call
#another script to run a simple statistical analysis
import xml.etree.ElementTree as xml
import subprocess
import argparse
import sys
import os

#Use autogen.py to build an executable
def make_test_executable(config, mode):

    if(mode == 'trace'):
        
        config_xml = config.trace_config_xml
    
    elif(mode == 'autotune'):
        
        config_xml = config.autotune_config_xml

    cmd = [config.python_ex, config.autogen_script, '-c', config_xml]

    p = subprocess.Popen(cmd, cwd = config.dare_dir)

    p.communicate()

    #Build the test executable
    cmd = ['make']
        
    p = subprocess.Popen(cmd, cwd = config.test_dir)

    p.communicate()

    return

def run_trace_executable(cmd, src, destination, iterations, config):
    
    for i in range(iterations):

        p = subprocess.Popen(cmd, cwd = config.test_dir)

        p.communicate()

    #Save output to this directory
    os.rename(config.test_dir + '/' + src,\
              this_dir + '/' + destination)

    return

def run_autotune_executable(args, stdin_args, iterations, config):

    for i in range(iterations):

        p = subprocess.Popen(
                            args.params,\
                            cwd = config.test_dir,\
                            stdin = subprocess.PIPE,\
                            stdout = subprocess.PIPE)

        out = p.communicate(stdin_args)

    os.rename(config.test_dir + '/' + config.autotune_test_output,\
              this_dir + '/' + config.autotune_test_output)

    return

def analyze_data(args, config):

    #Output files are now ready for analysis
    p = subprocess.Popen([config.python_ex,\
                          config.compare_script,\
                          '-t',\
                          config.trace_test_output,\
                          '-c',\
                          config.control_test_output,\
                          '-a',\
                          config.autotune_test_output])

    out = p.communicate()

    return

class config_class:
   
    def __init__(self):
        
        self.python_ex = ''
        self.dar_dir = ''
        self.test_dir = ''
        self.test_ex = ''
        self.autogen_script = ''
        self.trace_config_xml = ''
        self.autotune_config_xml = ''
        self.autotune_test_output = ''
        self.trace_test_output = ''
        self.control_test_output = ''
        self.control_script = ''


def parse_xml_config():

    tree = xml.parse(args.xml)

    root = tree.getroot()
    
    tag = root.find('python_ex')

    config = config_class()

    if(tag != None):
        
        config.python_ex = tag.text.strip()

    else:
        
        print('python_ex tag not present. Location of python executable')

        sys.exit()

    tag = root.find('dare_dir') 

    if(tag != None):
        
        config.dare_dir = tag.text.strip()

    else:
        
        print('dare_dir tag not present. Location of DARE directory')

        sys.exit()

    tag = root.find('test_dir')

    if(tag != None):
        
        config.test_dir = tag.text.strip()

    else:
        
        print('test_dir tag not present. Location of autotune and trace testing'\
              + ' directory.')

        sys.exit()

    tag = root.find('test_ex')

    if(tag != None):
        
        config.test_ex = tag.text.strip()

    else:
        
        print('test_ex tag not present. Name of executable under test.')

        sys.exit()

    tag = root.find('autogen_script')

    if(tag != None):
        
        config.autogen_script = tag.text.strip()

    else:
        
        print('autogen_script tag not present. Name of DARE autogenerator script')

        sys.exit()

    tag = root.find('trace_config_xml')

    if(tag != None):
        
        config.trace_config_xml = tag.text.strip()

    else:
        
        print('trace_config_xml tag not present. XML config file for DARE tracer')

        sys.exit()

    tag = root.find('autotune_config_xml')

    if(tag != None):
        
        config.autotune_config_xml = tag.text.strip()

    else:
        
        print('autotune_config_xml not present. XML config file for DARE autotuner')

        sys.exit()

    tag = root.find('trace_test_output')

    if(tag != None):
        
        config.trace_test_output = tag.text.strip()

    else:
        
        print('trace_test_output tag not present. DARE output file for trace run')

        sys.exit()

    tag = root.find('control_test_output')

    if(tag != None):
        
        config.control_test_output = tag.text.strip()

    else:
        
        print('control_test_output tag not present. DARE output file for control')

        sys.exit()

    tag = root.find('autotune_test_output')

    if(tag != None):
        
        config.autotune_test_output = tag.text.strip()

    else:
        
        print('autotune_test_output tag not present. DARE output file for autotune')

        sys.exit()

    tag = root.find('compare_script')

    if(tag != None):
        
        config.compare_script = tag.text.strip()

    else:

        print('compare_script tag not present. Python script to compare runs.')

        sys.exit()
    
    this_dir = os.getcwd()

    return config

#Main code

#Get command line arguments
parser = argparse.ArgumentParser()

parser.add_argument('--params', nargs = 8,\
                    help = 'function, m, m_add, n, n_add, iterations, seed, '\
                           + ' tile_size',\
                    required = True)

parser.add_argument('-e', '--execution_ratio',\
                    help = 'specify an execution_ratio for the autotuner',\
                    default = '2:2')

parser.add_argument('-x', '--xml',\
                    help = 'XML config file for settings',\
                    required = True)

args = parser.parse_args()

#Read the XML config file
config = parse_xml_config()

#Build the tracing library.
make_test_executable(config, 'trace')

#Insert the executable before the params
args.params.insert(0, config.test_ex)

#Run a control test
run_trace_executable(args.params,\
                     config.trace_test_output,\
                     config.control_test_output,\
                     2,\
                     config)

#Run the trace test 
run_trace_executable(args.params,\
                     config.trace_test_output,\
                     config.trace_test_output,\
                     2,
                     config)

#Build the autotune library
make_test_executable(config, 'autotune')

tile_size = args.params[-1]

args.params[-1] = '-1'

stdin_args = '2 execution_ratio {execution_ratio} tile_size {tile_size}'\
             .format(tile_size = tile_size,\
                     execution_ratio = args.execution_ratio).encode('utf-8')

#Run the autotune pass

run_autotune_executable(args, stdin_args, 2, config)

analyze_data(args, config)

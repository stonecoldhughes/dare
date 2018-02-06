#The purpose of this file is to conduct a simple statistical analysis
#of the outputs of test runs
import numpy
import argparse

#String templates
output_template = \
'''Trace Data:

{trace_stats}

Autotune Data:

{autotune_stats}

Control Data:

{control_stats}

Trace vs. Control:

{control_compare}

Trace vs. Autotune:

{autotune_compare}
'''

#Classes
#Represents basic statistical analysis of a single dataset
class stats_class:
    
    def __init__(self, function_name, times):
        
        self.function_name = function_name

        self.times = times

        self.mean = numpy.mean(times)

        self.std_dev = numpy.std(times)

        self.count = len(times)

        self.stats_template = \
'''
{function_name:>11s}: avg: {mean:<0.7f} std_dev: {std_dev:0.7f} count: {count:<5d}
'''
    
    def stats_string(self):
        
        return self.stats_template.format(function_name = self.function_name,\
                                          mean = self.mean,\
                                          std_dev = self.std_dev,\
                                          count = self.count)
        

#Represents statistical relation between two datasets
class comparison_class:
    
    def __init__(self, data_0, data_1):
        
        if(data_0.function_name != data_1.function_name):
            
            print('{n_0} != {n_1} - exiting'.format(n_0 = data_0.function_name,\
                            n_1 = data_1.function_name))

            sys.exit()

        self.function_name = data_0.function_name

        self.apd = numpy.absolute(data_0.mean - data_1.mean)\
                   / (data_0.mean + data_1.mean) * 100

        self.spd = numpy.absolute(data_0.std_dev - data_1.std_dev)\
                   / (data_0.std_dev + data_1.std_dev) * 100

        self.cpd = (data_0.count / data_1.count)

        self.stats_template = \
'''
{function:>11s}: avg diff: {apd:<3.3f}% std_dev diff: {spd:<3.3f}% ratio: {cpd:<3.3f}
'''
    
    def comparison_string(self):
        
        return self.stats_template.format(function = self.function_name,\
                                          apd = self.apd,\
                                          spd = self.spd,\
                                          cpd = self.cpd)

#Functions
#creates a dictionary of {function_name : raw_data object}
def generate_stats(lines):
    
    function_times = {}

    for line in lines:
        
        field = line.split(' ')

        function_name = field[0]

        time = float(field[3])

        if function_name not in function_times:
            
            function_times[function_name] = [time]

        else:
            
            function_times[function_name].append(time)

    #Analyze the data
    function_stats = {}

    for function_name in function_times:
        
        function_stats[function_name] = stats_class(function_name,\
                                                    function_times[function_name])

    return function_stats

#creates a dictionary of {function_name : compare_stats object}
def generate_comparison(function_stats_0, function_stats_1, keys):
   
    comparison = {}

    for key in keys:
        
        if(key not in function_stats_0 or key not in function_stats_1):
            
            print('{key} not present in both datasets.'.format(key = key))

            sys.exit()
        
        comparison[key] = comparison_class(function_stats_0[key],\
                                           function_stats_1[key])

    return comparison

def print_stats(function_stats):
    
    string = ''

    for stat in function_stats:
        
        string += function_stats[stat].stats_string()
    
    return string

def print_comparison(comparison):
    
    string = ''

    for stat in comparison:
        
        string += comparison[stat].comparison_string()

    return string

#Main code

#Parse command line arguments
parser = argparse.ArgumentParser()

parser.add_argument('-t', '--trace_file',\
                    help = 'trace file containing timing data',\
                    required = True)

parser.add_argument('-a', '--autotune_file',\
                    help = 'autotune file containing timing data',\
                    required = True)

parser.add_argument('-c', '--control_file',\
                    help = 'trace file used as experimental control',\
                    required = True)

parser.add_argument('-o', '--output',\
                    help = 'output file',\
                    default = 'output.txt')

args = parser.parse_args()

#Read input files
trace_data = open(args.trace_file, 'r').readlines()

autotune_data= open(args.autotune_file, 'r').readlines()

control_data = open(args.control_file, 'r').readlines()

#Extract data
trace_stats = generate_stats(trace_data[1:])

autotune_stats = generate_stats(autotune_data[1:])

control_stats = generate_stats(control_data[1:])

keys = set(trace_stats.keys())\
       .union(set(control_stats.keys()))\
       .union(set(autotune_stats.keys()))

#Compare the data
control_compare = generate_comparison(trace_stats, control_stats, keys)

autotune_compare = generate_comparison(trace_stats, autotune_stats, keys)

#Output the data
string = output_template.format(trace_stats = print_stats(trace_stats),\
                            autotune_stats = print_stats(autotune_stats),\
                            control_stats = print_stats(control_stats),\
                            control_compare = print_comparison(control_compare),\
                            autotune_compare = print_comparison(autotune_compare))

out = open(args.output, 'w')

out.write(string)

out.close()

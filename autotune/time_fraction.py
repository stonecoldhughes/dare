'''
This file determines how much faster each fractional run finishes all the points
than the largest run.
'''
import argparse
import sys
import re

class regex_class:

    def __init__(self):

        self.label_regex = re.compile(r'label:\s*(.*)')

        self.xy_regex = re.compile(r'x = (\d*) y = (\d*\.?\d*)')

#Start of main code
parser = argparse.ArgumentParser()

parser.add_argument('-d', '--data_file',\
                    help = 'data file to analyze',\
                    required = True)

parser.add_argument('-o', '--output',\
                    help = 'name of the output file',\
                    default = 'time_saved.txt')

args = parser.parse_args()

dfile = open(args.data_file, 'r')

lines = dfile.readlines()

dfile.close()

time_ratio = {}

label = '(not set)'

rgx = regex_class()

for line in lines:
    
    label_match = rgx.label_regex.match(line)

    if(label_match != None):
        
        label = label_match.group(1)

        if(label not in time_ratio):
            
            time_ratio[label] = 0

    else:
        
        xy_match = rgx.xy_regex.match(line)

        if(xy_match != None):

            y = float(xy_match.group(2))

            time_ratio[label] += y

largest = max(time_ratio.values())

for label in time_ratio:
    
    time_ratio[label] = largest / time_ratio[label]

outfile = open(args.output, 'w')

for label in time_ratio:
    
    string = '{label} run found the best tile size {factor} times faster\n'\
             .format(label = label, factor = time_ratio[label])

    outfile.write(string)

outfile.close()

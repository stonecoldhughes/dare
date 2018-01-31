'''
This script runs an executable iteratively based on a config file and obtains
a data point for a single run. Data points are associated with a line label.
Each run consumes a command line string and a stdin string. The format of the
command line string varies based on the executable, but the stdin string is
based off of the requirements of the DARE autotuning library and has the format:
<num_args> tile_size <size> execution_ratio <ratio>:<ratio>
'''

import argparse
import subprocess
import sys
import time
import matplotlib.pyplot as plt
import numpy as np
import re

iterations = 2

#Also have an "analyze_data" function where you do the gradients and such
#Plot the points. Assume each line has the same x values
def plot_point_data(xdata, ydata, line_labels):

    n_lines = len(xdata)
    
    legend_graph, legend_axis = plt.subplots()

    graph, axis = plt.subplots()

    ymax = -1

    ymin = sys.maxsize

    xmax = -1

    xmin = sys.maxsize
    
    #Plot each line on the same graph
    for i in range (0, n_lines):
        
        ylist = ydata[i]

        y = max(ylist)

        if(y > ymax):
            
            ymax = y
        
        y = min(ylist)
        
        if(y < ymin):

            ymin = y
    
        #xdata[i] is a list of (m, n) tuples. You only want "m"
        xlist = xdata[i]

        x = max(xlist)

        if(x > xmax):

            xmax = x

        x = min(xlist)

        if(x < xmin):

            xmin = x
        
        
        #Captain! Generate the label somehow. Make the first element a label
        #string and put that at the front of each set of line points?
        axis.plot(
                 xlist, \
                 ylist, \
                 linestyle = '-', \
                 marker = '.', \
                 )


        #Plot the legend in a seperate graph
        legend_axis.plot(
                        [], \
                        [], \
                        label = line_labels[i]
                        )

    #Put a buffer on the min and max
    xbuf = (xmax - xmin) / 5

    ybuf = (ymax - ymin) / 5

    axis.set_xlim(xmin - xbuf, xmax + xbuf)

    axis.set_ylim(ymin - ybuf, ymax + ybuf)

    axis.set_title("Performance Characteristics")

    axis.set_xlabel('m')

    axis.set_ylabel('time')

    #Show the legend in a seperate graph
    legend = legend_axis.legend(
                               loc = 'center', \
                               ncol = 2, \
                               fontsize = 'xx-large' \
                               )

    plt.show()

#Print out the data points you collected
def dump_point_data(xdata, ydata, line_labels):

    total_lines = len(xdata)

    f = open('output.txt', 'w')

    for i in range(0, total_lines):
        
        xlist = xdata[i]

        ylist = ydata[i]

        n_points = len(xlist)

        f.write('line label: {label} - best tile size: {tile_size}\n'\
               .format(label = line_labels[i],
                       tile_size = xlist[ylist.index(min(ylist))]))

        for j in range(0, n_points):

            f.write('x = {x} y = {y}\n'.format(x = xlist[j], \
                                             y = ylist[j]))

    f.close()

label_regex = re.compile(r'Label:\s*(.*)')

def run_process_once(cmd_args, stdin_args):
        
    p = subprocess.Popen(
                        cmd_args, \
                        stdin = subprocess.PIPE, \
                        stdout = subprocess.PIPE, \
                        )

    #Captain! Should t1 be here to avoid overhead?
    t1 = time.perf_counter()

    out = p.communicate(stdin_args)

    t2 = time.perf_counter()

    #print(out[0].decode('utf-8'))

    return ( t2 - t1 )
    

def run_process(cmd_args, stdin_args, iterations):

    total = 0.0

    #run once to ignore warm up values
    run_process_once(cmd_args, stdin_args)

    for i in range(iterations):

        total += run_process_once(cmd_args, stdin_args)

    return total / iterations

#Main code
parser = argparse.ArgumentParser()

parser.add_argument(
                   '-p', '--parameters',\
                   help = 'File containing executable parameters', \
                   required = True
                   )

args = parser.parse_args()

#at index "i", xdata contains x points for a curve,
#ydata contains y points, and line_labels contains the name of the curve
xdata = []

ydata = []

line_labels = []

#Enter the name of a file with command strings and stdin strings to run
#The program with
arg_file = open(args.parameters, 'r')

#Read the contents of the file into a data structure.
lines = arg_file.readlines()

i = 0

while(i < len(lines)):

    line = lines[i].strip()

    if(line):
        
        if(line.startswith(r'Label:')):
            
            print(line)

            match = label_regex.match(line)

            if(match == None):
                
                print('No label text found. Exiting')

                sys.exit()

            line_labels.append(match.group(1))
            
            #Create and insert lists for curve data to occupy
            xdata.append([])

            ydata.append([])

            xlist = xdata[-1]

            ylist = ydata[-1]
            

            i = i + 1

        elif(not line_labels):
            
            print('At least one line label must be present. Exiting')

            sys.exit()

        else:
        
            cmd_args = lines[ i ].split(' ')

            stdin_args = lines[ i + 1 ].encode('utf-8')

            #Run this a configurable number of times to get a better
            #average
            t = run_process(cmd_args, stdin_args, iterations)

            #Tuple contains 
            stdin_list = lines[ i + 1 ].split(' ')

            index = stdin_list.index('tile_size')

            tile_size = int(stdin_list[ index + 1 ])

            xlist.append(tile_size)

            ylist.append(t)

            i = i + 2

    else:
        
        i = i + 1

dump_point_data(xdata, ydata, line_labels)

plot_point_data(xdata, ydata, line_labels)

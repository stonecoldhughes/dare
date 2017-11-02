import argparse
import subprocess
import sys
import time
import matplotlib.pyplot as plt
import numpy as np

#Global variable indicating how many strings are needed to run dgemm_dpotrf.
#One for command line variables, one for stdin
n_dgemm_dpotrf_arg_strings = 2

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
        xlist = [t[0] for t in xdata[i]]

        x = max(xlist)

        if(x > xmax):

            xmax = x

        x = min(xlist)

        if(x < xmin):

            xmin = x
        
        
        print('line {i}:\n xlist: {x}\n ylist: {y}\n' + \
              'xmax: {xma} ymax: {yma}\n xmin: {xmi} ymin: {ymi}'.format(i = i, \
                                             x = xlist, \
                                             y = ylist, \
                                             xma = xmax, \
                                             yma = ymax, \
                                             xmi = xmin, \
                                             ymi = ymin))

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
    axis.set_xlim(xmin - 10, xmax + 10)

    axis.set_ylim(ymin - 10, ymax + 10)

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

    print('total graph lines: {count}'.format(count = total_lines))

    for i in range (0, total_lines):
        
        print('line!')

        xlist = xdata[i]

        ylist = ydata[i]

        n_points = len(xlist)

        print('line label: {label}'.format(label = line_labels[i]))

        for j in range(0, n_points):

            print('x = ({m},{n}) y = {y}'.format(m = xlist[j][0], \
                                                 n = xlist[j][1], \
                                                 y = ylist[j]
                                                ))

#Start of main code
parser = argparse.ArgumentParser()

parser.add_argument(
                   '-f', '--file',\
                   help = 'File containing executable parameters', \
                   required = True
                   )

args = parser.parse_args()

#Data sets to plot, 2 dimensional matrices. Possibly change to a list of tuples?
xdata = []

ydata = []

line_labels = []

print('This test requires a command line string and a stdin string\n')

print('Command line string format: m_low m_add n_low n_add iter seed\n')

print('Stdin string format: num_args tile_size <size> kernel_fraction' \
      + ' <ratio>:<ratio>')

#Enter the name of a file with command strings and stdin strings to run
#The program with
arg_file = open(args.file, 'r')

#Read the contents of the file into a data structure.
lines = arg_file.readlines()

#The first line of the file says how many data points are in each line
n_points = int(lines[0])

#Number of lines of text in the config file that describe a line in the graph
#2 lines are required to run the dgemm_dpotrf program
line_chunk = n_points * n_dgemm_dpotrf_arg_strings + 1

#Captain! Don't forget to get an overhead run
print('i in range(1, {len_lines}, {line_chunk})'.format(len_lines = len(lines), line_chunk = line_chunk))
for i in range (1, len(lines), line_chunk):
    
    print('at {i} in config file'.format(i = i))

    xdata.append([])

    ydata.append([])

    xlist = xdata[-1]

    ylist = ydata[-1]

    #The first line of every line_chunk is the label
    line_labels.append(lines[i])

    #Get the point data lines and run
    for j in range (i+1, i+line_chunk, 2):

        cmd_args = lines[j].split(' ')

        stdin_args = lines[j+1].encode('utf-8')
        
        t1 = time.perf_counter()

        p = subprocess.Popen(
                            cmd_args, \
                            stdin = subprocess.PIPE, \
                            stdout = subprocess.PIPE, \
                            )

        #Captain! Should t1 be here to avoid overhead?
        out = p.communicate(stdin_args)

        t2 = time.perf_counter()

        #tuple contains m, n
        xlist.append((int(cmd_args[1]), int(cmd_args[3])))

        ylist.append(t2 - t1)

        print(out[0].decode('utf-8'))

dump_point_data(xdata, ydata, line_labels)

plot_point_data(xdata, ydata, line_labels)

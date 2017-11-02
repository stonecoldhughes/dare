#Puts command line files on the same graph
import argparse
import matplotlib.pyplot as plt
import numpy as np
import sys

#Positions of data fields in the output table
gflops_pos = 3

n_pos = 5

nb_pos = 7

num_fields = 9

haswell_str = 'Haswell E5-2650 v3'

#Number of iterations at each problem size to average
num_iters = 3

def plot_point_data(xdata, ydata, line_labels, nb):

    n_lines = len(xdata)
    
    graph, axis = plt.subplots()
    
    legend_graph, legend_axis = plt.subplots()

    ymax = -1

    ymin = sys.maxsize

    xmax = -1

    xmin = sys.maxsize
    
    #Plot each line on the same graph
    for i in range (0, n_lines):
        
        #Get max values for each axis
        y = max(ydata[i])

        if(y > ymax):
            
            ymax = y
        
        y = min(ydata[i])
        
        if(y < ymin):

            ymin = y
    
        x = max(xdata[i])

        if(x > xmax):

            xmax = x

        x = min(xdata[i])

        if(x < xmin):

            xmin = x
        
        
        print('line {ii}:\n xlist: {xx}\n ylist: {yy}\n'.format(
                                                               ii = i, \
                                                               xx = xdata[i], \
                                                               yy = ydata[i]) + \
              'xmax: {xma} ymax: {yma}\n xmin: {xmi} ymin: {ymi}'.format(
                                             xma = xmax, \
                                             yma = ymax, \
                                             xmi = xmin, \
                                             ymi = ymin))

        axis.plot(
                 xdata[i], \
                 ydata[i], \
                 linestyle = '-', \
                 marker = '.', \
                 )
        
        legend_axis.plot(
                        [], \
                        [], \
                        label = line_labels[i]
                        )

    #Put a buffer on the min and max
    axis.set_xlim(xmin - 10, xmax + 10)

    axis.set_ylim(ymin - 10, ymax + 10)

    axis.set_title('Cholesky Performance - nb = {nb} - {chip}' \
                   .format(nb = nb, chip = haswell_str)
                  )

    axis.set_xlabel('n')

    axis.set_ylabel('gflops')

    #Show the legend in a seperate graph
    legend = legend_axis.legend(
                               loc = 'center', \
                               ncol = 2, \
                               fontsize = 'medium' \
                               )
    
    legend_axis.set_title('Legend - nb = {nb} - {chip}' \
                          .format(nb = nb, chip = haswell_str)
                         )

    plt.show()

def append_data(lines, xlist, ylist, num_iters):

    length = len(lines)

    #Account for trailing newline
    if(num_iters == 1):

        stride = 1

    else:
        
        stride = num_iters + 1

    for i in range(0, length, stride):

        #If there aren't num_iters lines of data left to average
        if(length - i - 1 < stride):

            continue
    
        total = 0

        print('iteration chunk:')
        for j in range(0, num_iters):
           
            data = lines[ i + j ].strip().split()

            print('adding {0} to the average...'.format(data[gflops_pos]))
            total += float(data[gflops_pos])

        avg = total / num_iters

        xlist.append(int(data[n_pos]))

        ylist.append(avg)
       
    
def append_data_old(line, xlist, ylist):

    data = line.strip().split()

    if(len(data) == num_fields):

        xlist.append(int(data[n_pos]))

        ylist.append(float(data[gflops_pos]))

#Start of main code

parser = argparse.ArgumentParser()

parser.add_argument(
                   '-i', '--input', \
                   help = 'Specify a list of input files', \
                   nargs = '+', \
                   type = argparse.FileType('r'), \
                   required = True
                   )

args = parser.parse_args()

file_list = args.input

xdata = []

ydata = []

line_labels = []

for f in file_list:
    
    #read empty line
    f.readline()

    #read title line
    title = f.readline()

    #read empty line
    f.readline()

    #read the rest of the lines
    lines = f.readlines()

    #create containers for the data points
    xlist = []

    ylist = []

    #extract nb
    first_line = lines[0].split()

    nb = first_line[nb_pos]
    
    #get info about the file's data
    line_labels.append(f.name + ', nb = ' + nb)


    #for line in lines:

        #append_data(line, xlist, ylist)

    #Captain! replace the function above to average the gflops
    append_data(lines, xlist, ylist, num_iters)

    xdata.append(xlist)

    ydata.append(ylist)

#Plot the data
plot_point_data(xdata, ydata, line_labels, nb)

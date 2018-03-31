'''
This script graphs the performance of Plasma applications under autotuning
'''
import xml.etree.ElementTree as xml
import argparse
import matplotlib.pyplot as plt
import sys
import re

#String templates
title_template = \
'''{function}
{cpu}
{cores} cores
{ram} RAM
{m}x{n} matrix
{iterations} iterations
'''

class config_class:
    
    def __init__(self, args):
        
        tree = xml.parse(args.xml_config)

        root = tree.getroot()

        tag = root.find('function')

        if(tag != None):
            
            self.function = tag.text.strip()

        else:
            
            print('function tag not present.' + \
                  'Name of the Plasma routine being tested.')

            sys.exit()

        tag = root.find('cores')

        if(tag != None):
            
            self.cores = tag.text.strip()

        else:
            
            print('cores tag not present. Number of cores the test was run on.')

            sys.exit()

        tag = root.find('cpu')

        if(tag != None):
            
            self.cpu = tag.text.strip()

        else:
            
            print('cpu tag not present. Make and model of the CPU the test ran on.')

            sys.exit()

        tag = root.find('iterations')

        if(tag != None):
            
            self.iterations = tag.text.strip()

        else:
            
            print('iterations tag not present. How many iterations to run')

            sys.exit()

        tag = root.find('m')

        if(tag != None):
            
            self.m = float(tag.text.strip())

        else:
            
            print('m tag not present. Rows of matrix')
            
            sys.exit()

        tag = root.find('n')

        if(tag != None):
            
            self.n = float(tag.text.strip())

        else:
            
            print('n tag not present. Columns of matrix')

            sys.exit()

        tag = root.find('ram')

        if(tag != None):
            
            self.ram = tag.text.strip()

        else:
            
            print('ram tag not present. How much memory on the system')

            sys.exit()


#Regexes
class regex_class:

    def __init__(self):

        self.label_regex = re.compile(r'label:\s*(.*)')

        self.best_regex = re.compile(r'best:\s*(\d*)')

        self.xy_regex = re.compile(r'x = (\d*) y = (\d*\.?\d*)')

def plot_point_data(xdata, ydata, line_labels, best_index, config):

    n_lines = len(xdata)
    
    legend_graph, legend_axis = plt.subplots()

    time_graph, time_axis = plt.subplots()

    gflops_graph, gflops_axis = plt.subplots()

    ymax = -1

    ymin = sys.maxsize

    xmax = -1

    xmin = sys.maxsize
    
    #Plot each line on the same graph
    for i in range (0, n_lines):
        
        #Find the max and min values
        time_ylist = ydata[i]

        gflops_ylist = gflops_sequence(time_ylist, config)

        y = max(time_ylist)

        if(y > ymax):
            
            ymax = y
        
        y = min(time_ylist)
        
        if(y < ymin):

            ymin = y
    
        xlist = xdata[i]

        x = max(xlist)

        if(x > xmax):

            xmax = x

        x = min(xlist)

        if(x < xmin):

            xmin = x
        
        #Plot data as time 
        time_axis.plot(
                 xlist, \
                 time_ylist, \
                 linestyle = '-', \
                 marker = '.', \
                 )

        #Mark the best point
        time_axis.plot(
                 xlist[best_index[i]],\
                 time_ylist[best_index[i]],\
                 'b*'\
                 )

        #Plot data in gflops
        gflops_axis.plot(
                        xlist,\
                        gflops_ylist,\
                        linestyle = '-',\
                        marker = '.'
                        )

        #Mark the best point
        gflops_axis.plot(
                        xlist[best_index[i]],\
                        gflops_ylist[best_index[i]],\
                        'b*'\
                        )


        #Plot the legend in a seperate graph
        legend_axis.plot(
                        [], \
                        [], \
                        label = line_labels[i]
                        )

    #Set the max and min axis limits
    xbuf = (xmax - xmin) / 5

    ybuf = (ymax - ymin) / 5

    time_axis.set_xlim(xmin - xbuf, xmax + xbuf)

    time_axis.set_ylim(ymin - ybuf, ymax + ybuf)

    #Set the max and min axis limits for the performance graph
    gflops_axis.set_xlim(xmin - xbuf, xmax + xbuf)

    #Set the title and axis labels
    time_axis.set_title('Execution_time')

    time_axis.set_xlabel('tile size')

    time_axis.set_ylabel('time (s)')

    gflops_axis.set_title('Performance')

    gflops_axis.set_xlabel('tile size')

    gflops_axis.set_ylabel('gflops')

    #Show the legend in a seperate graph
    legend = legend_axis.legend(
                               loc = 'lower center', \
                               ncol = 2, \
                               fontsize = 'xx-large' \
                               )

    legend_axis.set_title('Legend')

    legend_graph.text(0.5, 0.6, get_title(config),\
                     horizontalalignment = 'center',\
                     verticalalignment = 'center',\
                     fontsize = 20,\
                     bbox = dict(boxstyle = 'square',\
                                 facecolor = '#33ccff',\
                                 edgecolor = 'black'))

    plt.show()

def gflops_sequence(time_ylist, config):
    
    gflops_ylist = []

    for t in time_ylist:
        
        gflops_ylist.append(gflops(t, config))

    return gflops_ylist

def gflops(t, config):
    
    if(config.function == 'dgeqrf'):
        
        ops = 2 * config.m * config.n**2 - 2*config.n**3 / 3

    elif(config.function == 'dpotrf'):
        
        ops = config.n**3 / 3

    elif(config.function == 'dgetrf'):
        
        ops = config.n**3 * 2 / 3

    else:
        
        print('unrecognized function')

        sys.exit()

    g = ops / t / 1e9

    return g

def get_title(config):
    
    return title_template.format(function = config.function,\
                                 cpu = config.cpu,\
                                 cores = config.cores,\
                                 m = int(config.m),\
                                 n = int(config.n),\
                                 ram = config.ram,\
                                 iterations = config.iterations)

def find_best_index(xdata, ydata):
    
    best_index = []

    for dataset in ydata:

        best_index.append(dataset.index(min(dataset)))

    return best_index

#Main code
parser = argparse.ArgumentParser()

parser.add_argument('-d', '--data', \
                    help = 'file containing data to plot', \
                    required = True)

parser.add_argument('-x', '--xml-config', \
                    help = 'XML config file', \
                    required = True)

args = parser.parse_args()

arg_file = open(args.data, 'r')

lines = arg_file.readlines()

config = config_class(args)

rgx = regex_class()

#at index "i", xdata contains x points for a curve,
#ydata contains y points, and line_labels contains the name of the curve
xdata = []

ydata = []

line_labels = []

for line in lines:
    
    label_match = rgx.label_regex.match(line)

    best_match = rgx.best_regex.match(line)

    xy_match = rgx.xy_regex.match(line)

    if(label_match != None):
        
        line_labels.append(label_match.group(1))

        xdata.append([])

        ydata.append([])

    elif(best_match != None):
        
        pass

    elif(xy_match != None):
       
        xdata[-1].append(int(xy_match.group(1)))

        ydata[-1].append(float(xy_match.group(2)))

#best_index finds the index for the best point
best_index = find_best_index(xdata, ydata)

plot_point_data(xdata, ydata, line_labels, best_index, config)

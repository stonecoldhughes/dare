'''
This script graphs the performance of Plasma applications under autotuning
'''
import argparse
import matplotlib.pyplot as plt
import sys
import re

#Regexes
label_regex = re.compile(r'label:\s*(.*)')

best_regex = re.compile(r'best:\s*(\d*)')

xy_regex = re.compile(r'x = (\d*) y = (\d*\.?\d*)')

def plot_point_data(xdata, ydata, line_labels, best_index):

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

        #Mark the best point
        axis.plot(
                 xlist[best_index[i]],\
                 ylist[best_index[i]],\
                 'b*'\
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

def find_best_index(xdata, ydata):
    
    best_index = []

    for dataset in ydata:

        best_index.append(dataset.index(min(dataset)))

    return best_index

#Main code
parser = argparse.ArgumentParser()

parser.add_argument('-f', '--file', \
                    help = 'file containing data to plot', \
                    required = True)

args = parser.parse_args()

arg_file = open(args.file, 'r')

lines = arg_file.readlines()

#at index "i", xdata contains x points for a curve,
#ydata contains y points, and line_labels contains the name of the curve
xdata = []

ydata = []

line_labels = []

for line in lines:
    
    label_match = label_regex.match(line)

    best_match = best_regex.match(line)

    xy_match = xy_regex.match(line)

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

plot_point_data(xdata, ydata, line_labels, best_index)

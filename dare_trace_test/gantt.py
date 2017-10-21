#Captain! The length of the color map is used to determine how long the bars
#In the bar graph should be. This seems like a problem.
#Write a batch script to gather data on slurm
import matplotlib.pyplot as plt
import xml.etree.ElementTree as xml
import argparse
import decimal
import sys
from matplotlib import colors

#Defines a single line in the Gantt Chart
class kernel_node:
    
    def __init__(self):
        self.tuple_list = list()
        self.kernels = list()

    def add_block(self, start, end, kernel_string):
        self.tuple_list.append(start, end - start)
        self.kernels.append(kernel_string)

def read_color_config(f):

    tree = xml.parse(f)

    color_map = {}

    #Come on now. Have good practice and close the file
    f.close()

    root = tree.getroot()

    color_list_tag = root.find('color_list')

    if(color_list_tag == None):
        
        print('XML file does not contain a \'color_list\' tag. Exiting')

        sys.exit()

    color_pairs = color_list_tag.findall('pair')

    for pair in color_pairs:

        val_str = pair.find('value').text.strip()

        color_map[pair.find('key').text.strip()] = val_str
    
    return color_map


    

#Start of main code
#Get command line args
parser = argparse.ArgumentParser()

parser.add_argument(
                   '-i', '--input', \
                   help = 'Specify a list of input files', \
                   nargs = '+', \
                   type = argparse.FileType('r'), \
                   required = True
                   )

#Denotes colors for the kernels
parser.add_argument(
                   '-c', '--config', \
                   help = 'Specify the XML config file', \
                   type = argparse.FileType('r'), \
                   required = True
                   )

args = parser.parse_args()

file_list = args.input

#Contains kernel nodes
kernel_data = {}

#Associates kernel names with their color
color_map = read_color_config(args.config)

#Captain! Error checking
print(color_map)

for f in file_list:

    lines = f.read()
    f.close()
    lines = lines.split('\n')

    #Skip the title line
    del lines[0]

    #Determine the boundaries of the Gantt chart
    min_time = 0
    max_time = 0
    first = 1

    for line in lines:

        words = line.split() 
        if(len(words) > 1):

            #obtain raw data
            kernel_string = words[0]
            start = float(words[1])
            end = float(words[2])
            num_id = words[3]
            thread_id = words[4]

            #obtain limits for x-axis
            if(first == 1):
                first = 0
                min_time = start
            if(max_time < end):
                max_time = end
            if(min_time > start):
                min_time = start
            
            #create a new broken bar for a new thread_id
            if thread_id not in kernel_data:
                kernel_data[thread_id] = kernel_node()

            #create or update a broken bar for the thread_id
            kernel_data[thread_id].tuple_list.append((start, end-start))
            if(kernel_string in color_map):
                color_string = color_map[kernel_string]
            else:
                color_string = color_map['default']

            kernel_data[thread_id].kernels.append(color_string)

        
    #set x_limit and y_limit
    num_threads = len(kernel_data)
    graph, axis = plt.subplots()
    axis.set_xlim(min_time, max_time)
    axis.set_ylim(0, num_threads * 10)

    #iterate over data and plot it
    yticks = []
    yticklabels = []
    count = 0
    for key, val in kernel_data.items():
        index = count * 10 + 5
        axis.broken_barh(val.tuple_list, (index - 1, 2), facecolors = val.kernels) 
        yticks.append(index)
        yticklabels.append('Thread ' + ' {0}'.format(key))
        count = count + 1

    axis.set_yticks(yticks)
    axis.set_yticklabels(yticklabels)
    axis.set_title(f.name)

    #Graph the color legend
    legend_graph, legend_axis = plt.subplots()
    bar_lengths = [5] * len(color_map)
    legend_ypos = range(0, len(color_map)) 
    legend_labels = color_map.keys()
    legend_color = color_map.values()

    legend_axis.set_yticks(legend_ypos)
    legend_axis.set_yticklabels(legend_labels)
    legend_axis.set_title(f.name + ' Legend')

    legend_axis.barh(legend_ypos, bar_lengths, color = legend_color, align = 'center')

    #Don't show the graph, just see how long it takes to render
    plt.show()
    #Do I need this line?
    plt.close('all')

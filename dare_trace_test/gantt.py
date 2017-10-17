import matplotlib.pyplot as plt
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

#You must pass it a list or a file name
def run(arg, nature, show):
    #Contains kernel nodes
    kernel_data = dict()

    #Colors to use for Gantt boxes
    kernel_colors= list(colors.cnames.keys())

    #Associates kernel names with their color
    color_map = dict()

    if(nature == 'file'):
        f = open(arg)
        lines = f.read()
        f.close()
        lines = lines.split('\n')
    elif(nature == 'list'):
        lines = arg
    else:
        print('invalid arguments, exiting')
        sys.exit()
    
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
            
            #update kernel-to-color lookup table
            if(kernel_string not in color_map):
                if kernel_colors:
                    color_map[kernel_string] = kernel_colors.pop()
                else:
                    print('more kernels than colors!')
                    exit()

            #create a new broken bar for a new thread_id
            if thread_id not in kernel_data:
                kernel_data[thread_id] = kernel_node()

            #create or update a broken bar for the thread_id
            kernel_data[thread_id].tuple_list.append((start, end-start))
            kernel_data[thread_id].kernels.append(color_map[kernel_string])

        
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
    axis.set_title('Kernel Durations')
    
    #Graph the color legend
    legend_graph, legend_axis = plt.subplots()
    bar_lengths = [5] * len(color_map)
    legend_ypos = range(0, len(color_map)) 
    legend_labels = color_map.keys()
    legend_color = color_map.values()

    legend_axis.set_yticks(legend_ypos)
    legend_axis.set_yticklabels(legend_labels)
    legend_axis.set_title('Legend')

    legend_axis.barh(legend_ypos, bar_lengths, color = legend_color, align = 'center')

    #Don't show the graph, just see how long it takes to render
    if(show == True):
        plt.show()
    plt.close('all')

if(__name__ == '__main__'):
    run('kernel_data.txt', 'file', True)

#Script to test your research
import argparse
import subprocess
import sys
import time

def dump_point_data(xdata, ydata):

    total_lines = len(xdata)

    print('total graph lines: {count}'.format(count = total_lines))

    for i in range (0, total_lines):
        
        print('line!')

        xlist = xdata[i]

        ylist = ydata[i]

        n_points = len(xlist)

        for j in range(0, n_points):

            print('x = ({m},{n}) y = {y}'.format(m = xlist[j][0], \
                                                 n = xlist[j][1], \
                                                 y = ylist[j]
                                                ))

#Start of main code
parser = argparse.ArgumentParser()

parser.add_argument(
                   '-e', '--executable',\
                   help = 'Specify the executable name',\
                   required = True
                   )

parser.add_argument(
                   '-f', '--file',\
                   help = 'File containing executable parameters', \
                   required = True
                   )

args = parser.parse_args()

executable = './' +  args.executable

#Data sets to plot, 2 dimensional matrices. Possibly change to a list of tuples?
xdata = []

ydata = []

#Tests a dgemm followed by a cholesky
if(executable == './dgemm_dpotrf'):

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

    #Captain! Don't forget to get an overhead run
    for i in range (1, len(lines), n_points * 2):
        
        print("new line!")

        xdata.append([])

        ydata.append([])

        xlist = xdata[-1]

        ylist = ydata[-1]

        for j in range (0, n_points * 2, 2):

            cmd_args = lines[i+j].split(' ')

            stdin_args = lines[i+j+1].encode('utf-8')
            
            t1 = time.perf_counter()

            p = subprocess.Popen(
                                cmd_args, \
                                stdin = subprocess.PIPE, \
                                stdout = subprocess.PIPE, \
                                )

            #Should t1 be here to avoid overhead?
            out = p.communicate(stdin_args)

            t2 = time.perf_counter()

            #tuple contains m, n
            xlist.append((cmd_args[1], cmd_args[3]))

            ylist.append(t2 - t1)

            print(out[0].decode('utf-8'))

    dump_point_data(xdata, ydata)

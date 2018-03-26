'''
This is a convenience script to create the tile sizes to test
for dgemm points
'''
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-r', '--range',\
                    nargs = 3,\
                    type = int,\
                    help = 'start stop step values for tile sizes',\
                    required = True)

parser.add_argument('-f', '--file',\
                    nargs = '?',\
                    type = argparse.FileType('w'),\
                    help = 'name of the output file to create',\
                    default = 'tile_sizes_stdin.txt')

args = parser.parse_args()


for i in range(args.range[0], args.range[1], args.range[2]):
    
    args.file.write(str(i) + '\n')

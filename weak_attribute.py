import argparse
import re
from pathlib import Path

#Matches any string like "core_*.h but not core_omp stuff"
core_regex = re.compile(r'(\w+\s+core_(?!omp)\S+\(.*$)', re.MULTILINE)

repl = r'__attribute__ (( weak ))\n\1'

def find_and_replace(args):

    p = Path(args.path)

    for f_obj in p.iterdir():
        
        f_str = str(f_obj)

        f = open(f_str, 'r')

        contents = f.read()

        f.close()

        s = core_regex.sub(repl, contents)

        f = open(f_str, 'w')

        f.write(s)

        f.close()

def find_one(args):

    p = Path(args.path)

    f = open(str(p) + '/core_blas_c.h', 'r')

    s = f.read()

    print(s)

    print(core_regex.search(s))

#Start of main code

#Parse command line args
parser = argparse.ArgumentParser()

parser.add_argument('-p', '--path', \
                  help = 'Mark all core kernels as weak symbols',
                  required = True)

args = parser.parse_args()

find_and_replace(args)

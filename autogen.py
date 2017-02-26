import sys

print('Called autogen.py! argv[1] = {0}'.format(sys.argv[1]))

f = open('autogen_prelim.cpp', 'w')
f.close()
f = open('autogen_types_prelim.h', 'w')
f.close()

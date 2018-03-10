import xml.etree.ElementTree as xml
import argparse
import sys

#Configurable variables

class config_class:
    
    def __init__(self):
        
        self.function = ''
        self.m = 0
        self.m_add = 0
        self.n = 0
        self.n_add = 0
        self.iterations = 0
        self.seed = -1
        self.raw_executable = ''
        self.executable = ''
        self.execution_ratios = []
        self.line_labels = []
        self.tile_sizes = []
        self.do_raw_run = 0

def parse_xml_config(args):
    
    tree = xml.parse(args.xml_config)

    root = tree.getroot()

    config = config_class()

    tag = root.find('function')

    if(tag != None):
        
        config.function = tag.text.strip()

    else:
        
        print('function tag not present. Function to test')

        sys.exit()

    tag = root.find('m')

    if(tag != None):
        
        config.m = int(tag.text.strip())

    else:
        
        print('m tag not present. Rows of matrix')

        sys.exit()

    tag = root.find('m_add')

    if(tag != None):
        
        config.m_add = int(tag.text.strip())

    else:
        
        print('m_add tag not present. Randomizable range that m can increase')

        sys.exit()

    tag = root.find('n')
    
    if(tag != None):
        
        config.n = int(tag.text.strip())

    else:
        
        print('n tag not present. Number of columns of the matrix')

        sys.exit()

    tag = root.find('n_add')

    if(tag != None):
        
        config.n_add = int(tag.text.strip())

    else:
        
        print('n_add tag not present. Randomizable range that n can increase')

        sys.exit()
        
    tag = root.find('iterations')

    if(tag != None):
        
        config.iterations = int(tag.text.strip())
        
    else:
        
        print('iterations tag not present. Number of matrices of specified size' +\
              ' to test')

        sys.exit()

    tag = root.find('seed')

    if(tag != None):
        
        config.seed = int(tag.text.strip())
        
    else:
        
        print('seed tag not present. Seed for the random number generator')

        sys.exit()

    tag = root.find('raw_executable')

    if(tag != None):
        
        config.raw_executable = tag.text.strip()

    else:
        
        print('raw_exeuctable tag not present. Application binary unlinked with'+\
              ' DARE library')

        sys.exit()

    tag = root.find('executable')
    
    if(tag != None):
        
        config.executable = tag.text.strip()
        
    else:
        
        print('executable tag not present. Application binary linked with DARE'+\
              ' DARE library')

        sys.exit()

    tag = root.find('execution_ratios')

    if(tag != None):
        
        iter_tags = tag.findall('ratio')

        for t in iter_tags:
            
            config.execution_ratios.append(t.text.strip())

    else:
        
        print('execution_ratios tag not present. What fraction of core_functions'+\
               ' should be sampled')

        sys.exit()

    tag = root.find('line_labels')

    if(tag != None):
        
        iter_rags = tag.findall('line_label')

        for t in iter_tags:
            
            config.line_labels.append(t.text.strip())

    else:
        
        print('line_labels tag not present. The label for each line')

        sys.exit()

    tag = root.find('tile_sizes')

    if(tag != None):
        
        iter_tag = tag.findall('tile_size')

        for t in iter_tag:
            
            config.tile_sizes.append(int(t.text.strip()))

    else:
        
        print('tile_size tag not present. List of tile sizes to test')

        sys.exit()

    tag = root.find('do_raw_run')

    if(tag != None):
        
        config.do_raw_run = int(tag.text.strip())

    else:
        
        print('do_raw_run tag not present. 0 to skip raw run 1 to conduct one')

        sys.exit()

    return config

#String templates
stdin_template = \
'2 execution_ratio {execution_ratio} tile_size {tile_size}\n'

command_template = \
'{executable} {function} {m} {m_add} {n} {n_add} {iterations} {seed} {tile_size}\n'

label_template = \
'Label: {label}\n'

parser = argparse.ArgumentParser()

parser.add_argument(
                   '-f', '--file',\
                   help = 'name of output config file to generate', \
                   default = 'config.txt'
                   )

parser.add_argument(
                   '-x', '--xml_config',\
                   help = 'XML config file',\
                   required = True 
                   )

args = parser.parse_args()

config = parse_xml_config(args)

#Get the tile_sizes to test
output_config = open(args.file, 'w')

#Conduct a raw run
if(config.do_raw_run == 1):

    output_config.write(label_template.format(label = 'raw'))

    for tile_size in config.tile_sizes:
            
        string = command_template.format(executable = config.raw_executable,\
                                        n = config.n,\
                                        n_add = config.n_add,\
                                        m = config.m,\
                                        m_add = config.m_add,\
                                        iterations = config.iterations,\
                                        seed = config.seed,\
                                        tile_size = tile_size,\
                                        function = config.function)

        string += stdin_template.format(execution_ratio = 'overhead',\
                                        tile_size = tile_size)

        output_config.write(string)

#Conduct the autotuned runs
for pair in zip(config.line_labels, config.execution_ratios):
    
    output_config.write(label_template.format(label = pair[0]))

    for tile_size in config.tile_sizes:
        
        string = command_template.format(executable = config.executable,\
                                        m = config.m,\
                                        m_add = config.m_add,\
                                        n = config.n,\
                                        n_add = config.n_add,\
                                        iterations = config.iterations,\
                                        seed = config.seed,\
                                        tile_size = -1,\
                                        function = config.function)

        string += stdin_template.format(execution_ratio = pair[1],\
                                        tile_size = tile_size)

        output_config.write(string)

output_config.close()

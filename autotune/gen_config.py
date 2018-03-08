import argparse

#Configurable variables

function = 'dgeqrf'

m = 1000

m_add = 0

n = 1000

n_add = 0

iterations = 1

seed = -1 

raw_executable = './autotune_raw.bin'

executable = './autotune.bin'

execution_ratios = ['2:2', '1:2']

line_labels = ['full', 'half']

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
                   help = 'name of config file to generate', \
                   default = 'config.txt'
                   )

parser.add_argument(
                   '-t', '--tile_sizes',\
                   help = 'name of file containing a tile size on each line',\
                   required = True
                   )

args = parser.parse_args()

#Get the tile_sizes to test
tile_sizes = list(map(lambda x: int(x.strip()),\
                      open(args.tile_sizes, 'r').readlines()))

config_file = open(args.file, 'w')

#Conduct a raw run
config_file.write(label_template.format(label = 'raw'))

for tile_size in tile_sizes:
        
    string = command_template.format(executable = raw_executable,\
                                    n = n,\
                                    n_add = n_add,\
                                    m = m,\
                                    m_add = m_add,\
                                    iterations = iterations,\
                                    seed = seed,\
                                    tile_size = tile_size,\
                                    function = function)

    string += stdin_template.format(execution_ratio = 'overhead',\
                                    tile_size = tile_size)

    config_file.write(string)

#Conduct the autotuned runs
for pair in zip(line_labels, execution_ratios):
    
    config_file.write(label_template.format(label = pair[0]))

    for tile_size in tile_sizes:
        
        string = command_template.format(executable = executable,\
                                        m = m,\
                                        m_add = m_add,\
                                        n = n,\
                                        n_add = n_add,\
                                        iterations = iterations,\
                                        seed = seed,\
                                        tile_size = -1,\
                                        function = function)

        string += stdin_template.format(execution_ratio = pair[1],\
                                        tile_size = tile_size)

        config_file.write(string)

config_file.close()

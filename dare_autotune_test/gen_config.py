import argparse

#Configurable variables
tile_sizes = [64, 128, 256, 512]

n = 1000

n_add = 0

iterations = 1

seed = -1

executable = './dpotrf_test.bin'

execution_ratios = ['0:100', '50:100', '100:100']

line_labels = ['zero', 'half', 'full']

#String templates
stdin_template = \
'2 execution_ratio {execution_ratio} tile_size {tile_size}\n'

command_template = \
'{executable} {n} {n_add} {iterations} {seed}\n'

label_template = \
'Label: {label}\n'

parser = argparse.ArgumentParser()

parser.add_argument(
                   '-f', '--file',\
                   help = 'generated config file', \
                   default = 'config.txt'
                   )

args = parser.parse_args()

config_file = open(args.file, 'w')

for pair in zip(line_labels, execution_ratios):
    
    config_file.write(label_template.format(label = pair[0]))

    for tile_size in tile_sizes:
        
        string = command_template.format(executable = executable,\
                                        n = n,\
                                        n_add = n_add,\
                                        iterations = iterations,\
                                        seed = seed)

        string += stdin_template.format(execution_ratio = pair[1],\
                                        tile_size = tile_size)

        config_file.write(string)

config_file.close()

import argparse

#Configurable variables
tile_sizes = [32, 48, 64, 78, 92, 96, 110, 128, 147, 192, 225, 256]

n = 1000

n_add = 0

iterations = 20

seed = 5

overhead_executable = './dpotrf_test_overhead.bin'

executable = './dpotrf_test.bin'

execution_ratios = ['2:2', '1:2']

line_labels = ['full', 'half']

#String templates
stdin_template = \
'2 execution_ratio {execution_ratio} tile_size {tile_size}\n'

command_template = \
'{executable} {n} {n_add} {iterations} {seed} {nb}\n'

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

#Conduct a pure overhead run
config_file.write(label_template.format(label = 'raw'))

for tile_size in tile_sizes:
        
    string = command_template.format(executable = overhead_executable,\
                                    n = n,\
                                    n_add = n_add,\
                                    iterations = iterations,\
                                    seed = seed,\
                                    nb = tile_size)

    string += stdin_template.format(execution_ratio = 'overhead',\
                                    tile_size = tile_size)

    config_file.write(string)

#Conduct the autotuned runs
for pair in zip(line_labels, execution_ratios):
    
    config_file.write(label_template.format(label = pair[0]))

    for tile_size in tile_sizes:
        
        string = command_template.format(executable = executable,\
                                        n = n,\
                                        n_add = n_add,\
                                        iterations = iterations,\
                                        seed = seed,\
                                        nb = -1)

        string += stdin_template.format(execution_ratio = pair[1],\
                                        tile_size = tile_size)

        config_file.write(string)

config_file.close()

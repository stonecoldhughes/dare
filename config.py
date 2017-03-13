import re

def dump_file(string):
    f = open(string, 'r')
    file_list = list(f)
    f.close()
    file_string = ''
    for line in file_list:
        file_string = file_string + ' ' + line.strip()
    return file_string

file_string = dump_file('wrap_config.txt')

wrap_below_args_rgx = re.compile(r'\s*wrap_below_args:\s*{([^}]*)}')
wrap_above_args_rgx = re.compile(r'\s*wrap_above_args:\s*{([^}]*)}')
wrap_below_func_rgx = re.compile(r'\s*wrap_below_func:\s*{([^}]*)}')
wrap_above_func_rgx = re.compile(r'\s*wrap_above_func:\s*{([^}]*)}')

m_above_func = wrap_above_func_rgx.search(file_string)
m_below_func = wrap_below_func_rgx.search(file_string)
m_above_args = wrap_above_args_rgx.search(file_string)
m_below_args = wrap_below_args_rgx.search(file_string)

print('above_func: {0}\nbelow_func: {1}\nabove_args: {2}\nbelow_args: {3}\n' \
     .format(m_above_func.group(1), m_below_func.group(1), m_above_args.group(1), \
             m_below_args.group(1)))

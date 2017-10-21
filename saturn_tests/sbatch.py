#Generates batch scripts to run plasma/test on saturn

#Change these params to change content of the scripts
node = 'a00'

batch_fn = 'batch.sh'

omp_threads = [1, 5, 10, 20]

iters = 3

nb = [64, 128, 256, 512]

n = '300:350:25'

header = \
'''#!/bin/bash
#
#SBATCH --job-name=caffeine
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=2:00:00
#SBATCH --nodes=1
'''

plasma_test = 'srun ~/plasma-17.1/test/test dpotrf '

def write_batch(t, i):
        
        name = 't{0}_nb{1}.sh'.format(t, i)

        f = open(name, 'w')

        f.write(header)

        output = '#SBATCH --output=cholesky_t{0}_nb{1}.txt\n' \
                 .format(t, i)

        nodelist = '#SBATCH --nodelist={0}\n' \
                   .format(node)

        set_threads = '\nexport OMP_NUM_THREADS={0}\n\n' \
                      .format(t)

        run_str = plasma_test + '--n={} --iter={} --nb={}\n' \
                                .format(n, iters, i)

        f.write(output)

        f.write(nodelist)
        
        f.write(set_threads)

        f.write(run_str)

        f.close()
    
#Start of main code
f = open(batch_fn, 'w')

f.write(
'''
#!/bin/bash
'''
       )

for t in omp_threads:

    for i in nb:
        
        write_batch(t, i)

        f.write('sbatch t{0}_nb{1}.sh\n'.format(t, i))

f.close()

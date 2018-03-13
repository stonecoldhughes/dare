#!/bin/bash
#
#SBATCH --job-name=caffeine
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=2:00:00
#SBATCH --nodes=1
#SBATCH --output=cholesky_t10_nb512.txt
#SBATCH --nodelist=a00

export OMP_NUM_THREADS=10

srun ~/plasma-17.1/test/test dpotrf --n=300:350:25 --iter=3 --nb=512

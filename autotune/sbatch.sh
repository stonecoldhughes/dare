#!/bin/bash
#
#SBATCH --job-name=plasma_autotune
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=12:00:00
#SBATCH --time-min=12:00:00
#SBATCH --nodes=1
#SBATCH --output=sbatch_stdout.txt
#SBATCH --nodelist=a01
#SBATCH --partition=shared

export OMP_NUM_THREADS=20

srun python3 gather_data.py -p config.txt

#!/bin/bash
#
#SBATCH --job-name=plasma_analyze
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=12:00:00
#SBATCH --time-min=12:00:00
#SBATCH --nodes=1
#SBATCH --output=sbatch_stdout.txt
#SBATCH --nodelist=a00
#SBATCH --partition=shared

export OMP_NUM_THREADS=20

python3 analyze.py -x analysis_config.xml -e 1:16 --params dgeqrf \
25000 0 25000 0 3 -1 256


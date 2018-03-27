#!/bin/bash
#
#SBATCH --job-name=point_select
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=12:00:00
#SBATCH --time-min=12:00:00
#SBATCH --nodes=1
#SBATCH --output=sbatch_stdout.txt
#SBATCH --nodelist=b01
#SBATCH --partition=shared

export OMP_NUM_THREADS=20

./autotune_raw.bin dgemm 6000 0 6000 0 2 -1 -1 < tile_sizes_stdin.txt

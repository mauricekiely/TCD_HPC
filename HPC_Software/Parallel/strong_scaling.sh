#!/bin/bash

gcc-13 -o gs gs_parallel_2.c -fopenmp -lm -O3

for num_threads in {1..10}; do
    echo "Running with num_threads = $num_threads"
    ./gs $num_threads 250
done

#!/bin/bash

gcc-13 -o gs gs_parallel_2.c -fopenmp -lm 

for num_threads in {1..10}; do
    size=$(echo "scale=0; sqrt($num_threads * 250^2)" | bc)
    echo "Running with num_threads = $num_threads"
    ./gs $num_threads $size
done

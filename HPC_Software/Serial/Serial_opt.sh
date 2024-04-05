#!/bin/bash

gcc-13 -o gs gs_efficient_check.c -fopenmp -lm -O3

for num_threads in {1..10}; do
    size=$(echo "scale=0; sqrt($num_threads * 250^2)" | bc)
    echo "Running with size = $size"
    ./gs $size
done

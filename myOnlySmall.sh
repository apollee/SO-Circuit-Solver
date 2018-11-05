#!/bin/bash

N_THREADS=4

speedups=0
n_speedups=0
for FILENAME in $(ls inputs/random-x[^52]*.txt)
do
	./doTest.sh 4 $FILENAME
	speedup=$(grep "^4" ${FILENAME}.speedups.csv | grep -o -P "\d*\.\d*$")
	speedups=$(echo "scale=6; $speedups + $speedup" | bc)
	n_speedups=$(($n_speedups + 1))
done

echo "Average speedup time with 4 threads: $(echo "scale=5; $speedups/$n_speedups" | bc -l)"

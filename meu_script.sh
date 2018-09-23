#!/bin/bash
echo Script that prints the name of the file, the number of the lines in a file and the number of interconexions in the circuit.
echo

for f in $(ls inputs/*.txt)
do 
    echo filename: $f
    echo number of lines: $(cat $f | wc -l)
    echo number of interconexions in the circuit: $(cat $f | grep 'p' | wc -l) 
    echo
 
done




#!/bin/bash

NUMTASKS=$1
FILEPATH=$2

echo $1 $2

SEQSOLVERPATH='../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver'
PARSOLVERPATH='../CircuitRouter-ParSolver/CircuitRouter-ParSolver'
A='.speedup.csv'

$($SEQSOLVERPATH $FILEPATH)


#($PARSOLVERPATH -t $NUMTASKS $FILEPATH)

FILE="$FILEPATH$A"
echo $FILE

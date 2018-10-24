#!/bin/bash

OUTPUT_FILE="$FILEPATH$A"

COUNTER=1
NUM_TASKS=$1
FILE_PATH=$2

SEQSOLVER_PATH='../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver'
PARSOLVER_PATH='../CircuitRouter-ParSolver/CircuitRouter-ParSolver'

RES_ADD='.res'
OUTPUT_ADD='.speedup.csv'

RES_FILE="$FILE_PATH$RES_ADD"

($SEQSOLVER_PATH $FILE_PATH)
SEQSOLVER_TIME=$(grep 'Elapsed time' $RES_FILE | cut -b 19-26)

echo '#threads,exec_time,speedup' > "{$OUTPUT_FILE}"
echo "1S,$SEQSOLVER_TIME,1" >> "{$FILEPATH$A}"

#($PARSOLVER_PATH -t $NUM_TASKS $FILE_PATH)
#PARSOLVER_TIME=$(grep 'Elapsed time' $RES_FILE | cut -b 19-26)
#speedup=$(echo "scale=6; ${SEQSOLVER_TIME}/${PARSOLVER_TIME}" | bc)
echo '1,PARSOLVER_TIME,speedup' >> "{$FILEPATH$A}"

while [ $COUNTER -lt $NUM_TASKS ]; do
    let COUNTER=COUNTER+1
    ($SEQSOLVER_PATH $FILE_PATH)
    SEQSOLVER_TIME=$(grep 'Elapsed time' $RES_FILE | cut -b 19-26)
    #($PARSOLVER_PATH -t $NUM_TASKS $FILE_PATH)
    #PARSOLVER_TIME=$(grep 'Elapsed time' $RES_FILE | cut -b 19-26)
    #speedup=$(echo "scale=6; ${SEQSOLVER_TIME}/${PARSOLVER_TIME}" | bc)
    echo "$COUNTER,PARSOLVERTIME,speedup" >> "{$FILEPATH$A}"

done



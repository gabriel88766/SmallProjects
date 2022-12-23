#!/bin/bash

#execute ./fibonacci.sh number
#check if there is no args and exit with error
if [ $# -lt 1 ]
then 
    1>&2 echo "You must pass 1 positive number as argument"
    exit 1
fi

if [ $1 -eq 1 -o $1 -eq 2 ]
then
    echo "1"
fi

a=1
b=1
c=2
count=2
while [ $count -lt $1 ] 
do
    count=`expr $count + 1`;
    c=`expr $a + $b`
    a=$b
    b=$c 
done
echo $c

a=1
b=1
c=2
for i in $(seq 3 $1)
do
    count=$((count + 1))
    c=$((a + b))
    a=$b
    b=$c 
done
echo $c

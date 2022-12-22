#!/bin/bash

#echoes numbers from 1 to 10
#while
number=1
while [ $number -le 10 ]
do
    echo $number
    number=$(($number+1)) #another way, number=`expr $number+1` or $((number + 1))
done


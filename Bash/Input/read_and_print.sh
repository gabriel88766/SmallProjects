#!/bin/bash

#How to use = ./read_and_print.sh file
# < file pass file as input to a command
# > write in file
if [ $# -ne 1 ]
then
    2>&1 echo "too few or too many args. expected 1, have $#"
    exit 0
fi
string_test=$(< $1) #reading and storing file in string
string_test="$(printf "$string_test")"
#checking if there are differences
xxd <<< $string_test
xxd $1 > file2.ignore
if [[  file1.ignore == file2.ignore ]]
then
    echo "its equal"
else
    echo "its not equal"
fi

echo "$string_test" #right way to print a string
echo $string_test > file3.ignore #ignoring 0x0a of $string_test


#!/bin/bash

echo "Enter year"
read year

if [ $((year % 4)) -eq 0 ]
then
    if [ $((year % 100)) -ne 0 -o $((year % 400)) -eq 0 ]
    then
        echo "$year is a leap year"
    else
        echo "$year is not a leap year"
    fi
else
    echo "$year is not a leap year"
fi

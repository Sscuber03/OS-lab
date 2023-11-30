#!/bin/bash

echo "Enter a number"
read number

reverse=0

while [ $number -gt 0 ]
do
    remainder=$(( $number % 10 ))
    reverse=$(( $reverse * 10 + $remainder ))
    number=$(( $number / 10 ))
done

echo "Reverse of entered number is $reverse"
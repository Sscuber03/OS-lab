#!bin/bash

echo "Enter a number"
read number

factorial=1

while [ $number -gt 0 ]
do
    factorial=$(( $factorial * $number ))
    number=$(( $number - 1 ))
done

echo "Factorial of entered number is $factorial"
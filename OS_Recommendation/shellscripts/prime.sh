#!bin/bash

echo "Enter a number"
read number

isPrime=1

if [ $number -eq 0 -o $number -eq 1 ]
then
    isPrime=0
else
    for ((i=2; i<=$number/2; i++))
    do 
        if [ $(( $number % $i )) -eq 0 ]
        then
            isPrime=0
            break
        fi
    done
fi

if [ $isPrime -eq 1 ]
then
    echo "$number is a prime number"
else
    echo "$number is not a prime number"
fi

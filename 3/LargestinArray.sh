#!/bin/bash

read -p "Array Size>> " size

declare -a arr

for ((i=0; i<size; i++)); do
    read -p "arr[$i]: " arr[i]
done

big=${arr[0]}

for ((i=1; i<size; i++)); do
    if [ ${arr[i]} -ge $big ]; then
        big=${arr[i]}
    fi
done

echo "Largest Number in array: $big"

Output:
Array Size>> 5
arr[0]: 12
arr[1]: 7
arr[2]: 22
arr[3]: 5
arr[4]: 18

Largest Number in array: 22

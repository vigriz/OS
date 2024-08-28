#!/bin/bash

declare -a mat1
declare -a mat2
declare -a result

read -p "Enter m>> " m
read -p "Enter n>> " n

for((i=0;i<$m;i++))
do
	for((j=0;j<$n;j++))
	do
		read -p "mat1[$i,$j] : " ele
		mat1[$i,$j]=$ele
	done
done

for((i=0;i<$m;i++))
do
	for((j=0;j<$n;j++))
	do
		read -p "mat2[$i,$j] : " ele
		mat2[$i,$j]=$ele
		result[$i,$j]=$(( ${mat1[$i,$j]}+${mat2[$i,$j]} ))
	done
done

echo "Result Matrix: "
for((i=0;i<$m;i++))
do
	for((j=0;j<$n;j++))
	do
		echo -n "${result[$i,$j]} "
	done
	echo ""
done

Output:
Enter m>> 2
Enter n>> 2

mat1[0,0] : 1
mat1[0,1] : 2
mat1[1,0] : 3
mat1[1,1] : 4

mat2[0,0] : 5
mat2[0,1] : 6
mat2[1,0] : 7
mat2[1,1] : 8

Result Matrix: 
6 8 
10 12 

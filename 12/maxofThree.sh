#!/bin/bash

echo "Enter three numbers (space seperated): "
read a b c

echo -n "Largest Number: "
if [ $a -ge $b -a $b -ge $c ]
then
	echo "$a"
elif [ $b -ge $a -a $a -ge $c ]
then
	echo "$b"
else
	echo "$c"
fi
	
Output:
Enter three numbers (space separated): 
7 5 3
Largest Number: 7
Enter three numbers (space separated): 
4 9 6
Largest Number: 9
Enter three numbers (space separated): 
2 4 8
Largest Number: 8

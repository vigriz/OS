#!/bin/bash

read -p "Enter number>> " num
num=`echo $num`
numrev=`echo $num | rev`

if [ $num == $numrev ]
then
	echo "Palindrome"
else
	echo "Not a palindrome"
fi 


Output:
chmod +x check_palindrome.sh
./check_palindrome.sh
Enter number>> 12321
Palindrome
Enter number>> 12345
Not a palindrome
Enter number>> 7
Palindrome
Enter number>> 01210
Palindrome

#!/bin/bash

# Prompt the user to enter a string
read -p "Enter string>> " str1

# Reverse the entered string
str2=$(echo "$str1" | rev)

# Check if the original string is equal to the reversed string
if [ "$str1" == "$str2" ]; then
    echo "Palindrome"
else
    echo "Not a palindrome"
fi

Output1 :
Enter string>> level
Palindrome

Output2:
Enter string>> hello
Not a palindrome

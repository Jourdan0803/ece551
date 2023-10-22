#!/bin/bash

# Check if the user has provided two executable filenames as arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <executable1> <executable2>"
    exit 1
fi

# Check if the files exist and are executable
if [ ! -x "$1" ] || [ ! -x "$2" ]; then
    echo "One or both files do not exist or are not executable."
    exit 1
fi

for i in $(seq -100 200);
do
echo "This value is : $i"
# Run the first executable and save its output to a temporary file
./$1 $i > output1.txt

# Run the second executable and save its output to another temporary file
./$2 $i > output2.txt

# Compare the outputs
if diff -q output1.txt output2.txt &>/dev/null; then
    :
else
    echo "The outputs are different."
    diff output1.txt output2.txt
fi

# Remove the temporary output files
rm output1.txt output2.txt

done

i=",,,,"
echo "This value is : $i"
./$1 $i > output1.txt
./$2 $i > output2.txt

if diff -q output1.txt output2.txt &>/dev/null; then
    :
else
    echo "The outputs are different."
    diff output1.txt output2.txt
fi

rm output1.txt output2.txt


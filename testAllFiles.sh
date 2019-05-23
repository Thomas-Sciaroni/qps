#!/bin/bash

currentDirectory=$(pwd)
testDirectory=/$currentDirectory/binary

for file in $testDirectory/*
do
    ./qps "$file" >> results
done

awk ' NR % 2 == 1 { s+=$i } NR % 2 ==0 {t+=$i}END{print "Dijkstra Average: ", s/(NR/2) " Floodfill Average", t/(NR/2)}' results >> analysis

cat results

cat analysis


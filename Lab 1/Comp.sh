#!/bin/bash

g++ "Lab1_dop.cpp" -o Lab1.o -c
g++ "Source1.cpp" -o Source1.o -c
g++ -o main Lab1.o Source1.o
rm Lab1.o
rm Source1.o
./main
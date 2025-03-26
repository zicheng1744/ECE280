#!/bin/bash
g++ -g -Wall -o calc calc.cpp
g++ -g -Wall -o call call.cpp

./call < mysample1.in > mysample1.out
./call < mysample2.in > mysample2.out
./call < mysample3.in > mysample3.out
./calc < calc1.in > calc1.out
./calc < calc2.in > calc2.out
./calc < calc3.in > calc3.out
./calc < calc4.in > calc4.out

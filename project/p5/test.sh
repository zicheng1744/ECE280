#!/bin/bash
# You can use "chmod +x test.sh" to make the script executable
# You can use "./test.sh" to run the script
# You can use "#" to comment out any line

g++ -g -Wall -o calc calc.cpp
g++ -g -Wall -o call call.cpp

echo "*************Call 1 Memory Leak Test*************"
valgrind --leak-check=full ./call < mysample1.in > mysample1.localout
echo "                                                 "

diff mysample1.out mysample1.localout
echo "================Call Sample 1 End================"
echo "                                                 "

echo "*************Call 2 Memory Leak Test*************"
valgrind --leak-check=full ./call < mysample2.in > mysample2.localout
echo "                                                 "

diff mysample2.out mysample2.localout
echo "================Call Sample 2 End================"
echo "                                                 "

echo "*************Call 3 Memory Leak Test*************"
valgrind --leak-check=full ./call < mysample3.in > mysample3.localout
echo "                                                 "

diff mysample3.out mysample3.localout
echo "================Call Sample 3 End================"
echo "                                                 "

echo "*************Calc 1 Memory Leak Test*************"
valgrind --leak-check=full ./calc < calc1.in > calc1.localout
echo "                                                 "

diff calc1.out calc1.localout
echo "================Calc Sample 1 End================"
echo "                                                 "

echo "*************Calc 2 Memory Leak Test*************"
valgrind --leak-check=full ./calc < calc2.in > calc2.localout
echo "                                                 "

diff calc2.out calc2.localout
echo "================Calc Sample 2 End================"
echo "                                                 "

echo "*************Calc 3 Memory Leak Test*************"
valgrind --leak-check=full ./calc < calc3.in > calc3.localout
echo "                                                 "

diff calc3.out calc3.localout
echo "================Calc Sample 3 End================"
echo "                                                 "

echo "*************Calc 4 Memory Leak Test*************"
valgrind --leak-check=full ./calc < calc4.in > calc4.localout
echo "                                                 "

diff calc4.out calc4.localout
echo "================Calc Sample 4 End================"
echo "                                                 "

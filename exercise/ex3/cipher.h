#ifndef CIPHER_H
#define CIPHER_H

// Include your headers here
#include <string>
#include <cstring>
#include <iostream>

// Define the grids for encryption and decryption

const char uppercaseSquare[5][5] = {
    {'A', 'B', 'C', 'D', 'E'}, {'F', 'G', 'H', 'I', 'K'}, {'L', 'M', 'N', 'O', 'P'}, {'Q', 'R', 'S', 'T', 'U'}, {'V', 'W', 'X', 'Y', 'Z'}};

const char lowercaseSquare[5][5] = {
    {'a', 'b', 'c', 'd', 'e'}, {'f', 'g', 'h', 'i', 'k'}, {'l', 'm', 'n', 'o', 'p'}, {'q', 'r', 's', 't', 'u'}, {'v', 'w', 'x', 'y', 'z'}};

// Declare your functions here

void printHelp();
void read_command(int argc, char *argv[], int &command, int &outputMode);
std::string trim(const std::string &str);
void encrypt(int outputMode);
void en_compact(std::string message);
void en_sparse(std::string message);
void decrypt(int outputMode);
void de_compact(std::string message);
void de_sparse(std::string message);
std::string find_cipher_place(char c, const char square[5][5]);

#endif
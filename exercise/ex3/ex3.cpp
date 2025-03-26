#include "cipher.h"

using namespace std;

int main(int argc, char *argv[])
{
    int command = 0, outputMode = 0;
    read_command(argc, argv, command, outputMode);
    // cout << "Command: " << command << endl;
    // cout << "Output mode: " << outputMode << endl;
    switch (command)
    {
    case -1:
        break;
    case 0:
        printHelp();
        break;
    case 1:
        encrypt(outputMode);
        break;
    case 2:
        decrypt(outputMode);
        break;
    }
    return 0;
}

/*
testcase 1
input:
./ex3 -e
  Jj A aHh

testcase 2
input:
./ex3 --encrypt
  Jj A aHh

testcase 3
input:
./ex3 -d
      100200000111000211123223

testcase 4
input:
./ex3 -d -s
      100 200 000 111 000 211 123 223
*/
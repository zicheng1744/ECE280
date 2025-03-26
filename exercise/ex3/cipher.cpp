#include "cipher.h"
#include <iostream>

using namespace std;

void printHelp()
{
  cout << "Encrypt or decrypt a message using the Polybius Square cipher.\n"
       << "Usage: ./ex3 <command> [outputMode]\n"
       << "Commands:\n"
       << "\t-e, --encrypt\tEncrypt a message\n"
       << "\t-d, --decrypt\tDecrypt a message\n"
       << "Output modes:\n"
       << "\t-c, --compact\tProcess the message without spaces\n"
       << "\t-s, --sparse\tProcess the message with spaces" << endl;
}

// Implement other functions here

void read_command(int argc, char *argv[], int &command, int &outputMode)
{
  // cout << "argv[1]: " << argv[1] << endl;
  //  handling the case when no option is provided and when too many options are provided
  if (argc == 1)
  {
    cout << "No option!" << endl;
    command = -1;
    return;
  }
  else if (argc > 3)
  {
    cout << "Too many options!" << endl;
    command = -1;
    return;
  }

  // Since we have a valid number of options, we can now check the command
  if (!strcmp(argv[1], "-e") || !strcmp(argv[1], "--encrypt"))
  {
    // cout << strcmp(argv[1], "-e") << endl;
    command = 1;
    // cout << "1" << endl;
  }
  else if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--decrypt"))
  {
    command = 2;
  }
  else if ((!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) && argc == 2)
  {
    command = 0;
  }
  else
  {
    cout << "Invalid option!" << endl;
    command = -1;
  }

  // The output mode is optional, so we need to check if it is provided
  if (argc == 2)
  {
    outputMode = 0;
    return;
  }
  else
  {
    if (!strcmp(argv[2], "-c") || !strcmp(argv[2], "--compact"))
    {
      outputMode = 0;
    }
    else if (!strcmp(argv[2], "-s") || !strcmp(argv[2], "--sparse"))
    {
      outputMode = 1;
    }
    else
    {
      cout << "Invalid option!" << endl;
      command = -1;
    }
  }

  return;
}

string trim(const string &str)
{
  size_t first = str.find_first_not_of(' ');
  if (first == string::npos)
  {
    return "";
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

void encrypt(int outputMode)
{
  string raw_message;
  string pro_message;
  getline(cin, raw_message);
  pro_message = trim(raw_message);
  // if pro_message is empty, return
  if (pro_message == "")
  {
    cout << endl;
    return;
  }

  switch (outputMode)
  {
  case 0:
    en_compact(pro_message);
    break;
  case 1:
    en_sparse(pro_message);
    break;
  }
  return;
}

void en_compact(string message)
{
  string output;
  int length = message.length();
  for (int i = 0; i < length; i++)
  {
    if (message[i] == ' ')
    {
      output += "000";
    }
    else if (message[i] == 'j')
    {
      output += "100";
    }
    else if (message[i] == 'J')
    {
      output += "200";
    }
    else if (message[i] >= 'a' && message[i] <= 'z')
    {
      output += "2" + find_cipher_place(message[i], lowercaseSquare);
    }
    else if (message[i] >= 'A' && message[i] <= 'Z')
    {
      output += "1" + find_cipher_place(message[i], uppercaseSquare);
    }
  }
  cout << output << endl;
  return;
}

string find_cipher_place(char c, const char square[5][5])
{
  string output;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (c == square[i][j])
      {
        output += to_string(i + 1);
        output += to_string(j + 1);
        return output;
      }
    }
  }
  return output;
}

void en_sparse(string message)
{
  string output;
  int length = message.length();
  for (int i = 0; i < length; i++)
  {
    if (message[i] == ' ')
    {
      cout << "000 ";
    }
    else if (message[i] == 'j')
    {
      cout << "100 ";
    }
    else if (message[i] == 'J')
    {
      cout << "200 ";
    }
    else if (message[i] >= 'a' && message[i] <= 'z')
    {
      cout << "2" + find_cipher_place(message[i], lowercaseSquare) + " ";
    }
    else if (message[i] >= 'A' && message[i] <= 'Z')
    {
      cout << "1" + find_cipher_place(message[i], uppercaseSquare) + " ";
    }
    output += " ";
  }
  string final_output = trim(output);
  cout << final_output << endl;
  return;
}

void decrypt(int outputMode)
{
  string raw_message;
  string pro_message;
  getline(cin, raw_message);
  pro_message = trim(raw_message);
  // cout << "1" << endl;
  //  if pro_message is empty, return
  if (pro_message == "")
  {
    cout << endl;
    return;
  }

  switch (outputMode)
  {
  case 0:
    de_compact(pro_message);
    break;
  case 1:
    de_sparse(pro_message);
    break;
  }
  return;
}

void de_compact(string message)
{
  // cout << message << endl;
  string output;
  int length = message.length();
  for (int i = 0; i < length; i += 3)
  {
    if (message[i] == '0' && message[i + 1] == '0' && message[i + 2] == '0')
    {
      output += " ";
    }
    else if (message[i] == '1')
    {
      if (message[i + 1] == '0' && message[i + 2] == '0')
      {
        output += 'J';
      }
      else
      {
        output += uppercaseSquare[message[i + 1] - '0' - 1][message[i + 2] - '0' - 1];
      }
    }
    else if (message[i] == '2')
    {
      if (message[i + 1] == '0' && message[i + 2] == '0')
      {
        output += 'j';
      }
      else
      {
        output += lowercaseSquare[message[i + 1] - '0' - 1][message[i + 2] - '0' - 1];
      }
    }
    // cout << output << endl;
  }
  cout << output << endl;
  return;
}

void de_sparse(string message)
{
  string output;
  int length = message.length();
  for (int i = 0; i < length; i += 4)
  {
    if (message[i] == '0' && message[i + 1] == '0' && message[i + 2] == '0' && message[i + 3] == ' ')
    {
      output += " ";
    }
    else if (message[i] == '1')
    {
      if (message[i + 1] == '0' && message[i + 2] == '0' && message[i + 3] == ' ')
      {
        output += 'J';
      }
      else
      {
        output += uppercaseSquare[message[i + 1] - '0' - 1][message[i + 2] - '0' - 1];
      }
    }
    else if (message[i] == '2')
    {
      if (message[i + 1] == '0' && message[i + 2] == '0' && message[i + 3] == ' ')
      {
        output += 'j';
      }
      else
      {
        output += lowercaseSquare[message[i + 1] - '0' - 1][message[i + 2] - '0' - 1];
      }
    }
  }

  cout << output << endl;
  return;
}
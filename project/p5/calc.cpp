#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

void integer(Dlist<int> &stack, int n);
void add(Dlist<int> &stack);
void subtract(Dlist<int> &stack);
void multiply(Dlist<int> &stack);
void divide(Dlist<int> &stack);
void negateNum(Dlist<int> &stack);
void duplicate(Dlist<int> &stack);
void reverse(Dlist<int> &stack);
void print(Dlist<int> &stack);
void clear(Dlist<int> &stack);
void printAll(Dlist<int> &stack);
void quit(Dlist<int> &stack);
bool isValidIntegers(const string &token);

// Reverse-Polish Notation Calculator
int main()
{
    Dlist<int> stack;
    string input, token;

    // read input from the user by line
    while (getline(cin, input))
    {
        size_t start = 0, end = 0;
        // split the input string by space or tab
        while ((end = input.find_first_of(" \t", start)) != string::npos)
        {
            // get the token
            token = input.substr(start, end - start);
            start = end + 1;
            if (!token.empty())
            {
                if (token == "+")
                {
                    add(stack);
                }
                else if (token == "-")
                {
                    subtract(stack);
                }
                else if (token == "*")
                {
                    multiply(stack);
                }
                else if (token == "/")
                {
                    divide(stack);
                }
                else if (token == "n")
                {
                    negateNum(stack);
                }
                else if (token == "d")
                {
                    duplicate(stack);
                }
                else if (token == "r")
                {
                    reverse(stack);
                }
                else if (token == "p")
                {
                    print(stack);
                }
                else if (token == "c")
                {
                    clear(stack);
                }
                else if (token == "a")
                {
                    printAll(stack);
                }
                else if (token == "q")
                {
                    quit(stack);
                }
                else if (isValidIntegers(token))
                {
                    int n = stoi(token);
                    integer(stack, n);
                }
                else
                {
                    cout << "Bad input\n";
                }
            }
        }
        // get the last token
        token = input.substr(start);
        if (!token.empty())
        {
            if (token == "+")
            {
                add(stack);
            }
            else if (token == "-")
            {
                subtract(stack);
            }
            else if (token == "*")
            {
                multiply(stack);
            }
            else if (token == "/")
            {
                divide(stack);
            }
            else if (token == "n")
            {
                negateNum(stack);
            }
            else if (token == "d")
            {
                duplicate(stack);
            }
            else if (token == "r")
            {
                reverse(stack);
            }
            else if (token == "p")
            {
                print(stack);
            }
            else if (token == "c")
            {
                clear(stack);
            }
            else if (token == "a")
            {
                printAll(stack);
            }
            else if (token == "q")
            {
                quit(stack);
            }
            else if (isValidIntegers(token))
            {
                int n = stoi(token);
                integer(stack, n);
            }
            else
            {
                cout << "Bad input\n";
            }
        }
    }
    return 0;
}

// push an integer onto the stack
void integer(Dlist<int> &stack, int n)
{
    int *np = new int;
    *np = n;
    stack.insertFront(np);
}

// pop two integers from the stack, add them, and push the result
void add(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        stack.insertFront(op1);
        return;
    }
    int *op2 = stack.removeFront();
    int *result = new int;
    *result = *op1 + *op2;
    stack.insertFront(result);
    delete op1;
    delete op2;
}

// pop two integers from the stack, subtract them, and push the result
void subtract(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        stack.insertFront(op1);
        return;
    }
    int *op2 = stack.removeFront();
    int *result = new int;
    *result = *op2 - *op1;
    stack.insertFront(result);
    delete op1;
    delete op2;
}

// pop two integers from the stack, multiply them, and push the result
void multiply(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        stack.insertFront(op1);
        return;
    }
    int *op2 = stack.removeFront();
    int *result = new int;
    *result = *op1 * *op2;
    stack.insertFront(result);
    delete op1;
    delete op2;
}

// pop two integers from the stack, divide them, and push the result
void divide(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        stack.insertFront(op1);
        return;
    }
    int *op2 = stack.removeFront();
    if (*op1 == 0)
    {
        cout << "Divide by zero\n";
        stack.insertFront(op2);
        stack.insertFront(op1);
        return;
    }
    int *result = new int;
    *result = *op2 / *op1;
    stack.insertFront(result);
    delete op1;
    delete op2;
}

// pop an integer from the stack, negate it, and push the result
void negateNum(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    int *result = new int;
    *result = -(*op1);
    stack.insertFront(result);
    delete op1;
}

// duplicate the top integer on the stack
void duplicate(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    int *result = new int;
    *result = *op1;
    stack.insertFront(op1);
    stack.insertFront(result);
}

// reverse the top two integers on the stack
void reverse(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        stack.insertFront(op1);
        return;
    }
    int *op2 = stack.removeFront();
    stack.insertFront(op1);
    stack.insertFront(op2);
}

// print the top integer on the stack
void print(Dlist<int> &stack)
{
    if (stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int *op1 = stack.removeFront();
    cout << *op1 << endl;
    stack.insertFront(op1);
}

// clear the stack
void clear(Dlist<int> &stack)
{
    while (!stack.isEmpty())
    {
        delete stack.removeFront();
    }
}

// print all integers on the stack
void printAll(Dlist<int> &stack)
{
    Dlist<int> tempStack = stack;
    string output;

    while (!tempStack.isEmpty())
    {
        int *op = tempStack.removeFront();
        output += to_string(*op) + " ";
        delete op;
    }

    // delete the last space
    if (!output.empty() && output.back() == ' ')
    {
        output.pop_back();
    }

    cout << output << endl;
}

// quit the program
void quit(Dlist<int> &stack)
{
    clear(stack);
    exit(0);
}

bool isValidIntegers(const string &token)
{
    if (token.empty())
    {
        return false;
    }

    size_t start = 0;
    if (token[0] == '-')
    {
        if (token.size() == 1)
        {
            return false; // only a minus sign
        }
        start = 1;
    }

    for (size_t i = start; i < token.size(); ++i)
    {
        if (!isdigit(token[i]))
        {
            return false; // find a non-digit character
        }
    }
    return true;
}
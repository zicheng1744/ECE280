#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "ex4.h"

using namespace std;

int main()
{
    library lib;
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("To Kill a Mockingbird", "Harper Lee");

    lib.addBook(book1);
    lib.addBook(book2);

    lib.printInventory();

    cout << "Searching for 'The Great Gatsby'..." << endl;
    cout << lib.searchBook("The Great Gatsby") << endl;

    cout << "Searching for 'aaa'..." << endl;
    try
    {
        cout << lib.searchBook("aaa") << endl;
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        lib.returnBook(1);
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        lib.returnBook(3);
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        lib.borrowBook(3);
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }

    lib.borrowBook(1);
    lib.listBorrowed();

    lib.returnBook(1);
    try
    {
        lib.listBorrowed();
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
#include "ex2.h"

int main()
{
    Library lib = initLibrary();
    addBook(lib, "1", "J.D. Salinger");
    addBook(lib, "2", "Harper Lee");
    addBook(lib, "3", "Harper");
    addBook(lib, "4", "Harper");
    addBook(lib, "5", "Harper");
    addBook(lib, "6", "Harper Lee");
    addBook(lib, "7", "Harper Lee");
    addBook(lib, "8", "Harper Lee");
    addBook(lib, "9", "Harper Lee");
    addBook(lib, "10", "Harper Lee");
    addBook(lib, "11", "Harper Lee");
    addBook(lib, "12", "Harper Lee");
    printLibrary(lib);
    borrowBook(lib, 1);
    borrowBook(lib, 1);
    borrowBook(lib, 11);
    borrowBook(lib, 2);
    returnBook(lib, 11);
    returnBook(lib, 1);
    returnBook(lib, 1);
    printLibrary(lib);
    return 0;
}
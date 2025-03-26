#include "ex2.h"

// initialize the library
Library initLibrary()
{
    Library lib;
    lib.numBooks = 0;
    return lib;
}

// add a book to the library
void addBook(Library &lib, const std::string title, const std::string author)
{
    if (lib.numBooks < MAX_BOOKS)
    {
        int ID = lib.numBooks + 1;
        lib.books[lib.numBooks] = {ID, title, author, true};
        lib.numBooks++;
    }
    else
    {
        cout << "The library is full." << endl;
    }
}

// borrow a book
void borrowBook(Library &lib, int ID)
{
    if (ID < 1 || ID > lib.numBooks)
    {
        cout << "Invalid book ID." << endl;
        return;
    }
    for (int i = 0; i < lib.numBooks; ++i)
    {
        if (lib.books[i].ID == ID && lib.books[i].isAvailable)
        {
            lib.books[i].isAvailable = false;
            cout << "Book " << lib.books[i].title << " is borrowed." << endl;
            return;
        }
        else if (lib.books[i].ID == ID && !lib.books[i].isAvailable)
        {
            cout << "Book " << lib.books[i].title << " is not available." << endl;
            return;
        }
    }
}

// return a book
void returnBook(Library &lib, int ID)
{
    if (ID < 1 || ID > lib.numBooks)
    {
        cout << "Invalid book ID." << endl;
        return;
    }
    for (int i = 0; i < lib.numBooks; ++i)
    {
        if (lib.books[i].ID == ID && !lib.books[i].isAvailable)
        {
            lib.books[i].isAvailable = true;
            cout << "Book " << lib.books[i].title << " is returned." << endl;
            return;
        }
        else if (lib.books[i].ID == ID && lib.books[i].isAvailable)
        {
            cout << "Book " << lib.books[i].title << " is already available." << endl;
            return;
        }
    }
}

// print the library
void printLibrary(const Library &lib)
{
    for (int i = 0; i < lib.numBooks; ++i)
    {
        const auto &book = lib.books[i];
        cout << "Book ID: " << book.ID << endl
             << "Title: " << book.title << endl
             << "Author: " << book.author << endl
             << "Status: " << (book.isAvailable ? "available" : "not available") << endl;
    }
}

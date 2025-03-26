#include "ex4.h"
#include <iostream>

using namespace std;

bookInventory::bookInventory() : numBooks(0)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        books[i] = Book();
    }
}

void bookInventory::addBook(const Book &book)
{
    if (numBooks == MAX_BOOKS)
    {
        throw Exception("The inventory is full.");
    }
    books[numBooks] = book;
    numBooks++;
}

int bookInventory::searchBook(const string &title) const
{
    for (unsigned int i = 0; i < numBooks; i++)
    {
        if (books[i].title == title)
        {
            return i + 1;
        }
    }
    throw Exception("Book " + title + " not found.");
}

void bookInventory::setBook(const Book &book, int ID)
{
    // Check if the ID is valid
    if (ID < 1 || ID > MAX_BOOKS)
    {
        throw Exception("Invalid book ID.");
    }
    // ID is valid and the ID is not occupied
    else if (static_cast<unsigned int>(ID) > numBooks)
    {
        books[numBooks] = book;
        numBooks++;
    }
    else
    {
        books[ID - 1] = book;
    }
}

Book bookInventory::viewBook(int ID) const
{
    // Check if the ID is valid
    if (ID < 1 || static_cast<unsigned int>(ID) > numBooks)
    {
        throw Exception("Invalid book ID.");
    }
    return books[ID - 1];
}

void bookInventory::removeBook(int ID)
{
    // Check if the ID is valid
    if (ID < 1 || static_cast<unsigned int>(ID) > numBooks)
    {
        throw Exception("Invalid book ID.");
    }
    // Shift the books to the left
    for (unsigned int i = ID - 1; i < numBooks - 1; i++)
    {
        books[i] = books[i + 1];
    }
    numBooks--;
}

void bookInventory::printInventory() const
{
    if (numBooks == 0)
    {
        throw Exception("The inventory is empty.");
    }
    for (unsigned int i = 0; i < numBooks; i++)
    {
        cout << "Book ID: " << i + 1 << endl
             << "Title: " << books[i].title << endl
             << "Author: " << books[i].author << endl
             << "Status: " << (books[i].isAvailable ? "available" : "not available") << endl;
    }
}

library::library() : bookInventory()
{
}

void library::borrowBook(int ID)
{
    // Check if the ID is valid
    if (ID < 1 || static_cast<unsigned int>(ID) > numBooks)
    {
        throw Exception("Invalid book ID.");
    }
    // Check if the book is available
    if (books[ID - 1].isAvailable)
    {
        books[ID - 1].isAvailable = false;
    }
    else
    {
        throw Exception("Book " + books[ID - 1].title + " is not available.");
    }
}

void library::returnBook(int ID)
{
    // Check if the ID is valid
    if (ID < 1 || static_cast<unsigned int>(ID) > numBooks)
    {
        throw Exception("Invalid book ID.");
    }
    // Check if the book is not available
    if (!books[ID - 1].isAvailable)
    {
        books[ID - 1].isAvailable = true;
    }
    else
    {
        throw Exception("Book " + books[ID - 1].title + " is already available.");
    }
}

void library::listBorrowed() const
{
    bool borrowed = false;
    for (unsigned int i = 0; i < numBooks; i++)
    {
        if (!books[i].isAvailable)
        {
            cout << "Book ID: " << i + 1 << endl
                 << "Title: " << books[i].title << endl
                 << "Author: " << books[i].author << endl;
            borrowed = true;
        }
    }
    if (!borrowed)
    {
        throw Exception("All books are available.");
    }
}

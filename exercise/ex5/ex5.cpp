#include "ex5.h"
#include <iostream>

using namespace std;

bookInventory::bookInventory() : numBooks(0), empty(true), size(MAX_BOOKS)
{
    books = new Book[MAX_BOOKS];
}

bookInventory::bookInventory(int maxBooks) : numBooks(0), empty(true)
{
    if (maxBooks < 1 || maxBooks > MAX_BOOKS)
    {
        throw Exception("Invalid size.");
    }
    size = maxBooks;
    books = new Book[maxBooks];
}

bookInventory::~bookInventory()
{
    delete[] books;
}

void bookInventory::addBook(const Book &book)
{
    if (numBooks == size)
    {
        throw Exception("The inventory is full.");
    }
    books[numBooks++] = book;
    empty = false;
}

void bookInventory::removeBook(int ID)
{
    if (ID < 1 || ID > static_cast<int>(numBooks))
    {
        throw Exception("Invalid book ID.");
    }
    for (unsigned int i = ID - 1; i < numBooks - 1; i++)
    {
        books[i] = books[i + 1];
    }
    books[--numBooks] = Book();
    if (numBooks == 0)
    {
        empty = true;
    }
}

void bookInventory::printInventory() const
{
    if (empty)
    {
        throw Exception("The inventory is empty.");
    }
    else
    {
        for (unsigned int i = 0; i < numBooks; i++)
        {
            cout << "Book ID: " << i + 1 << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
        }
    }
}

bool bookInventory::repOK()
{
    int numBooks = getNumBooks();
    bool empty = isEmpty();
    unsigned int size = getSize();

    if (size < 1 || size > MAX_BOOKS)
    {
        return false;
    }

    if (numBooks < 0 || static_cast<unsigned int>(numBooks) > size)
    {
        return false;
    }

    if (empty && numBooks != 0)
    {
        return false;
    }

    if (!empty && numBooks == 0)
    {
        return false;
    }

    // The inventory is empty if and only if all the books are default empty books
    if (empty)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            if (books[i].title != "" || books[i].author != "")
            {
                return false;
            }
        }
    }
    else
    {
        // The books should be tightly packed in the array. That is, there should be no empty slots between books
        for (unsigned int i = 0; i < static_cast<unsigned int>(numBooks); i++)
        {
            if (books[i].title == "" || books[i].author == "")
            {
                return false;
            }
        }
        // All books after the last book should be default empty books
        for (unsigned int i = numBooks; i < size; i++)
        {
            if (books[i].title != "" || books[i].author != "")
            {
                return false;
            }
        }
    }

    return true;
}

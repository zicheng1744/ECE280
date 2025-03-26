#ifndef EX2_H
#define EX2_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 10;

// build the structure of Book and Library
struct Book
{
    int ID;
    string title;
    string author;
    bool isAvailable;
};

struct Library
{
    Book books[MAX_BOOKS];
    int numBooks;
};

// declare the functions
Library initLibrary();
void addBook(Library &lib, const std::string title, const std::string author);
void borrowBook(Library &lib, int ID);
void returnBook(Library &lib, int ID);
void printLibrary(const Library &lib);

#endif

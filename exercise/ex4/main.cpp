#include "ex4.h"

using namespace std;

int main()
{
    library lib;
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("To Kill a Mockingbird", "Harper Lee");
    Book book3("1984", "George Orwell");
    Book book4("Pride and Prejudice", "Jane Austen");
    Book book5("The Catcher in the Rye", "J.D. Salinger");
    Book book6("Animal Farm", "George Orwell");
    Book book7("The Hobbit", "J.R.R. Tolkien");
    Book book8("The Lord of the Rings", "J.R.R. Tolkien");
    Book book9("The Da Vinci Code", "Dan Brown");
    Book book10("The Alchemist", "Paulo Coelho");

    lib.addBook(book1);
    lib.addBook(book2);
    lib.addBook(book3);
    lib.addBook(book4);
    lib.addBook(book5);
    lib.addBook(book6);
    lib.addBook(book7);
    lib.addBook(book8);
    lib.addBook(book9);
    lib.addBook(book10);

    lib.printInventory();

    lib.borrowBook(1);
    lib.borrowBook(2);
    lib.borrowBook(3);
    lib.borrowBook(4);
    lib.borrowBook(5);
    lib.borrowBook(6);
    lib.borrowBook(7);
    lib.borrowBook(8);
    lib.borrowBook(9);
    lib.borrowBook(10);

    lib.printInventory();

    return 0;
}
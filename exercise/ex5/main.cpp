#include "ex5.h"
#include <iostream>

using namespace std;

void is_repOK(bookInventory &inventory);

int main()
{
    // normal test
    bookInventory inventory(5);
    is_repOK(inventory); // 1

    inventory.setNumBooks(10);
    is_repOK(inventory); // 0
    inventory.setNumBooks(0);

    inventory.setEmpty(false);
    is_repOK(inventory); // 0
    inventory.setEmpty(true);

    inventory.setBook(Book("Book1", "Author1"), 1);
    is_repOK(inventory); // 0
    inventory.setBook(Book(), 1);
    is_repOK(inventory); // 1

    inventory.addBook(Book("Book1", "Author1"));
    inventory.addBook(Book("Book2", "Author2"));
    inventory.addBook(Book("Book3", "Author3"));
    inventory.addBook(Book("Book4", "Author4"));
    inventory.printInventory();

    is_repOK(inventory); // 1

    inventory.setEmpty(true);
    is_repOK(inventory); // 0
    inventory.setEmpty(false);

    inventory.setBook(Book("Book5", "Author5"), 5);
    is_repOK(inventory); // 0
    inventory.setBook(Book(), 5);
    is_repOK(inventory); // 1

    inventory.removeBook(3);
    inventory.printInventory();
    is_repOK(inventory); // 1

    inventory.addBook(Book("Book5", "Author5"));
    try
    {
        inventory.addBook(Book("Book6", "Author6"));
    }
    catch (Exception &e)
    {
        cout << e.what() << endl;
    }
    is_repOK(inventory); // 1

    // bookInventory inventory2(20);
    // is_repOK(inventory2); // 1
    // try
    // {
    //     bookInventory inventory3(0);
    //     is_repOK(inventory3); // 0
    // }
    // catch (Exception &e)
    // {
    //     cout << e.what() << endl;
    // }
    // try
    // {
    //     bookInventory inventory4(21);
    //     is_repOK(inventory4); // 0
    // }
    // catch (Exception &e)
    // {
    //     cout << e.what() << endl;
    // }

    // bookInventory inventory5(1);
    // is_repOK(inventory5); // 1

    inventory.printInventory();
    is_repOK(inventory); // 1

    return 0;
}

void is_repOK(bookInventory &inventory)
{
    bool repOK = inventory.repOK();
    cout << "------ repOK: " << repOK << " ------" << endl;
}
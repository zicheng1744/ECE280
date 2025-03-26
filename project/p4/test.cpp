#include "deck.h"
#include "hand.h"
#include <iostream>

using namespace std;

int main()
{
    // test deck
    Deck d;
    d.reset();
    d.shuffle(24);
    Card c = d.deal();
    cout << c.spot << " " << c.suit << endl;
    cout << d.cardsLeft() << endl;

    // test hand
    Hand h;
    // h.addCard(c);
    cout << h.handValue().count << " " << h.handValue().soft << endl;
    Card c1 = d.deal();
    cout << c1.spot << " " << c1.suit << endl;
    cout << d.cardsLeft() << endl;
    h.addCard(c1);
    HandValue hv = h.handValue();
    cout << hv.count << " " << hv.soft << endl;
    Card c2 = d.deal();
    cout << c2.spot << " " << c2.suit << endl;
    cout << d.cardsLeft() << endl;
    h.addCard(c2);
    hv = h.handValue();
    cout << hv.count << " " << hv.soft << endl;
}
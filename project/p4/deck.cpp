#include "deck.h"
#include <iostream>

using namespace std;

// EFFECTS: constructs a "newly opened" deck of cards:  first the
// spades from 2-A, then the hearts, then the clubs, then the
// diamonds.  The first card dealt should be the 2 of Spades.
Deck::Deck()
{
    reset();
}

// EFFECTS: resets the deck to the state of a "newly opened" deck
// of cards:
void Deck::reset()
{
    int i = 0;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            Card newCard;
            newCard.suit = Suit(suit);
            newCard.spot = Spot(rank);
            deck[i] = newCard;
            // cout << deck[i].spot << " " << deck[i].suit << endl;
            i++;
        }
    }
    next = 0;
    // for (int i = 0; i < DeckSize; i++)
    // {
    //     cout << deck[i].spot << " " << deck[i].suit << endl;
    // }
}

// REQUIRES: "n" is between 0 and 52, inclusive.
// MODIFIES: this
void Deck::shuffle(int n)
{
    Card tempDeck[DeckSize];
    if (n <= 26)
    {
        for (int i = 0; i < n; i++)
        {
            tempDeck[2 * i] = deck[n + i];
            tempDeck[2 * i + 1] = deck[i];
        }
        for (int i = 0; i < 52 - 2 * n; i++)
        {
            tempDeck[2 * n + i] = deck[2 * n + i];
        }
    }
    else
    {
        for (int i = 0; i < 52 - n; i++)
        {
            tempDeck[2 * i] = deck[n + i];
            tempDeck[2 * i + 1] = deck[i];
        }
        for (int i = 0; i < 2 * n - 52; i++)
        {
            tempDeck[2 * (52 - n) + i] = deck[52 - n + i];
        }
    }

    for (int i = 0; i < DeckSize; i++)
    {
        deck[i] = tempDeck[i];
    }
    next = 0;
    // for (int i = 0; i < DeckSize; i++)
    // {
    //     cout << deck[i].spot << " " << deck[i].suit << endl;
    // }
}

// MODIFIES: this
// EFFECTS: deals the "next" card and returns that card. If no cards
// remain, throws an instance of DeckEmpty.
Card Deck::deal()
{
    if (next == DeckSize)
    {
        throw DeckEmpty();
    }
    next++;
    return deck[next - 1];
}

// EFFECTS: returns the number of cards in the deck that have not
// been dealt since the last reset/shuffle.
int Deck::cardsLeft()
{
    return DeckSize - next;
}
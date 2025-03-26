#include "hand.h"

using namespace std;

Hand::Hand()
{
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll()
{
    curValue.count = 0;
    curValue.soft = false;
}

// MODIFIES: this
// EFFECTS: adds the card "c" to those presently held.
void Hand::addCard(Card c)
{
    if (c.spot == ACE)
    {
        if (curValue.count + 11 > 21)
        {
            curValue.count += 1;
        }
        else
        {
            curValue.count += 11;
            curValue.soft = true;
        }
    }
    else if (c.spot >= TEN)
    {
        curValue.count += 10;
    }
    else
    {
        curValue.count += c.spot + 2;
    }

    if (curValue.count > 21 && curValue.soft)
    {
        curValue.count -= 10;
        curValue.soft = false;
    }
}

// EFFECTS: returns the present value of the blackjack hand.  The
// count field is the highest blackjack total possible without
// going over 21.  The soft field should be true if and only if at
// least one ACE is present, and its value is counted as 11 rather
// than 1.  If the hand is over 21, any value over 21 may be returned.
HandValue Hand::handValue() const
{
    return curValue;
}
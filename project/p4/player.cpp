#include "player.h"

using namespace std;

class SimplePlayer : public Player
{
    // A simple player
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // EFFECTS: returns the player's bet, between minimum and bankroll
    // inclusive

    bool draw(Card dealer,         // Dealer's "up card"
              const Hand &player); // Player's current hand
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.

    void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

    void shuffled();
    // EFFECTS: tells the player that the deck has been re-shuffled.
};

int SimplePlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}

bool SimplePlayer::draw(Card dealer, const Hand &player)
{
    HandValue hv = player.handValue();
    if (!hv.soft) // hard count
    {
        if (hv.count <= 11)
        {
            return true;
        }
        else if (hv.count == 12)
        {
            if (dealer.spot >= FOUR && dealer.spot <= SIX)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (hv.count >= 13 && hv.count <= 16)
        {
            if (dealer.spot >= SEVEN)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else // soft count
    {
        if (hv.count <= 17)
        {
            return true;
        }
        else if (hv.count == 18)
        {
            if (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
}

void SimplePlayer::expose(Card c)
{
    return;
}

void SimplePlayer::shuffled()
{
    return;
}

class CountingPlayer : public SimplePlayer
{
    // A counting player
    int count;

public:
    CountingPlayer() : count(0) {}
    // EFFECTS: constructs a counting player with a count of 0

    int bet(unsigned int bankroll,
            unsigned int minimum);
    // EFFECTS: returns the player's bet, between minimum and bankroll
    // inclusive

    void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

    void shuffled();
    // EFFECTS: tells the player that the deck has been re-shuffled.
};

int CountingPlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    if (count >= 2 && bankroll >= 2 * minimum)
    {
        return 2 * minimum;
    }
    else
    {
        return minimum;
    }
}

void CountingPlayer::expose(Card c)
{
    if (c.spot >= TWO && c.spot <= SIX)
    {
        count++;
    }
    else if (c.spot >= TEN)
    {
        count--;
    }
}

void CountingPlayer::shuffled()
{
    count = 0;
}

static SimplePlayer simple;
static CountingPlayer counting;

Player *get_Simple()
{
    return &simple;
}

Player *get_Counting()
{
    return &counting;
}
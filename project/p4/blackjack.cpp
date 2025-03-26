#include "rand.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <string>

using namespace std;

void goShuffle(Deck &d, Player *p);
void playOneHand(Deck &d, Player *p, int &bankroll, int &minimum);

int main(int argc, char *argv[])
{
    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);

    // set the player
    Player *p;
    if (string(argv[3]) == "simple")
    {
        p = get_Simple();
    }
    else
    {
        p = get_Counting();
    }

    // initialize the deck
    int minimum = 5;
    Deck d;
    goShuffle(d, p);

    // go and play
    int thishand = 0;
    for (int i = 0; i < hands; i++)
    {
        if (bankroll < minimum)
        {
            break;
        }
        thishand++;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        playOneHand(d, p, bankroll, minimum);
    }

    // print the result
    cout << "Player has " << bankroll
         << " after " << thishand << " hands\n";

    return 0;
}

void goShuffle(Deck &d, Player *p)
{
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; i++)
    {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        d.shuffle(cut);
        p->shuffled();
    }
}

void playOneHand(Deck &d, Player *p, int &bankroll, int &minimum)
{
    // check if the deck needs to be shuffled
    if (d.cardsLeft() < 20)
    {
        goShuffle(d, p);
    }

    // place the bet
    int wager = 0;
    if (bankroll < minimum)
    {
        return;
    }
    else
    {
        wager = p->bet(bankroll, minimum);
        cout << "Player bets " << wager << endl;
    }

    // deal the first four cards
    Card player1 = d.deal();
    cout << "Player dealt " << SpotNames[player1.spot] << " of " << SuitNames[player1.suit] << endl;
    p->expose(player1);
    Card dealer1 = d.deal();
    cout << "Dealer dealt " << SpotNames[dealer1.spot] << " of " << SuitNames[dealer1.suit] << endl;
    p->expose(dealer1);
    Card player2 = d.deal();
    cout << "Player dealt " << SpotNames[player2.spot] << " of " << SuitNames[player2.suit] << endl;
    p->expose(player2);
    Card dealer2 = d.deal();

    Hand playerHand;
    playerHand.addCard(player1);
    playerHand.addCard(player2);

    Hand dealerHand;
    dealerHand.addCard(dealer1);
    dealerHand.addCard(dealer2);

    // check if the player has a natural 21
    HandValue playerValueInitial = playerHand.handValue();
    if (playerValueInitial.count == 21)
    {
        cout << "Player dealt natural 21\n";
        bankroll += 3 * wager / 2;
        return;
    }

    // player's turn
    while (p->draw(dealer1, playerHand))
    {
        Card player = d.deal();
        cout << "Player dealt " << SpotNames[player.spot] << " of " << SuitNames[player.suit] << endl;
        playerHand.addCard(player);
        p->expose(player);
    }

    int player_count = playerHand.handValue().count;
    cout << "Player's total is " << player_count << endl;
    if (player_count > 21)
    {
        cout << "Player busts\n";
        bankroll -= wager;
        return;
    }

    // show the dealer's hole card
    cout << "Dealer's hole card is " << SpotNames[dealer2.spot] << " of " << SuitNames[dealer2.suit] << endl;
    p->expose(dealer2);

    // dealer's turn
    while (dealerHand.handValue().count < 17)
    {
        Card dealer = d.deal();
        cout << "Dealer dealt " << SpotNames[dealer.spot] << " of " << SuitNames[dealer.suit] << endl;
        dealerHand.addCard(dealer);
        p->expose(dealer);
    }
    int dealer_count = dealerHand.handValue().count;
    cout << "Dealer's total is " << dealer_count << endl;

    if (dealer_count > 21)
    {
        cout << "Dealer busts\n";
        bankroll += wager;
        return;
    }

    // compare the player and dealer
    if (player_count > dealer_count)
    {
        cout << "Player wins\n";
        bankroll += wager;
    }
    else if (player_count < dealer_count)
    {
        cout << "Dealer wins\n";
        bankroll -= wager;
    }
    else
    {
        cout << "Push\n";
    }
    return;
}
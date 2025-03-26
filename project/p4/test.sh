#!/bin/bash
g++ -Wall -o blackjack blackjack.cpp card.cpp deck.cpp hand.cpp player.cpp rand.cpp
./blackjack 10000 10000 simple > localtest1.out
diff localtest1.out mytest1.out
./blackjack 10000 10000 counting > localtest2.out
diff localtest2.out mytest2.out
./blackjack 987 10000 simple > localtest3.out
diff localtest3.out mytest3.out
./blackjack 987 10000 counting > localtest4.out
diff localtest4.out mytest4.out
./blackjack 10 10000 counting > ltest11.out
diff ltest11.out test11.out
./blackjack 7 10000 counting > ltest22.out
diff ltest22.out test22.out
./blackjack 26 10000 counting > ltest33.out
diff ltest33.out test33.out           
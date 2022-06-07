// achieved good results on probabilities by running 2 million tests

#include <iostream>
#include <vector>
#include <algorithm> // random_shuffle
#include <iomanip> // setprecision
#include "Card.hpp"

#define foo1( a ) (a * a)
inline int foo2( int a ) { return (a * a); }

using namespace std;

const short deckSize = 52;
const short handSize = 5;

bool sortByPips(const Card& lhs, const Card& rhs){
    return (lhs.getValue() < rhs.getValue());
}
ostream& operator<< (ostream& out, const vector<Card>& deck);

void init_deck          (vector<Card>& deck);
void getHandOfCards     (vector<Card>& hand, vector<Card>& deck);
bool hasDuplicatePips   (vector<Card>& hand);
bool thereIsAnAce       (vector<Card>& hand);
bool isFlush            (vector<Card>& hand);
bool isStraight         (vector<Card>& hand);
bool isStraightFlush    (vector<Card>& hand);


int main (int argc, char** argv){

    int a = 2, b = -3, c = 2;
    cout <<  "-a * c++ " << -a * c++ << endl;
    char ch = 'b';
    ch += 2;
    cout << "ch += 2 -> " << ch << endl;
    return 0;

    cout << "This program allows you to choose the number of deck shuffles in order to calculate";
    cout << " the probabilities of obtaining a hand of poker which will be a:" << endl;
    cout << "1) Flush" << endl;
    cout << "2) Straight" << endl;
    cout << "3) Straight Flush" << endl << endl;
    
    bool printDeck = false;
    int numOfShuffles = 1;
    int flushCount = 0, straightCount = 0, straightFlushCount = 0;
    srand(time(0));

    vector<Card> deck (deckSize);
    vector<Card> hand (handSize);

    init_deck(deck);

    char answer = 'n';
    cout << "Should we print the deck (y/n) ?";
    
    do // just to use some do-while somewhere
    {
        cout << "Please answer only 'y' for YES or 'n' fo NO.";
        cin >> answer;
    } while (answer != 'y' && answer != 'n'); 

    printDeck = (answer == 'y' ? true : false);

    if (printDeck){
        cout << "Printing deck: " << deck << endl;
        cout << "Done printing the deck." << endl;
        cout << endl; 
    }else{
        cout << "Won't print the deck." << endl;
    }

    cout << "How many shuffles? " << endl;
    cout << "Usually we get good results with 2M+ shuffles." << endl;

    do 
    {
        cout << "Please input a number >= 100: ";
        cin >> numOfShuffles;
    } while (numOfShuffles < 100);

    cout << "------------------------------------------------" << endl;
    cout << "Shuffling " << numOfShuffles << " times.." << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < numOfShuffles; i++){
        random_shuffle(deck.begin(), deck.end());
        getHandOfCards(hand, deck);
        if (isStraight(hand)){
            straightCount++;
            // cout << hand << (isStraight(hand) ? " is a straight - ": "") << (isFlush(hand) ? " is a Flush - ": "") << (isStraightFlush(hand) ? " is a StraightFlush": "") << endl;
        }
        if (isFlush (hand)){
            flushCount++;
            // cout << hand << (isStraight(hand) ? " is a straight - ": "") << (isFlush(hand) ? " is a Flush - ": "") << (isStraightFlush(hand) ? " is a StraightFlush": "") << endl;
        }
        if (isStraightFlush(hand)){
            straightFlushCount++;
            // cout << hand << (isStraight(hand) ? " is a straight - ": "") << (isFlush(hand) ? " is a Flush - ": "") << (isStraightFlush(hand) ? " is a StraightFlush": "") << endl;
        }    
    }

    double percFlushes          = (1.0*flushCount)/numOfShuffles*100;
    double percStraights        = (1.0*straightCount)/numOfShuffles*100;
    double percStraightFlushes  = (1.0*straightFlushCount)/numOfShuffles*100;

    cout << "Total shuffles:    " <<  numOfShuffles     << endl;
    cout << "Flushes:           " <<  flushCount        << "\t(" << fixed << setprecision(4)     << percFlushes         << "%) or 1 in " << ( percFlushes  <= 0 ? 0 : static_cast<int>(100.0/(percFlushes        )) ) << endl;
    cout << "Straights:         " <<  straightCount     << "\t(" << fixed << setprecision(4)     << percStraights       << "%) or 1 in " << ( percFlushes  <= 0 ? 0 : static_cast<int>(100.0/(percStraights      )) ) << endl;
    cout << "StraightFlushes:   " <<  straightFlushCount<< "\t(" << fixed << setprecision(4)     << percStraightFlushes << "%) or 1 in " << ( percFlushes  <= 0 ? 0 : static_cast<int>(100.0/(percStraightFlushes)) ) << endl;

    return 0;
}

ostream& operator<< (ostream& out, const vector<Card>& cards){

    // if it's a deck
    if (cards.size() == deckSize){

        out << endl;
        out << "---------------- begin of cards --------------" << endl;
        out << "cards size = " << cards.size() << endl;
        // doesnt work
        // for (auto &card : cards){
        //     out << "hi" << endl;
        //     out << card << endl;
        // }
        
        // works
        for (int i = 0; i < deckSize; i++){
            out << cards.at(i) << endl;
        }
        out << "---------------- end of cards --------------" << endl;
        
    }else if (cards.size() == handSize){
        
        out << "HAND: ";
        for (int i = 0; i < handSize - 1; i++){
            out << cards.at(i) << "\t";
        }
        out << cards.at(handSize-1);
    }
    
    return out;
}

void init_deck(vector<Card>& deck){

    assert(deck.capacity() == deckSize);

    for (int i = 1; i <= 13; i++){
        // Card cardOfSpades   ( i, suit::SPADE);
        // Card cardOfHearts   ( i, suit::HEART);
        // Card cardOfDiamonds ( i, suit::DIAMOND);
        // Card cardOfClubs    ( i, suit::CLUB);
        
        // deck.at(i -1) = cardOfSpades;
        // deck.at(i+12) = cardOfHearts;
        // deck.at(i+25) = cardOfDiamonds;
        // deck.at(i+38) = cardOfClubs;

        deck.at(i -1) = Card( i, suit::SPADE);
        deck.at(i+12) = Card( i, suit::HEART);
        deck.at(i+25) = Card( i, suit::DIAMOND);
        deck.at(i+38) = Card( i, suit::CLUB);

        
    }

    // cout << "ORIGINAL DECK : " << deck << endl;
}

void getHandOfCards(vector<Card>& hand, vector<Card>& deck){
    
    for (int i = 0; i < handSize; i++){
        hand[i] = deck[i];
    }
}

bool hasDuplicatePips(vector<Card>& hand){
    
    for (int i = 0; i < hand.size() -1; i++){
        if (hand[i].getValue() == hand[i+1].getValue()){
            return true;
        }
    }
    return false;
}

bool thereIsAnAce(vector<Card>& hand){

    for (auto &card: hand){
        if (card.getValue() == 1)
            return true;
    }

    return false;

}

bool isFlush(vector<Card>& hand){

    assert(hand.capacity() == handSize);
    suit s = hand[0].getSuit();
    for (int i = 1; i < handSize; i++){
        if (hand[i].getSuit() != s) 
            return false;
    }

    return true;
}

bool isStraight(vector<Card>& hand){

    if (hasDuplicatePips(hand)){ 
        return false;
    }
    
    // sort vector
    sort(hand.begin(), hand.end(), sortByPips);

    // logic if there's an ace
    if (thereIsAnAce(hand)){
        // if the Ace is working as a '1', the following is true
        if ((hand[4].getValue() - hand[0].getValue()) == 4){
            return true;
        }else{
            // if the last element is a king (13) we can make the following difference
            if( hand[4].getValue() == 13 && abs(hand[4].getValue() - hand[1].getValue()) == 3){
                return true;
            }
        }
        
        return false;    

    }else{// logic if there's NOT an ace
        // since there are no duplicates, no aces and vector is sorted
        return (abs(hand[4].getValue() - hand[0].getValue()) == 4);
    }
    

}

bool isStraightFlush(vector<Card>& hand){

    return (isStraight(hand) && isFlush(hand));
}
#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <assert.h>

using namespace std;

enum class suit:short{SPADE, HEART, DIAMOND, CLUB}; // defining as short to save memory

ostream& operator<< (ostream& out, const suit& s);

class pips{
    public:   
        pips(int value);
        int getValue() const;     
        friend ostream& operator<<(ostream& out, const pips& p);
    private:
        int value;
};


class Card{
    public:
        Card();
        Card(pips p, suit s);
        Card(int i , suit s);
        int getValue() const;
        suit getSuit() const;
        friend ostream& operator<<(ostream& out, const Card& card){
            out << card.pip << " of " << card.getSuit();
            return out;
        }   

    private:
        pips pip;
        suit s;
};

#endif
#include "Card.hpp"

using namespace std;

std::ostream& operator<< (std::ostream& out, const suit& s){
    switch (s)
    {
    case suit::SPADE:
        out << "SPADES";
        break;
    case suit::HEART:
        out << "HEARTS";
        break;
    case suit::DIAMOND:
        out << "DIAMONDS";
        break;
    case suit::CLUB:
        out << "CLUBS";
        break;
    default:
        break;
    }
    return out;
}

ostream& operator<<(ostream& out, const pips& p){
    switch (p.getValue())
    {
    case 1:
        out << "Ace";
        break;
    case 11:
        out << "J";
        break;
    case 12:
        out << "Q";
        break;
    case 13:
        out << "K";
        break;
    default:
        out << p.getValue();
        break;
    }
    return out; 
}

pips::pips(int value = 1): value(value){
    assert(value >= 1 && value <= 13);
}

int pips::getValue() const {return value;}  

Card::Card(){}

Card::Card(pips p, suit s) : pip(p), s(s){}

Card::Card(int i, suit s){
    pips p(i);
    this->pip = p;
    this->s = s;
}

int Card::getValue() const {return pip.getValue();}

suit Card::getSuit() const {return s;}
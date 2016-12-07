/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097,
* Date: November 30, 2016
*
* Description:  A Dealer class that uses Player class as a base class reperesenting 
*               an instance of a dealer in a Blackjack game.
*				
*/

#ifndef _DEALER
#define _DEALER

#include "Card.h"
#include "Player.h"
//#include <cstdlib>					// for system()
//#include <stdexcept>
//#include <iomanip> 					// for output formatting
//#include <iostream>
//#include <string>					    // for string
//#include <sstream>					// for stringstream
#include <vector>

using namespace std;

class Dealer : public Player
{
    public:
        // STATIC DATA MEMBERS
        static const double DEFAULT_MONEY_AMOUNT;
        // DEFAULT CONSTRUCTOR
        Dealer(): Player("Dealer") {}
        // PARAMETERIZED CONSTRUCTOR
        Dealer(string name);
        // ACCESSORS
        
        // MUTATORS
        void FlipInitialCard();                     // Method used to flip the initial card dealt to the dealer face up
};


/************************ 
 Dealer Class Definitions
 *********************/ 
 
// Parameterized Constructor
Dealer::Dealer(string name)
{
    // call base class constructor
    m_playerName = name;        
}

void Dealer::FlipInitialCard()
{
    m_hand[0].m_isFaceUp = true;
}

#endif

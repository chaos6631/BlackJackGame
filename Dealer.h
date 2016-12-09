/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097, Christopher Alexander #100360337
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
		Dealer(): Player("Dealer"), m_dealersTurn(false) {}
        
		// PARAMETERIZED CONSTRUCTOR
        Dealer(string name);
        
		// ACCESSORS
        
        // MUTATORS
        void FlipInitialCard();                     // Method used to flip the initial card dealt to the dealer face up
        void Hit(Card newCard);    					// Gets a new card and places it in the hand
        bool m_dealersTurn;							// returns true if it is the dealers turn
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
// FlipInitialCard() : Method used to flip the initial card dealt to the dealer face up
void Dealer::FlipInitialCard()
{
    m_hand[0].m_isFaceUp = true;
    m_dealersTurn = true;
}
// Hit() : Gets a new card and places it in the hand
void Dealer::Hit(Card newCard)
{       
    m_hand.push_back(newCard);       
}
#endif

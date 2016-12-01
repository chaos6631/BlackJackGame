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
        Dealer(): Player("Dealer1") {}
        // PARAMETERIZED CONSTRUCTOR
        Dealer(string name);
        // ACCESSORS
        
        // MUTATORS
        void Play();                     // Method used to play a round for the dealer, determining which moves are to be made based on cards
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

void Dealer::Play()
{
    // Check card values then determine what move the dealer must make
    // If value is less than 17 dealer must hit
    // If value is greater or equal to 17 dealer must stand
}
#endif

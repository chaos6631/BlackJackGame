/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097,
* Date: 
*
* Description:  A Game class that reperesents an instance of a blackjack game
*				
*/

#ifndef _GAMEBLACKJACK
#define _GAMEBLACKJACK

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
//#include "Dealer.h"
//#include <cstdlib>					// for system()
//#include <stdexcept>
//#include <iomanip> 					// for output formatting
//#include <iostream>
//#include <string>					// for string
//#include <sstream>					// for stringstream
////#include <algorithm>   
////#include <stack>
////#include <vector>


using namespace std;

class BlackJackGame
{
    public:
        static const double MINIMUM_BET;
        
        // default Constructor
        BlackJackGame(){}
        // Parameterized Constructor 
		BlackJackGame(Player& player) ;
    	
		void StartGame();                   // consists of a new round
    	void NextRound();                   // is called if player still has money and wishes to continue, consists of a new round
    	void EndGame();                     // shows player totals and returns to the main menu
    	//GetCurrentLeader()                // could be void just outputing the current leader or could return a player object to be used  
    	//GetPlayerTotals()                 // Output the player money totals
	private:
		Player m_player;
        Deck m_gameDeck;
//    	Dealer m_gameDealer;
};

/*************************
 FUNCTION DEFINITIONS
**************************/

const double BlackJackGame::MINIMUM_BET = 5;

BlackJackGame::BlackJackGame(Player& player)
{
	m_player = player;
//	m_gameDeck = gameDeck;
//	m_gameDeck();
//	m_gameDealer = gameDealer;
//	m_gameDealer = new Dealer();
}
//BlackJackGame::NextRound()
//{
//	//ask player to bet amount, which removes amount from player total
//	// deal cards use pop_back() to remove card from vector
//		//player.SetHand(deck.GiveCard(), deck.GiveCard())
//		// dealer.SetHand(deck.GiveCard(), deck. GiveCard() )
//	// display hands
//	// Ask player to hit, stand, or split
//	// run the dealer. Play
//		// dealer must hit until they are over 17
//	// decide winner and if player wins add bet amount plus appropriate winnings
//	// end round
//		
//    
//}

#endif


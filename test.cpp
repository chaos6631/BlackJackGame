/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097,
* Date: 
*
* Description:  A C++ program that ....
*				
*/

//#include "MyInputValidation.h"
//#include "GameBlackJack.h"
//#include "BlackJackGUI.h"
#include <ctime>
#include "Deck.h"	// for external file
#include "Player.h"
//#include <cstdlib>					// for system()
//#include <stdexcept>
//#include <algorithm>   
//#include <iomanip> 					// for output formatting
//#include <iostream>
//#include <string>					// for string
//#include <sstream>					// for stringstream
//#include <stack>
//#include <vector>
// Required for Card Symbol Characters
//#include <clocale>
//#include <cstdio>
//#include <windows.h>
//#include <fcntl.h>
//#include <io.h>
//#include <wchar.h>
//
//#pragma execution_character_set( "utf-8" )

using namespace std;
//using namespace myValidation;
//using namespace GUI;

/*************************
 FUNCTION DECLARATIONS
**************************/

/*************************
 GLOBALS
**************************/
const double MINIMUM_BET = 5;
//Player player1;
//Dealer dealer;
Deck gameDeck;
int main()
{
    gameDeck.SetDeckTotal(2);
    gameDeck.FillDeck();
    gameDeck.Shuffle();
	gameDeck.DisplayRemainingCards();
	return 0;    
}


/*************************
 FUNCTION DEFINITIONS
**************************/

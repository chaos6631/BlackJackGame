/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097,
* Date: 
*
* Description:  A C++ program that ....
*				
*/

#include "MyInputValidation.h"
#include "GameBlackJack.h"
#include "BlackJackGUI.h"
#include <ctime>
//#include "Deck.h"	// for external file
//#include "Player.h"
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
using namespace myValidation;
using namespace GUI;

/*************************
 FUNCTION DECLARATIONS
**************************/
bool BeginGamePrompt();

/*************************
 GLOBALS
**************************/
BlackJackGame game;

/*************************
 MAIN 
**************************/
int main()
{
	bool wishToPlay = true;
	
    srand(time(0));                        // Needed for random_shuffle to work should only be implemented once, so in blackjack.cpp main
    SetConsoleOutputCP(65001);             // Code Page must be set to this for Unicode characters to work properly
    
    GUI::DisplayBanner();                  // Displays Game LOGO
    
    try
    {
        wishToPlay = BeginGamePrompt();                      // True if player wants to play, false if not
        if(wishToPlay)
        {    
            GUI::ClearScreen();
            GUI::DisplayBanner(); 
            //// Start the Game if player wishToPlay is true
            game.StartGame();           
        }
                
        //// Continue playing rounds as long as player wants to continue
        while(wishToPlay)
        {   
            //// Prompt for Bet, then deal cards
            game.BettingPrompt();                              // Ask player how much they wish to bet            
            game.DealCards();                                  // Deal cards (comment out to test for SPLIT)
            //game.DealSplitHand();                            // TESTING FOR SPLITHAND FUNCTIONALITY
            
            //// Check for Natural Blackjack
            if(!game.CheckNaturalBlackjack())                  // False if neither player or dealer has a natural blackjack   
            {                   
                game.Round();                                  // Play Round                                      
            }                  
            //// Round Over
            game.ClearHands();                                 // Clear the hands            
            wishToPlay = game.ContinuePlayingPrompt();         // Ask if user would like to play again
        }         
    }
    catch(const invalid_argument& error) 
    {
        cerr << endl << error.what() << endl;
    }
    catch(const exception& error)
    {
        cerr << endl << error.what() << endl;
    }   
    catch(...)
    {
        cerr << endl << "FATAL ERROR!!" << endl;
        cerr << "Contact Technical Support" << endl;
    }
        
	cin.get();
	return 0;    
}


/*************************
 FUNCTION DEFINITIONS
**************************/

bool BeginGamePrompt() // Should stay in BlackJackMain.cpp
{    
	bool play = false;

    if(GUI::YesNoChoicePrompt("\nWould you like to play a game of Blackjack(y/n)?"))
    {
        play = true;
    }
    else
    {
        GUI::GameMessage("\nThat's too bad, maybe next time!! See ya.......\n");      //NOT CREATED YET        
        play = false;
    }
    return play;
}


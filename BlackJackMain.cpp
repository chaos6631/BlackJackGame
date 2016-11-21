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

const double MINIMUM_BET = 5;
int main()
{
	bool wishToPlay = true;
    srand(time(0));                        // Needed for random_shuffle to work should only be implemented once, so in blackjack.cpp main
    SetConsoleOutputCP(65001);             // Code Page must be set to this for Unicode characters to work properly
    DisplayBanner();
    try
    {
        wishToPlay = BeginGamePrompt();
        while(wishToPlay)
        {    
            system("CLS");   
            DisplayBanner();        
            // Player name prompt :: SHould be added to GameBlackJack class as a method           
            string playerName;
            cout << "Please enter your name: ";
            cin >> playerName;
            Player player1(playerName);
            Player dealer("Dealer");
            
            // Start game :: SHould be added to GameBlackJack class as a method
            Deck gameDeck;  
            gameDeck.Shuffle();                       
            
            system("CLS");
            DisplayBanner();  
            GameInfo(player1);  
            
            // Betting Prompt :: SHould be added to GameBlackJack class as a method and called in the GameBlackJack::PlayRound() method
            cout << "\n(Minimum bet is $5, you may increase in $5 increments)"
                 << "Place your bet: $";
            double playerBet = GetValidDouble(MINIMUM_BET, player1.GetPlayerMoneyTotal());
            player1.Bet(playerBet);
            
            cout << "Dealer will now deal cards....." << endl;
            Delay(1);
            cout << "test";
            for(int i = 1;i <= 2; i++)
            {
                player1.AddCard(gameDeck.RemoveNextCard());
                Delay(0.5);
                GameScreen(player1, dealer);
                if(i == 1)
                {
                    Card firstCard = gameDeck.RemoveNextCard();
                    firstCard.m_isFaceUp = false; 
                    dealer.AddCard(firstCard);
                }
                else
                {
                    dealer.AddCard(gameDeck.RemoveNextCard());
                }                
                Delay(0.5);
                GameScreen(player1, dealer);
            }                        
            
            // TODO : need to check for blackjack    
            if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() == 21)
            {
                cout << "Both you and the dealer have BLACKJACK!" << endl
                     << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
                //player1.CollectMoney(playerBet);
            } 
            else if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() < 21)
            {
                cout << "BlackJack!! You win $" << ((playerBet * 2) * 1.5) << endl;
                //player1.CollectMoney(playerBet);
            }
            else
            {
                // continue the round
            }
            wishToPlay = false;
            // TODO:: make dealer an extension of player class            
           
        }
            
    }
    catch(const exception& ex)
    {
        cerr << endl << ex.what() << endl;
    }    
    catch(...)
    {
        cerr << endl << "FATAL ERROR" << endl;
    }
        
	cin.get();
	return 0;    
}


/*************************
 FUNCTION DEFINITIONS
**************************/
bool BeginGamePrompt()
{    
	bool play = true;
	bool valid = false;
    char result;
    do
    {
        cout << "\nWould you like to play a game of Blackjack(y/n)?";
        cin >> result;        
        
        result = toupper(result);
        if(result == 'Y')
        {
            play = true;
            valid = true;
        }
        else if(result == 'N')
        {
            cout << "That's too bad, maybe next time!! See ya......." << endl;
            play = false;
            valid = true;
        }
        else
        {
            cerr << "Please enter 'y' for yes, 'n' for no" << endl;
        }
    }
    while(valid == false);
	
    
    return play;
}

//Ask user to create a game(while answer = y) 
// If yes, Collect player name
	// Game newGame(Player player1(string playerName) ) 
	// game consists of players, and a deck
	// newGame.Start(); -> this runs the deck.fill()
	// newGame.Round; -> this runs all functions for a full round
	// if player still has money and or wishes to continue then
		// then newGame.Round();
		// else newGame.Finish();
		


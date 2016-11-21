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
/* Delay() function
 * - Delays the program for a specified amount of time in seconds
 *  @param seconds: the number of seconds to delay the program
 *	@returns void
*/
//double GetValidDouble(const double MIN, const double MAX);

//void Delay(double seconds);
//void GameScreen(Player& player1, Player& dealer);
//void DisplayBanner();               // Function to display game banner
//void GameInfo(Player& player1);
//void RoundScreen(Player& player1, Player& dealer);
bool BeginGamePrompt();

const double MINIMUM_BET = 5;
int main()
{
	bool wishToPlay = true;
    srand(time(0));                 // Needed for random_shuffle to work should only be implemented once, so in blackjack.cpp main
    SetConsoleOutputCP(65001);           // Code Page must be set to this for Unicode characters to work properly
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
            
            
            
            wishToPlay = false;
            // TODO:: make dealer an extension of player class
            // TODO:: Create game
               //GameBlackJack newGame();
            // TODO:: Start game
            // TODO::
            // TODO::
            // TODO::
            // TODO::           
           
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
//
//void GameScreen(Player& player1, Player& dealer)
//{
//    system("CLS");
//    DisplayBanner();
//    GameInfo(player1);
//    RoundScreen(player1, dealer);
//}
//
//void DisplayBanner()
//{
////    cout << "====================================================================================================" << endl
////         << "=       _/_/_/    _/          _/_/      _/_/_/  _/    _/        _/    _/_/      _/_/_/  _/    _/   =" << endl
////         << "=      _/    _/  _/        _/    _/  _/        _/  _/          _/  _/    _/  _/        _/  _/      =" << endl
////         << "=     _/_/_/    _/        _/_/_/_/  _/        _/_/            _/  _/_/_/_/  _/        _/_/         =" << endl
////         << "=    _/    _/  _/        _/    _/  _/        _/  _/    _/    _/  _/    _/  _/        _/  _/        =" << endl
////         << "=   _/_/_/    _/_/_/_/  _/    _/    _/_/_/  _/    _/    _/_/    _/    _/    _/_/_/  _/    _/       =" << endl
////         << "====================================================================================================" << endl;
////    cout << "===================================================================================================================" << endl     
////         << "=         ______     __         ______     ______     __  __       __     ______     ______     __  __            =" << endl
////         << "=        /\  == \   /\ \       /\  __ \   /\  ___\   /\ \/ /      /\ \   /\  __ \   /\  ___\   /\ \/ /            =" << endl
////         << '=        \ \  __<   \ \ \____  \ \  __ \  \ \ \____  \ \  _"-.   _\_\ \  \ \  __ \  \ \ \____  \ \  _"-.          =' << endl
////         << "=         \ \_____\  \ \_____\  \ \_\ \_\  \ \_____\  \ \_\ \_\ /\_____\  \ \_\ \_\  \ \_____\  \ \_\ \_\         =" << endl
////         << "=          \/_____/   \/_____/   \/_/\/_/   \/_____/   \/_/\/_/ \/_____/   \/_/\/_/   \/_____/   \/_/\/_/         =" << endl
////         << "===================================================================================================================" << endl;     
////        NEEDS A WAY TO PRINT IGNORING ESCAPE CHARACTERS                                                                                        
//    cout << "====================================================================================================" << endl
//         << "=       ####### ####         ####  ###### ###  ##  ######     ####  ###### ###  ##                 =" << endl
//         << "=        ###  ## ###        ##### ###  ## ### ##   ## ###    ##### ###  ## ### ##                  =" << endl
//         << "=        ######  ###       ## ### ###     #####       ###   ## ### ###     #####                   =" << endl
//         << "=        ###  ## ###      ##  ### ###     #####       ###  ##  ### ###     #####                   =" << endl
//         << "=        ###  ## ###     ######## ###     ### ##      ### ######## ###     ### ##                  =" << endl
//         << "=        ###  ## ###   # ##   ### ###  ## ###  ##  ## ### ##   ### ###  ## ###  ##                 =" << endl
//         << "=        ######  ####### ##   ###  #####  ###  ##   ####  ##   ###  #####  ###  ##                 =" << endl
//         << "=                         ###                  ##          ###                  ##                 =" << endl
//         << "====================================================================================================" << endl;
//         
//          
//           
//            
//        
//          
//          
//                    
//
//}
//
//void GameInfo(Player& player1)
//{
//    cout << "= Player Name: " << player1.GetPlayerName() << "          Chip Amount: $" << player1.GetPlayerMoneyTotal() << endl
//         << "====================================================================================================" << endl;
//}
//
//void RoundScreen(Player& player1, Player& dealer)
//{
//    int minLength = dealer.GetPlayerName().length();
//    int playerNameLength = player1.GetPlayerName().length();
//    string filler;
//    
//    // If players name is shorter than dealers, add space for player name
//    if(playerNameLength < minLength)
//    {
//        string diff1((minLength - playerNameLength), ' ');
//        filler = diff1;             
//    }        
//    cout << "--------------------------------------------------------------" << endl;
//    cout << filler << player1.GetPlayerName() << "'s Hand: ";
//    player1.ShowCards();
//    cout << "           Card Total : " << player1.GetTotalValue()
//         << "\n--------------------------------------------------------------" << endl;
//    
//    filler.clear();
//    // If players name is longer than dealers, add space for dealer name
//    if(playerNameLength > minLength)                  
//    {
//        string diff2((playerNameLength - minLength), ' ');        
//        filler = diff2;                    
//    }    
//    cout << filler << dealer.GetPlayerName() << "'s Hand: ";
//    dealer.ShowCards();
//    cout << "           Card Total : " << dealer.GetTotalValue()
//         << "\n--------------------------------------------------------------" << endl;
//}
//
//void Delay(double seconds)
//{	
//	clock_t start_time = clock();							// Start time for delay
//	clock_t end_time = seconds * 1000 + start_time;			// End time for delay is seconds * 1000 milliseconds after start time
//	while(clock() != end_time);								// Loop to simulate delay	
//} 
//
//Ask user to create a game(while answer = y) 
// If yes, Collect player name
	// Game newGame(Player player1(string playerName) ) 
	// game consists of players, and a deck
	// newGame.Start(); -> this runs the deck.fill()
	// newGame.Round; -> this runs all functions for a full round
	// if player still has money and or wishes to continue then
		// then newGame.Round();
		// else newGame.Finish();
		


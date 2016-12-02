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
double BettingPrompt(double minimumBet, double maximumBet);
bool CheckBlackjack(Dealer &dealer, Player &player, double playerBet);
bool ContinuePlayingPrompt();
void DealCards(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
void ChoicePrompt(Player &gamePlayer, Deck &gameDeck);


const double MINIMUM_BET = 5;
int main()
{
	bool wishToPlay = true;
	double playerBet;
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
//            Player dealer("Dealer");
            Dealer dealer("Dealer");
            
            // Start game :: SHould be added to GameBlackJack class as a method
            Deck gameDeck;  
            gameDeck.Shuffle();                       
            
            system("CLS");
            DisplayBanner();  
            GameInfo(player1);  
            
            // Betting Prompt :: SHould be added to GameBlackJack class as a method and called in the GameBlackJack::PlayRound() method
            playerBet = BettingPrompt(MINIMUM_BET, player1.GetPlayerMoneyTotal());            
            player1.Bet(playerBet);
            
            // Deal cards
            DealCards(player1, dealer, gameDeck);
            
            // TODO : need to check for blackjack    
            if(CheckBlackjack(dealer, player1, playerBet))
            {
                // End Round
                if(ContinuePlayingPrompt() == true)
                {
                    // play round
                    cout << "\nBegin next round......" << endl;
                }
                else
                {
                    // exit game
                    cout << "\nEnding game......" << endl;
                }
            }
            else
            {
                // play round
                cout << "\nBegin next round......" << endl;
                
            }
            // Check if player has a total of 9,10,11 then ask for DoubleDown doubling initial bet and player will receive one more card
            //       player can also split if both cards are 5's and play it out normally
            ChoicePrompt(player1, gameDeck);
            
//            if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() == 21)
//            {
//                cout << "Both you and the dealer have BLACKJACK!" << endl
//                     << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
//                //player1.CollectMoney(playerBet);
//            } 
//            else if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() < 21)
//            {
//                cout << "BlackJack!! You win $" << ((playerBet * 2) * 1.5) << endl;
//                //player1.CollectMoney(playerBet);
//            }
//            else
//            {
//                // continue the round
//            }
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

double BettingPrompt(double minimumBet, double maximumBet)
{
    double betAmount;
    cout << "\n(Minimum bet is $5, you may increase in $5 increments)"
         << "Place your bet: $";
    betAmount = GetValidDouble(minimumBet, maximumBet);                
    return betAmount;
}

bool CheckBlackjack(Dealer &dealer, Player &player, double playerBet)
{
    bool roundOver = false;                // true if blackjack was reached by anyone, false if not
    
    if(player.GetTotalValue() == 21 && dealer.GetTotalValue() == 21)
    {
        cout << "Both you and the dealer have BLACKJACK!" << endl
             << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
        //player.CollectMoney(playerBet);
        roundOver = true;
    } 
    else if(player.GetTotalValue() == 21 && dealer.GetTotalValue() < 21)
    {
        cout << "BlackJack!..... You win $" << ((playerBet * 2) * 1.5) << "!!!!" << endl;
        //player.CollectMoney(playerBet); ((playerBet * 2) * 1.5)
        roundOver = true;
    }
    else
    {
        cout << "\nNobody has Blackjack!!......" << endl;
    }
    
    return roundOver;                     // Unchanged if no conditional was met
}

bool ContinuePlayingPrompt()
{    
	bool play = true;
	bool valid = false;
    char result;
    do
    {
        cout << "\nWould you like to continue playing(y/n)?";
        cin >> result;        
        
        result = toupper(result);
        if(result == 'Y')
        {
            play = true;
            valid = true;
        }
        else if(result == 'N')
        {
            cout << "Ok, see ya later!!" << endl;
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

void DealCards(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck)
{
    cout << "Dealer will now deal cards....." << endl;
    Delay(1);
    //cout << "test";
    for(int cardsPerPlayer = 1;cardsPerPlayer <= 2; cardsPerPlayer++)
    {
        gamePlayer.AddCard(gameDeck.RemoveNextCard());
        Delay(0.5);
        GameScreen(gamePlayer, gameDealer);
        if(cardsPerPlayer == 1)
        {
            Card firstCard = gameDeck.RemoveNextCard();
            firstCard.m_isFaceUp = false; 
            gameDealer.AddCard(firstCard);
        }
        else
        {
            gameDealer.AddCard(gameDeck.RemoveNextCard());
        }                
        Delay(0.5);
        GameScreen(gamePlayer, gameDealer);
    }                        
}

void ChoicePrompt(Player &gamePlayer, Deck &gameDeck)
{
    bool play = true;
	bool valid = false;         // for valid input
    char result;   
    
    cout << "What would you like to do: " << endl
         << "(H) Hit\n(P) Stand\n(S) Split\n(D) Double-Down)" << endl;             
    do
    {                     
        cout << "Choice: ";             
        cin >> result;        
        
        result = toupper(result);
        switch(result)
        {
            case 'H' : {
                cout << "You chose to HIT"; // run the hit method  
                gamePlayer.Hit(gameDeck.RemoveNextCard());                          
                valid = true;   
                break;
            }                        
            case 'P' : {
                cout << "You chose to STAND"; // run the stand method
                gamePlayer.Stand();   
                valid = true; 
                break;
            }                        
            case 'S' : {
                cout << "You chose to SPLIT"; // run the split method
                // splitting splits the cards and the initial bet amount is taken again for the split hand
                // then the two hands are played with the original hand played first and then the split hand
//                gamePlayer.DoubleDown(gamePlayer.GetCurrentBet())
                valid = true; 
                break;
            }                       
                               
            default : cerr << "Please enter H, P, S, or D" << endl;                          
        }   
    }
    while(valid == false);
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
		


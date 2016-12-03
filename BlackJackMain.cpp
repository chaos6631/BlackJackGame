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
bool CheckNaturalBlackjack(Dealer &dealer, Player &player, double playerBet);
bool ContinuePlayingPrompt();
void DealCards(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
//void ChoicePrompt(Player &gamePlayer, Deck &gameDeck);
bool PlayerDoubleDownCheck(Player &gamePlayer);
void PlayerHitStandCheck(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
bool PlayerSplitCheck(Player &gamePlayer);
void PlayerRound(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
void DealerRound(Dealer &gameDealer, Player &gamePlayer, Deck &gameDeck);
void RoundSettlement(Player &player1, Dealer &dealer);

/*************************
 GLOBALS
**************************/
const double MINIMUM_BET = 5;
Player player1;
Dealer dealer;
Deck gameDeck;
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
        if(wishToPlay)
        {
            system("CLS");   
            DisplayBanner();        
            
            // Player name prompt :: SHould be added to GameBlackJack class as a method           
            string playerName;
            cout << "Please enter your name: ";
            cin >> playerName;
//            Player player1(playerName);
//            Dealer dealer("Dealer");
            player1 = Player(playerName);
            dealer = Dealer("Dealer");
            // Start game :: SHould be added to GameBlackJack class as a method
//            Deck gameDeck; 
            gameDeck = Deck(); 
            gameDeck.Shuffle();    
        }
        while(wishToPlay)
        {    
            if(gameDeck.CardsRemaining() < (gameDeck.MAX_CARD_COUNT / 2))
            {
                gameDeck.FillDeck();
                gameDeck.Shuffle();
            }
            system("CLS");
            DisplayBanner();  
            GameInfo(player1);  
            
            // Betting Prompt :: SHould be added to GameBlackJack class as a method and called in the GameBlackJack::PlayRound() method
            playerBet = BettingPrompt(MINIMUM_BET, player1.GetPlayerMoneyTotal());            
            player1.Bet(playerBet);
            
            // Deal cards
            DealCards(player1, dealer, gameDeck);
            
            // CheckNaturalBlackjack() : need to check for blackjack    
            if(CheckNaturalBlackjack(dealer, player1, playerBet))  
            {    // True if someone has natural BlackJack          
                if(ContinuePlayingPrompt() == true)
                {                    
                    cout << "\nBegin next round......" << endl;                               // play round
                }
                else
                {                    
                    cout << "\nEnding game......" << endl;                                    // exit game
                }
            }
            else // False if nobody has a natural blackjack
            {                
                cout << "\nBegin next round......" << endl;                                   // play round                
            }
            
            //Reload the screen
            GameScreen(player1, dealer);
            PlayerRound(player1, dealer, gameDeck);
            if(player1.GetTotalValue() <= 21)
            {
                //Dealer flips card
                dealer.FlipInitialCard();
                // Reload the screen
                GameScreen(player1, dealer);
                DealerRound(dealer, player1, gameDeck);
                RoundSettlement(player1, dealer);                
            }
            
            // Clear the hands
            player1.ClearHand();
            dealer.ClearHand();
            // Ask if user would like to play again
            wishToPlay = ContinuePlayingPrompt();
            
            
            
            //wishToPlay = false;
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
void RoundSettlement(Player &player1, Dealer &dealer)
{    
    // Player has 21 and wins
    if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() < 21)
    {
        cout << "You have 21!! You win $" << (player1.GetCurrentBet() * 2) << endl;
        player1.CollectMoney(player1.GetCurrentBet() * 2);
    }
    // TIE of 21
    else if(player1.GetTotalValue() == 21 && dealer.GetTotalValue() == 21) 
    {
        cout << "Both you and the dealer have 21!" << endl
             << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
        player1.CollectMoney(player1.GetCurrentBet());
    } 
    // TIE of same values
    else if(player1.GetTotalValue() < 21 && player1.GetTotalValue() == dealer.GetTotalValue()) 
    {
        cout << "Both you and the dealer have " << player1.GetTotalValue() << "!" << endl 
             << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
        player1.CollectMoney(player1.GetCurrentBet());
    }
    // Player beats dealer
    else if(player1.GetTotalValue() < 21 && player1.GetTotalValue() > dealer.GetTotalValue())
    {
        cout << "You have " << player1.GetTotalValue() << " and the dealer has " << dealer.GetTotalValue() << endl;
        cout << "You beat the dealer!! You win $" << (player1.GetCurrentBet() * 2) << endl;
        player1.CollectMoney(player1.GetCurrentBet() * 2);
    }                
    else
    {
        cout << "Dealer has " << dealer.GetTotalValue() << ", Sorry you lost!!" << endl;
        // continue the round
    }
    
    
}

void DealerRound(Dealer &gameDealer, Player &gamePlayer, Deck &gameDeck)
{
    bool dealerContinue = true;
    while(dealerContinue)
    {
        if(gameDealer.GetTotalValue() < 17)
        {
            gameDealer.Hit(gameDeck.RemoveNextCard());
            GameScreen(gamePlayer, gameDealer);
        }
        else if(gameDealer.GetTotalValue() >= 17)
        {
            dealerContinue = false;
        }
    }  
}

void PlayerRound(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck)
{
    
    // Check if player has a total of 9,10,11 then ask for DoubleDown doubling initial bet and player will receive one more card
    //       player can also split if both cards are 5's and play it out normally
    if(PlayerDoubleDownCheck(gamePlayer))
    {     // True if player is doubling down              
        
    }
    else // False if not going to double down
    {
        if(PlayerSplitCheck(gamePlayer))
        {      // True if going to split                      
            cout << "Lets start with the Left Side of your split first..." << endl;                         
        }
        else
        {      // False if not going to split hand
            GameScreen(gamePlayer, gameDealer);            // Reload screen
            PlayerHitStandCheck(gamePlayer, gameDealer, gameDeck);                 
        }
    }
}

void PlayerHitStandCheck(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck)
{    
    bool continueHitting = true;                          // True if player chooses to hit
    bool valid = false;                                   // True if user input is valid, false if not
    char result;   
    while(continueHitting)
    {   
        do
        {
            cout << "Would you like to HIT or STAND(H/S)? ";
            cin >> result;   
            result = toupper(result);
            if(result == 'H')
            {      
                cout << "You chose to HIT!" << endl;
                gamePlayer.Hit(gameDeck.RemoveNextCard());
                //continueHitting = true;
                valid = true;
            }
            else if(result == 'S')
            {  
                cout << "You chose to STAND!" << endl;    
                continueHitting = false;             
                valid = true;
            }
            else
            {
                cerr << "Please enter 'H' for HIT, 'S' for STAND." << endl;
            }
        }
        while(valid == false); 
        
        GameScreen(gamePlayer, gameDealer);                          // Reload the screen
        //if value is greater than 21, inform of bust
        if(gamePlayer.GetTotalValue() > 21)
        {
            cout << "\nSorry, looks like you busted!!" << endl;      // might do this outside of function
            continueHitting = false;    
        }   
        else if(gamePlayer.GetTotalValue() == 21)  
        {
            cout << "\nLooks like you got 21!!" << endl;     // might do this outside of function
            continueHitting = false;
        }  
    }
    
}

bool PlayerSplitCheck(Player &gamePlayer) 
{
    bool splitting = false;                                   // True if player is splitting, false if not
    if(gamePlayer.CanSplit())  
    {  
        bool valid = false;                                   // True if user input is valid, false if not
        char result;               
        do
        {
            cout << "Would you like to split your hand(y/n)? ";
            cin >> result;   
            result = toupper(result);
            if(result == 'Y')
            {      
                cout << "You chose to split!" << endl;
                // call to splithand() in player class
                splitting = true;
                valid = true;
            }
            else if(result == 'N')
            {                
                valid = true;
            }
            else
            {
                cerr << "Please enter 'y' for yes, 'n' for no" << endl;
            }
        }
        while(valid == false);        
    }
    
    return splitting;
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

double BettingPrompt(double minimumBet, double maximumBet)
{
    double betAmount;
    cout << "\n(Minimum bet is $5, you may increase in $5 increments)"
         << "Place your bet: $";
    betAmount = GetValidDouble(minimumBet, maximumBet);                
    return betAmount;
}

bool CheckNaturalBlackjack(Dealer &dealer, Player &player, double playerBet)
{
    bool isRoundOver = false;                // true if blackjack was reached by anyone, false if not
    
    if(player.GetTotalValue() == 21 && dealer.GetTotalValue() == 21)
    {
        cout << "Both you and the dealer have BLACKJACK!" << endl
             << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
        //player.CollectMoney(playerBet);
        isRoundOver = true;
    } 
    else if(player.GetTotalValue() == 21 && dealer.GetTotalValue() < 21)
    {
        cout << "BlackJack!..... You win $" << ((playerBet * 2) * 1.5) << "!!!!" << endl;
        //player.CollectMoney(playerBet); ((playerBet * 2) * 1.5)
        isRoundOver = true;
    }
    else
    {
        cout << "\nNobody has Blackjack!!......" << endl;
    }
    
    return isRoundOver;                     // Unchanged if no conditional was met
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

bool PlayerDoubleDownCheck(Player &gamePlayer)
{
    bool doublingDown = false;                // True if player is doubling down, false if not
    bool valid = false;                       // True if user input is valid, false if not
    char result;
    if(gamePlayer.GetTotalValue() >= 9 && gamePlayer.GetTotalValue() <= 11)
    {        
        do
        {
            cout << "Would you like to Double-Down(y/n)? ";
            cin >> result;      
            
            result = toupper(result);
            if(result == 'Y')
            {      
                cout << "You chose to Double-Down!" << endl;
                doublingDown = true;
                valid = true;
            }
            else if(result == 'N')
            {                
                valid = true;
            }
            else
            {
                cerr << "Please enter 'y' for yes, 'n' for no" << endl;
            }
        }
        while(valid == false);        
    }
    return doublingDown;
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
		
//void ChoicePrompt(Player &gamePlayer, Deck &gameDeck)
//{
//    bool play = true;
//	bool valid = false;         // for valid input
//    char result;   
//    
//    cout << "What would you like to do: " << endl
//         << "(H) Hit\n(P) Stand\n(S) Split\n(D) Double-Down)" << endl;             
//    do
//    {                     
//        cout << "Choice: ";             
//        cin >> result;        
//        
//        result = toupper(result);
//        switch(result)
//        {
//            case 'H' : {
//                cout << "You chose to HIT"; // run the hit method  
//                gamePlayer.Hit(gameDeck.RemoveNextCard());                          
//                valid = true;   
//                break;
//            }                        
//            case 'P' : {
//                cout << "You chose to STAND"; // run the stand method
//                gamePlayer.Stand();   
//                valid = true; 
//                break;
//            }                        
//            case 'S' : {
//                cout << "You chose to SPLIT"; // run the split method
//                // splitting splits the cards and the initial bet amount is taken again for the split hand
//                // then the two hands are played with the original hand played first and then the split hand
////                gamePlayer.DoubleDown(gamePlayer.GetCurrentBet())
//                valid = true; 
//                break;
//            }                       
//                               
//            default : cerr << "Please enter H, P, S, or D" << endl;                          
//        }   
//    }
//    while(valid == false);
//}

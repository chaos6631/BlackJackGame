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
void PlayerNamePrompt(Player &player1);
bool PlayerDoubleDownCheck(Player &gamePlayer);
void PlayerHitStandCheck(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
bool PlayerSplitCheck(Player &gamePlayer);
void PlayerRound(Player &gamePlayer, Dealer &gameDealer, Deck &gameDeck);
void DealerRound(Dealer &gameDealer, Player &gamePlayer, Deck &gameDeck);
void RoundSettlement(Player &player1, Dealer &dealer);
//GUI FUNCTIONS
bool YesNoChoicePrompt(string message);

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
            PlayerNamePrompt(player1);
            dealer = Dealer("Dealer");
            // Start game :: SHould be added to GameBlackJack class as a method 
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
            //player1.Bet(BettingPrompt(MINIMUM_BET, player1.GetPlayerMoneyTotal()));
            
            // Deal cards
            DealCards(player1, dealer, gameDeck);
            
            // CheckNaturalBlackjack() : need to check for blackjack    
            if(!CheckNaturalBlackjack(dealer, player1, playerBet))  // False if nobody has a natural blackjack   
            {   
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
            }      
            // Clear the hands
            player1.ClearHand();
            dealer.ClearHand();
            // Ask if user would like to play again
            wishToPlay = ContinuePlayingPrompt();
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

bool BeginGamePrompt() // Should stay in BlacJackMin.cpp
{    
	bool play = false;

    if(GUI::YesNoChoicePrompt("\nWould you like to play a game of Blackjack(y/n)?"))
    {
        play = true;
    }
    else
    {
        //GameMessage("\nThat's too bad, maybe next time!! See ya.......\n");      //NOT CREATED YET
        cout << "\nThat's too bad, maybe next time!! See ya.......\n" << endl;
        play = false;
    }
    return play;
}

void PlayerNamePrompt(Player &player1)
{
    string playerName;
    cout << "Please enter your name: ";
    cin >> playerName;
    player1 = Player(playerName);
}

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
    else if(player1.GetTotalValue() <= 21 && player1.GetTotalValue() > dealer.GetTotalValue())
    {
        cout << "You have " << player1.GetTotalValue() << " and the dealer has " << dealer.GetTotalValue() << endl;
        cout << "You beat the dealer!! You win $" << (player1.GetCurrentBet() * 2) << endl;
        player1.CollectMoney(player1.GetCurrentBet() * 2);
    }
    // Dealer beats player
    else if(dealer.GetTotalValue() <= 21 && player1.GetTotalValue() < dealer.GetTotalValue())       
    {
        cout << "Dealer has " << dealer.GetTotalValue() << ", Sorry you lost!!" << endl;
        // continue the round
    } 
    // Dealer beats player
    else if(dealer.GetTotalValue() <= 21 && player1.GetTotalValue() <= 21 && player1.GetTotalValue() < dealer.GetTotalValue())       
    {
        cout << "Dealer has " << dealer.GetTotalValue() << ", Sorry you lost!!" << endl;
        // continue the round
    }             
    else
    {
        cout << "You have " << player1.GetTotalValue() << " and the dealer has BUSTED with " << dealer.GetTotalValue() << ".\n";
        cout << "You beat the dealer!! You win $" << (player1.GetCurrentBet() * 2) << endl;
        player1.CollectMoney(player1.GetCurrentBet() * 2);
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
            //Delay(1);
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
        gamePlayer.Hit(gameDeck.RemoveNextCard());
        GameScreen(gamePlayer, gameDealer);            // Reload screen
        //Delay(1);
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
            //GameMessage("\nWould you like to HIT or STAND(H/S)? ");
            cout << "Would you like to HIT or STAND(H/S)? ";
            cin >> result;   
            result = toupper(result);
            if(result == 'H')
            {      
                //GameMessage("\nYou chose to HIT!\n")
                cout << "You chose to HIT!" << endl;
                gamePlayer.Hit(gameDeck.RemoveNextCard());
                //continueHitting = true;
                valid = true;
            }
            else if(result == 'S')
            {  
                //GameMessage("\nYou chose to STAND!\n")
                cout << "You chose to STAND!" << endl;    
                continueHitting = false;             
                valid = true;
            }
            else
            {
                //GameMessage("\nPlease enter 'H' for HIT, 'S' for STAND.\n");
                cerr << "Please enter 'H' for HIT, 'S' for STAND." << endl;
            }
        }
        while(valid == false); 
        
        GameScreen(gamePlayer, gameDealer);                          // Reload the screen
        //if value is greater than 21, inform of bust
        if(gamePlayer.GetTotalValue() > 21)
        {
            //GameMessage("\nSorry, looks like you busted!!\n");
            cout << "\nSorry, looks like you busted!!" << endl;      // might do this outside of function
            continueHitting = false;    
        }   
        else if(gamePlayer.GetTotalValue() == 21)  
        {
            //GameMessage("\nLooks like you got 21!!\n");
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
        if(GUI::YesNoChoicePrompt("Would you like to split your hand(y/n)? "))
        {
            //GameMessage("\nYou chose to split!\n");
            // call to splithand() in player class
            splitting = true;
        }            
    }
    
    return splitting;
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
    //Delay(0.5);
    //cout << "test";
    for(int cardsPerPlayer = 1;cardsPerPlayer <= 2; cardsPerPlayer++)
    {
        gamePlayer.AddCard(gameDeck.RemoveNextCard());
        //Delay(0.5);
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
        //Delay(0.5);
        GameScreen(gamePlayer, gameDealer);
    }                        
}

bool PlayerDoubleDownCheck(Player &gamePlayer)
{
    bool doublingDown = false;                // True if player is doubling down, false if not
    
    if(gamePlayer.GetTotalValue() >= 9 && gamePlayer.GetTotalValue() <= 11)
    {     
        if(GUI::YesNoChoicePrompt("\nWould you like to Double-Down(y/n)? "))   
        {
            //string message = "You have chosen to double down with a bet of $" + gamePlayer.GetCurrentBet() + "\n";
            //GameMessage(message);
            
            gamePlayer.DoubleDown((gamePlayer.GetCurrentBet()));
            cout << "You have chosen to double down with a bet of $" << gamePlayer.GetCurrentBet() << endl;
            doublingDown = true;
        }        
    }
    return doublingDown;
}

// GUI Function
bool YesNoChoicePrompt(string message)
{
    bool answer = false;                      // True if player chooses Yes, false if No
    bool valid = false;                       // True if user input is valid, false if not
    char result;
          
    do
    {
        cout << message;
        cin >> result;      
        
        result = toupper(result);
        if(result == 'Y')
        {                  
            answer = true;
            valid = true;
        }
        else if(result == 'N')
        {                
            valid = true;
        }
        else
        {
            cerr << "Please enter 'y/Y' for yes, 'n/N' for no" << endl;
        }
    }
    while(valid == false);    
    return answer;
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


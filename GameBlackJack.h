/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097, Christopher Alexander #100360337
* Date: 
*
* Description:  A Game class that reperesents an instance of a blackjack game
*				
*/

#ifndef _BLACKJACKGAME
#define _BLACKJACKGAME

#include "MyInputValidation.h"
#include "BlackJackGUI.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <fstream>			// needed for ifstream class
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
using namespace GUI;       // Should prefix functions anyways for clarity

class BlackJackGame
{
    public:
        static const double MINIMUM_BET; 
        static const int MAXIMUM_SCORE;          
        // default Constructor
        BlackJackGame(); // Should be able to define it here as well
        // Parameterized Constructor 
		//BlackJackGame(Player& player) ;
    	// ACCESSORS
    	int GetCardCount() const;
        // MUTATORS        
        void BettingPrompt();
        bool CheckNaturalBlackjack();
        bool ContinuePlayingPrompt();
        void DealCards();
        void DealSplitHand();                        // Solely for TESTING purposes
        void DealerRound();
        void DecksToPlayWith();
        void PlayerNamePrompt();
        bool PlayerDoubleDownCheck();
        void PlayerHitStandCheck(bool isSplitHand);
        bool PlayerSplitCheck();
        void PlayerRound();
        void Round();
        void RoundSettlement(bool isSplitHand);
        void StartGame();
        void ShuffleDeck();
        void FillDeck();
        void ClearHands();
        bool LoadSavedGame();
        void SaveGame();
        void SaveGamePrompt();
		// OPERATORS
	private:
		Player m_player;
		Dealer m_dealer;
        Deck m_gameDeck;
};

/*************************
 FUNCTION DEFINITIONS
**************************/
//// Minimum bet should not be more than the default money amount for the Player class which is 100.
const double BlackJackGame::MINIMUM_BET = 5;  
const int BlackJackGame::MAXIMUM_SCORE = 21;       
const string SAVE_GAME_FILENAME = "saved_games.dat"; // File that stores the saved game
  
//// Constructor
BlackJackGame::BlackJackGame()
{
	
}

//// Betting Prompt
void BlackJackGame::BettingPrompt()
{
    int betAmount;
    bool valid = false;
    stringstream infoMessage;
    GUI::ClearScreen();                                 // Clear the screen
    GUI::DisplayBanner();                               // Display Game Title
    GUI::GameInfo(m_player);                            // Display Player information
    infoMessage << "\n(Minimum bet is $" << MINIMUM_BET << ", you may increase in $5 increments)" << "\nPlace your bet: $";
    GUI::GameMessage(infoMessage.str());
    
    while(!valid)
    {
        betAmount = myValidation::GetValidInteger(MINIMUM_BET, m_player.GetPlayerMoneyTotal());        
        if((betAmount % 5) > 0)
        {            
            GUI::GameMessage("\nINVALID!! Bet must be increments of 5.");
            GUI::GameMessage(infoMessage.str());
            valid = false;
        }
        else
        {
            valid = true;
        }
    }
    // need to create a validator that uses GetValidDouble and checks that the input value is an increment of 5
    m_player.Bet((double)betAmount); 
}

//// Check for Natural Blackjack
bool BlackJackGame::CheckNaturalBlackjack()
{
    bool isRoundOver = false;                // true if blackjack was reached by anyone, false if not
    stringstream infoMessage;
    
    if(m_player.GetTotalValue() == 21 && m_dealer.GetTotalValue() == 21)
    {        
        infoMessage << "Both you and the m_dealer have BLACKJACK!" << endl
                    << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
        m_dealer.FlipInitialCard();
        m_dealer.m_dealersTurn = true;
        GUI::GameScreen(m_player, m_dealer);
        GUI::GameMessage(infoMessage.str());
        m_player.CollectMoney(m_player.GetCurrentBet());
        isRoundOver = true;
    } 
    else if(m_player.GetTotalValue() == 21 && m_dealer.GetTotalValue() < 21)
    {
        infoMessage << "BlackJack!..... You win $" << (m_player.GetCurrentBet() * 3) << "!!!!" << endl;
        m_dealer.FlipInitialCard();
        m_dealer.m_dealersTurn = true;
        GUI::GameScreen(m_player, m_dealer);
        GUI::GameMessage(infoMessage.str());
        m_player.CollectMoney(m_player.GetCurrentBet() * 3); 
        isRoundOver = true;
    }
    else if(m_dealer.GetTotalValue() == 21 && m_player.GetTotalValue() < 21)
    {                
        infoMessage << "\nDealer has Blackjack!!...... You lose!" << endl;
        m_dealer.FlipInitialCard();
        m_dealer.m_dealersTurn = true;
        GUI::GameScreen(m_player, m_dealer);
        GUI::GameMessage(infoMessage.str());
        isRoundOver = true;
    }
    
    return isRoundOver;                     // Unchanged if no conditional was met
}

//// Continue Playing after a hand has been played
bool BlackJackGame::ContinuePlayingPrompt()
{
    bool play = true;	
	if(m_player.GetPlayerMoneyTotal() == 0)
	{
	    GUI::GameMessage("\nGAME OVER!!\n");
	    play = false;
    }
    else
    {
        if(GUI::YesNoChoicePrompt("\nWould you like to continue playing(y/n)?"))
        {
            play = true;
        }
        else
        {
            GUI::ClearScreen();
            GUI::DisplayBanner(); 
            GUI::GameInfo(m_player);
            SaveGamePrompt();
            //GUI::GameMessage("\nOk, see ya later!!\n");      //NOT CREATED YET
            cout << "\n\n\nOk, see ya later!!\n" << endl;
            play = false;
        }
    }
    return play;
}

//// Deal cards to the player and dealer
void BlackJackGame::DealCards()
{    
    //Delay(0.5);    
    for(int cardsPerPlayer = 1;cardsPerPlayer <= 2; cardsPerPlayer++)
    {
        m_player.AddCard(m_gameDeck.RemoveNextCard());
        //Delay(0.5);
        GUI::GameScreen(m_player, m_dealer);
        if(cardsPerPlayer == 1)
        {
            Card firstCard = m_gameDeck.RemoveNextCard();
            firstCard.m_isFaceUp = false; 
            m_dealer.AddCard(firstCard);
        }
        else
        {
            m_dealer.AddCard(m_gameDeck.RemoveNextCard());
        }                
        //Delay(0.5);
        GameScreen(m_player, m_dealer);
    }                        
}

//// Deals a splitable hand to the player
void BlackJackGame::DealSplitHand()
{   //int value, char valueChar , string suit, char suitChar, bool faceUp = true
    Card card1(5, '5', "Hearts", 'H', true);
    Card card2(5, '5', "Clubs", 'C', true);
    Card card3(6, '6', "Hearts", 'H', true);
    Card card4(10, 'J', "Hearts", 'H', true);
    m_player.AddCard(card1);
    m_player.AddCard(card2);
    m_dealer.AddCard(card3);
    m_dealer.AddCard(card4);
}

//// Play Dealers hand
void BlackJackGame::DealerRound()
{
    bool dealerContinue = true;
    while(dealerContinue)
    {
        if(m_dealer.GetTotalValue() < 17)
        {
            m_dealer.Hit(m_gameDeck.RemoveNextCard());
            GameScreen(m_player, m_dealer);
            //Delay(1);
        }
        else if(m_dealer.GetTotalValue() >= 17)
        {
            dealerContinue = false;
        }
    }  
}

//// Ask user the number of decks they wish to play with
void BlackJackGame::DecksToPlayWith()
{
    int numberOfDecks;                                                       // The number of decks the user chooses  
    const int NUM_OF_CHOICES = 5;
    int choices[NUM_OF_CHOICES] = {1, 2, 4, 6, 8};                           // The allowable number of decks to choose from                                   
    bool valid = false;                                                      // true if input is valid, false if not    
    stringstream howManyDecks;                                               // message prompt
    
    howManyDecks << "\nHow many decks would you like to play with(";       
    //// Add choices to message prompt    
    for(int count = 0; count < NUM_OF_CHOICES; count++)
    {
        if(count < (NUM_OF_CHOICES - 1))
        {                   
            howManyDecks << choices[count] << ", ";    
        }
        else
        {            
            howManyDecks << choices[count] << ")? ";
        }        
    }        
    //// While the user inputs an INVALID choice do this....
    while(!valid)
    {        
        GUI::GameMessage(howManyDecks.str());
        myValidation::ClearInputBuffer();
        numberOfDecks = myValidation::GetValidInteger();        
        
        for(int count = 0; count < NUM_OF_CHOICES; count++)
        {
            if(numberOfDecks == choices[count])
            {
                valid = true;
            }            
        }
        if(!valid)
        {           
            GUI::GameMessage("\nThat is not a valid number of decks!\n");                 
        }
    }
    m_gameDeck.SetDeckTotal(numberOfDecks);
    m_gameDeck.FillDeck();    
}

//// Get user input for the players name
void BlackJackGame::PlayerNamePrompt()
{
    string playerName;
    GUI::GameMessage("\nPlease enter your name: ");    
    cin >> playerName;
    myValidation::ClearInputBuffer();
    m_player = Player(playerName);
}

//// Check if the player wishes to Double-Down
bool BlackJackGame::PlayerDoubleDownCheck()
{
    bool doublingDown = false;                // True if player is doubling down, false if not
    stringstream infoMessage;
    
    if(m_player.GetTotalValue() >= 9 && m_player.GetTotalValue() <= 11)
    {   
        if(m_player.GetCurrentBet() <= m_player.GetPlayerMoneyTotal())
        {
            if(YesNoChoicePrompt("\nWould you like to Double-Down(y/n)? "))   
            {      
                m_player.DoubleDown();
                infoMessage << "You have chosen to double down with a bet of $" << m_player.GetCurrentBet() << endl;
                GUI::GameMessage(infoMessage.str());
                doublingDown = true;
                GUI::PauseGame();                
            }
        }                  
    }
    return doublingDown;
}

//// Player choses to Hit or Stand
void BlackJackGame::PlayerHitStandCheck(bool isSplitHand)
{
    bool continueHitting = true;                          // True if player chooses to hit
    bool valid = false;                                   // True if user input is valid, false if not
    char result;   
    int playerCardsTotal;
    while(continueHitting)
    {   
        do
        {
            GameMessage("\nWould you like to HIT or STAND(H/S)? ");            
            cin >> result;   
            result = toupper(result);// Convert to uppercase
            
            if(result == 'H')        // Chose to hit
            {      
                GameMessage("\nYou chose to HIT!\n");                
                m_player.Hit(m_gameDeck.RemoveNextCard(), isSplitHand);                
                valid = true;
            }
            else if(result == 'S')   // Chose to stand
            {  
                GameMessage("\nYou chose to STAND!\n");                
                continueHitting = false;             
                valid = true;
            }
            else                     // INVALID entry
            {
                GameMessage("\nPlease enter 'H' for HIT, 'S' for STAND.\n");                
            }
        }
        while(valid == false); 
        
        GameScreen(m_player, m_dealer);         // Reload the screen
        
        //// Set card total depending on which hand is being played
        if(isSplitHand)
        {
            playerCardsTotal = m_player.GetSplitTotalValue();      
        }
        else
        {
            playerCardsTotal = m_player.GetTotalValue();    
        }
        //// if value is greater than 21, inform of bust
        if(playerCardsTotal > 21)
        {                       
            continueHitting = false;    
        }   
        else if(playerCardsTotal == 21)  
        {
            //GameMessage("\nLooks like you got 21!!\n");            
            continueHitting = false;
        }  
    }
}

//// Check if the player can split their hand, proceed to do so if they choose
bool BlackJackGame::PlayerSplitCheck()
{
    bool splitting = false;                                   // True if player is splitting, false if not
    if(m_player.CanSplit())  
    {           
        if(YesNoChoicePrompt("Would you like to split your hand(y/n)? "))
        {
            GameMessage("\nYou chose to split!\n");
            m_player.SplitHand();         // call to splithand() in player class
            splitting = true;
        }            
    }    
    return splitting;
}

//// Play out the players hand
void BlackJackGame::PlayerRound()
{
    //// Check if player has a total of 9,10,11 then ask for DoubleDown doubling initial bet and player will receive one more card
    //// player can also split if both cards are 5's and play it out normally.
    
    if(PlayerDoubleDownCheck())                            // True if player is doubling down   
    {                
        m_player.Hit(m_gameDeck.RemoveNextCard(), false);  // False because it is not a splithand
        GameScreen(m_player, m_dealer);                    // Reload screen        
    }
    else                                                   // False if not going to double down
    {
        if(PlayerSplitCheck())
        {      // True if going to split  
            GameScreen(m_player, m_dealer);                // Reload screen
            GUI::GameMessage("\nLets start with the Left Side of your split first...\n"); 
            PlayerHitStandCheck(false);                    // False becasue it is not a splithand  
            GameScreen(m_player, m_dealer);                // Reload screen
            GUI::GameMessage("\nNow for the Right Side of your split!\n"); 
            PlayerHitStandCheck(true);                     // True because it is a splithand          
        }
        else
        {      // False if not going to split hand
            GameScreen(m_player, m_dealer);                // Reload screen
            PlayerHitStandCheck(false);                    // False becasue it is not a splithand       
        }
    }
}

//// Decide the winner of the hand and distribute winnings accordingly
void BlackJackGame::RoundSettlement(bool isSplitHand)
{
    int playerTotal = m_player.GetTotalValue();
    double playerBet = m_player.GetCurrentBet();
    stringstream infoMessage;
    if(isSplitHand)
    {
        playerTotal = m_player.GetSplitTotalValue();
        playerBet = m_player.GetCurrentSplitBet();
    }
    
    if(playerTotal <= MAXIMUM_SCORE)
    {
       // Player has 21 and wins
        if(playerTotal == MAXIMUM_SCORE && m_dealer.GetTotalValue() < MAXIMUM_SCORE)
        {
            infoMessage << "You have 21!! You win $" << (playerBet * 2) << endl;           
            GUI::GameMessage(infoMessage.str());
            m_player.CollectMoney(playerBet * 2);
        }
        // TIE of 21
        else if(playerTotal == MAXIMUM_SCORE && m_dealer.GetTotalValue() == MAXIMUM_SCORE) 
        {
            infoMessage << "Both you and the dealer have 21!" << endl
                        << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
            GUI::GameMessage(infoMessage.str());
            m_player.CollectMoney(playerBet);
        } 
        // TIE of same values
        else if(playerTotal < MAXIMUM_SCORE && playerTotal == m_dealer.GetTotalValue()) 
        {
            infoMessage << "Both you and the dealer have " << playerTotal << "!" << endl 
                        << "Game is a Stand-Off(tie), you get your initial bet back!" << endl;
            GUI::GameMessage(infoMessage.str());
            m_player.CollectMoney(playerBet);
        }
        // Player beats dealer
        else if(playerTotal <= MAXIMUM_SCORE && playerTotal > m_dealer.GetTotalValue())
        {
            infoMessage << "You have " << playerTotal << " and the dealer has " << m_dealer.GetTotalValue() << endl
                        << "You beat the dealer!! You win $" << (playerBet * 2) << endl;
            GUI::GameMessage(infoMessage.str());
            m_player.CollectMoney(playerBet * 2);
        }
        // Dealer beats player
        else if(m_dealer.GetTotalValue() <= MAXIMUM_SCORE && playerTotal < m_dealer.GetTotalValue())       
        {
            infoMessage << "Dealer has " << m_dealer.GetTotalValue() << ", Sorry you lost!!" << endl;
            GUI::GameMessage(infoMessage.str());
            // continue the round
        }               
        else
        {
            infoMessage << "You have " << playerTotal << " and the dealer has BUSTED with " << m_dealer.GetTotalValue() << "." << endl
                        << "You beat the dealer!! You win $" << (playerBet * 2) << endl;
            GUI::GameMessage(infoMessage.str());
            m_player.CollectMoney(playerBet * 2);
        }
    }
    else
    {
        GUI::GameMessage("Sorry, Looks like you BUSTED!!!\n");
    }
}

//// Play a full round
void BlackJackGame::Round()
{
    //Reload the screen
    GameScreen(m_player, m_dealer);
    PlayerRound();
    //// Player has not busted and doesn't have a split hand
    if(m_player.GetTotalValue() <= 21 || m_player.GetCurrentSplitBet() == 0)
    {
        //Dealer flips card
        m_dealer.FlipInitialCard();
        // Reload the screen
        GameScreen(m_player, m_dealer);
        DealerRound();        
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);           
        GUI::GameMessage("\n            RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n"); 
        RoundSettlement(false);    
        GUI::ResetConsoleColour();     
    }
    //// Player has busted and doesn't have a split  
    else if(m_player.GetTotalValue() > 21 || m_player.GetCurrentSplitBet() == 0)
    {
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);           
        GUI::GameMessage("\n            RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n"); 
        RoundSettlement(false);  
        GUI::ResetConsoleColour();     
    }
    //// Player has not busted and has a split
    else if(m_player.GetTotalValue() <= 21 || m_player.GetSplitTotalValue() <= 21)
    {
        //Dealer flips card
        m_dealer.FlipInitialCard();
        // Reload the screen
        GameScreen(m_player, m_dealer);
        DealerRound();  
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);      
        GUI::GameMessage("\n      LEFT SIDE RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n");
        RoundSettlement(false);   
        //GUI::ResetConsoleColour();  
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);           
        GUI::GameMessage("\n      RIGHT SIDE RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n"); 
        RoundSettlement(true);         
        GUI::ResetConsoleColour();     
    }  
    //// Player has split and has busted with both hands
    else if(m_player.GetTotalValue() > 21 && m_player.GetSplitTotalValue() > 21)
    {
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);      
        GUI::GameMessage("\n      LEFT SIDE RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n");
        //GUI::ResetConsoleColour(); 
        RoundSettlement(false);   
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_GREEN);           
        GUI::GameMessage("\n      RIGHT SIDE RESULTS");
        GUI::GameMessage("\n''''''''''''''''''''''''''''''''\n"); 
        RoundSettlement(true); 
        GUI::ResetConsoleColour();               
    }
    
    // Replenish the game deck if card count drops below 50% 
    if(m_gameDeck.CardsRemaining() < (m_gameDeck.GetMaxCardCount() / 2))
    {
        FillDeck();                
    }                       
}

//// Starts game
void BlackJackGame::StartGame()
{
    if(!LoadSavedGame())              // If true load saved player data, if false prompt player for name
    {
        PlayerNamePrompt();
    }  
    DecksToPlayWith();        
    m_gameDeck.Shuffle();    
    GUI::ClearScreen();                                 // Clear the screen
    GUI::DisplayBanner();                              // Display Game Title
    GUI::GameInfo(m_player);                           // Display Player information
}

bool BlackJackGame::LoadSavedGame()
{
    
    ifstream inFile;								         // an ifstream object to connect to a file for reading
    stringstream output;							         // the ouput string to be stored in the outFile object
    bool loadGame = false;	
	//if (FILE *file = fopen(SAVE_GAME_FILENAME.c_str(), "r")) 
	inFile.open(SAVE_GAME_FILENAME.c_str());					     // Open the file to be read from 	
		
 	/** If the input file could not be opened **/
 	if(inFile.fail()) 
 	{ 		 	    
		loadGame = false;
 	}
 	/** Read from the file! **/ 
 	else
    {        
        if(GUI::YesNoChoicePrompt("\nWould you like to load your previous game(y/n)?"))
        {
            string name;
            double money;
            // Read all the contents from the file and store as new player object. 
                  
			while(inFile.good())
			{			
				inFile >> name >> money;			// Read contents and store in the variables
				if(!inFile.fail())
				{		 	
				 	output << name << " " << money;					// Create output content from file contents	
                    //cout << name << " " << money;			 	   // TESTING	   	
				}					
			}					
            m_player = Player(name, money);            
            inFile.close();
            loadGame = true;
        }
        else
        {
            inFile.close();
        }    
    }  
    
    return loadGame;
}

void BlackJackGame::SaveGame()
{
    
    ofstream outFile;								            // an ofstream object to connect to a file for writing    
    stringstream output;							            // the ouput string to be stored in the outFile object
	string error = "";								            // string for error message	
    try
    {
        output << m_player.GetPlayerName() << " " << m_player.GetPlayerMoneyTotal();
        //// Save current game        
		outFile.open(SAVE_GAME_FILENAME.c_str(), fstream::in | fstream::out | fstream::trunc);	 	

		/** If the file is successfully created...., otherwise throw error and end program **/
		if(!outFile.is_open())			
		{	
			error = "Game NOT Saved!!";	
			error += "\n\n\nThe file \"" + SAVE_GAME_FILENAME;	// Set the error message if unable to open the file	for writing	
			error += "\" was NOT successfully created for writing. \nContact an IT Representative to diagnose the problem."; 
			throw ios::failure(error);
		}
		else      /** File opened successfully.. **/
		{
		    GUI::GameMessage("Saving Game");		
		    for(int count = 1; count <= 5; count++)				       /**************SIMULATED DELAY***************/
			{														   // Simulated delay for 1 second for user interaction,					
				//GUI::Delay(0.1);	
                GUI::GameMessage("..");										 		// just to slow things down a bit. Not required	    				
			}	
			GUI::GameMessage("Game Saved!!!");			
			outFile << output.str();						// Write the contents of output to the file				
		}
    }
    catch(ifstream::failure& error)	
	{
		cerr << "\n\n\nError: " << error.what() << endl;		// If there are ERRORS inform the user
	}
	catch(exception& error)	
	{
		cerr << "\n\n\nError: " << error.what() << endl;		// If there are ERRORS inform the user
	}    
    
}


void BlackJackGame::SaveGamePrompt()
{
    if(GUI::YesNoChoicePrompt("\nWould you like to save your game(y/n)?"))
    {
         SaveGame();
    }
}

//// Shuffle the game deck
void BlackJackGame::ShuffleDeck()
{
    m_gameDeck.Shuffle();
}

//// Replenish the game deck and shuffle
void BlackJackGame::FillDeck()
{
    m_gameDeck.FillDeck();
    m_gameDeck.Shuffle();
}

//// Clear the player and dealer hands
void BlackJackGame::ClearHands()
{
    m_player.ClearHand();
    m_dealer.ClearHand(); 
    m_dealer.m_dealersTurn = false;   
}

int BlackJackGame::GetCardCount() const
{
    int count;
    count = m_gameDeck.CardsRemaining();
    return count;
}
#endif


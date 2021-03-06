/*
* Project Name: Final Project: BlackJack
* Author: Chris Calder #100601097, Christopher Alexander #100360337
* Date: November 21, 2016
*
* Description:  A library of screen output functions that represent the GUI interface of the GameBlackJack class
*				
*/
#ifndef _BLACKJACKGUI
#define _BLACKJACKGUI

#include "Player.h"
#include "Dealer.h"
#include <iostream>
#include <iomanip> 					// for output formatting
#include <string>					// for string
#include <sstream>					// for stringstream
#include <cstdlib>					// for system()
#include <ctime>

using namespace std;
namespace GUI
{
    /*************************
     FUNCTION DECLARATIONS
    **************************/
    /**	Delay function
	 * - Delays the program for a specified amount of time in seconds
     *  @param seconds: the number of seconds to delay the program
     *	@returns void
	*/
    void Delay(unsigned int milliseconds);
    
    /**	DisplayBanner function
	 * - Displays the game logo     
     *	@returns void
	*/
    void DisplayBanner();
         
    /**	GameInfo function
	 * - Displays the game information for the human player
     *  @param player1: the player object referenced for information
     *	@returns void
	*/          
    void GameInfo(Player& player1);
    
    /**	GameScreen function
	 * Calls DisplayBanner(), GameInfo(), and RoundScreen() together in that order, main display function.
	 *
	 * @param  player1: The human player object to be referenced
	 * @param  dealer: The dealer player object to be referenced
	 * @returns void
	*/
    void GameScreen(Player& player1, Dealer& dealer);
    
    /**	RoundScreen function
	 * 
	 *
     * @param  player1: The human player object to be referenced
	 * @param  dealer: The dealer player object to be referenced
	 * @return A validated int input by the user.
	*/
    void RoundScreen(Player& player1, Dealer& dealer);
    
    /**	YesNoChoicePrompt function
	 *
     * @param  string message: The prompt to be output to the user	 
	 * @return True for Yes, False for No.
	*/
    bool YesNoChoicePrompt(string message);
    
    /**	ClearScreen function
	 *
     *  Clear all output from the screen.	 
	*/
    void ClearScreen();
    
    /**	GameMessage function
	 *
     * @param  string message: The feedback message to be output to the user	 
	 * @return void.
	*/
    void GameMessage(string message);
    
    /**	PauseGame function
	 *
     * Pauses game and waits for user to press any key to proceed 
	 * @return void.
	*/
    void PauseGame();
    
    /**	SetConsoleColour function
	 *  (code snippet taken from http://stackoverflow.com/questions/25559077/how-to-get-background-color-back-to-previous-color-after-use-of-std-handle)
	 *  Sets the colour of the text in the console window 
	 *
     * @param  Attributes: attributes taken from Console Screen Buffer	 
     * @param  Colour: console colour to be set
	 * @return void.
	*/
    void SetConsoleColour(DWORD Colour);

    /**	ResetConsoleColour function
	 *  (code snippet taken from http://stackoverflow.com/questions/25559077/how-to-get-background-color-back-to-previous-color-after-use-of-std-handle)
	 *  Resets the colour of the text in the console window to default
	 *  
     * @param  Attributes: attributes taken from Console Screen Buffer 
	 * @return void.
	*/
    void ResetConsoleColour();
    
    /*************************
     GLOBALS
    **************************/
    static WORD Attributes = 0;
    
    /*************************
     FUNCTION DEFINITIONS
    **************************/
    void Delay(unsigned int milliseconds)
    {	
        //// LINUX Systems
    	//clock_t startTime = clock();							    // Start time for delay
    	//clock_t endTime = milliseconds + startTime;			    // End time for delay is seconds * 1000 milliseconds after start time
    	//while(clock() != endTime);								// Loop to simulate delay	
    	
    	//// Windows Systems
        Sleep(milliseconds);
    } // END DELAY
    
    void DisplayBanner()
    {
        
    //    cout << "====================================================================================================" << endl
    //         << "=       _/_/_/    _/          _/_/      _/_/_/  _/    _/        _/    _/_/      _/_/_/  _/    _/   =" << endl
    //         << "=      _/    _/  _/        _/    _/  _/        _/  _/          _/  _/    _/  _/        _/  _/      =" << endl
    //         << "=     _/_/_/    _/        _/_/_/_/  _/        _/_/            _/  _/_/_/_/  _/        _/_/         =" << endl
    //         << "=    _/    _/  _/        _/    _/  _/        _/  _/    _/    _/  _/    _/  _/        _/  _/        =" << endl
    //         << "=   _/_/_/    _/_/_/_/  _/    _/    _/_/_/  _/    _/    _/_/    _/    _/    _/_/_/  _/    _/       =" << endl
    //         << "====================================================================================================" << endl;

//        cout << "====================================================================================================" << endl
//             << "=       ####### ####         ####  ###### ###  ##  ######     ####  ###### ###  ##                 =" << endl
//             << "=        ###  ## ###        ##### ###  ## ### ##   ## ###    ##### ###  ## ### ##                  =" << endl
//             << "=        ######  ###       ## ### ###     #####       ###   ## ### ###     #####                   =" << endl
//             << "=        ###  ## ###      ##  ### ###     #####       ###  ##  ### ###     #####                   =" << endl
//             << "=        ###  ## ###     ######## ###     ### ##      ### ######## ###     ### ##                  =" << endl
//             << "=        ###  ## ###   # ##   ### ###  ## ###  ##  ## ### ##   ### ###  ## ###  ##                 =" << endl
//             << "=        ######  ####### ##   ###  #####  ###  ##   ####  ##   ###  #####  ###  ##                 =" << endl
//             << "=                         ###                  ##          ###                  ##                 =" << endl
//             << "====================================================================================================" << endl;
        cout << "===================================================================================================================" << endl;
        GUI::SetConsoleColour(FOREGROUND_INTENSITY | FOREGROUND_BLUE);  
        cout << "=         ______     __         ______     ______     __  __       __     ______     ______     __  __            =" << endl
             << "=        /\\  == \\   /\\ \\       /\\  __ \\   /\\  ___\\   /\\ \\/ /      /\\ \\   /\\  __ \\   /\\  ___\\   /\\ \\/ /            ="<< endl
             << "=        \\ \\  __<   \\ \\ \\____  \\ \\  __ \\  \\ \\ \\____  \\ \\  _-.    _\\_\\ \\  \\ \\  __ \\  \\ \\ \\____  \\ \\  _-.           =" << endl
             << "=         \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\ /\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\         ="<< endl
             << "=          \\/_____/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_/\\/_/ \\/_____/   \\/_/\\/_/   \\/_____/   \\/_/\\/_/         ="<< endl;
        GUI::ResetConsoleColour();  
        cout << "===================================================================================================================" << endl; 
    } //// END BANNER

    void GameInfo(Player& player1)
    {         
        cout << "                                   Player Name: " << player1.GetPlayerName() 
             << "          Chip Amount: $" << player1.GetPlayerMoneyTotal() << endl 
             << "===================================================================================================================" << endl;
    }// END INFO
    
    void GameMessage(string message)
    {
        cout << message;           
    }// END GAME MESSAGE
    
    void GameScreen(Player& player1, Dealer& dealer)
    {
        system("CLS");
        DisplayBanner();
        GameInfo(player1);
        RoundScreen(player1, dealer);
    }// END GAMESCREEN
    
    void RoundScreen(Player& player1, Dealer& dealer)
    {
        int minLength = dealer.GetPlayerName().length();
        int playerNameLength = player1.GetPlayerName().length();
        string filler;

        // If players name is shorter than dealers, add space for player name
        if(playerNameLength < minLength)
        {
            string diff1((minLength - playerNameLength), ' ');
            filler = diff1;             
        }        
        //// Player Hand
        cout << "\n---------------------------------------------------------" << endl;        
        cout << filler << player1.GetPlayerName() << "'s Hand -> Total("  
             << player1.GetTotalValue() << "): ";
        player1.ShowCards();
        cout << endl << "---------------------------------------------------------" << endl; 
                
        
        filler.clear();
        // If players name is longer than dealers, add space for dealer name
        if(playerNameLength > minLength)                  
        {
            string diff2((playerNameLength - minLength), ' ');        
            filler = diff2;                    
        }    
        //// Split Hand
        if(player1.GetSplitTotalValue() > 0)
        {            
            cout << filler << "   Split Hand -> Total("
                 << player1.GetSplitTotalValue() << "): ";
            player1.ShowSplitCards();
            cout << endl << "---------------------------------------------------------" << endl;
        }
        //// Dealer Hand  
        cout << filler << dealer.GetPlayerName() << "'s Hand -> Total(";
        if(dealer.m_dealersTurn)
        {
            cout << dealer.GetTotalValue();   
        }
        else
        {
            cout << "??";
        }        
        cout << "): ";
        dealer.ShowCards();     
        cout << endl << "---------------------------------------------------------" << endl;            
    }// END ROUNDSCREEN
    
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
    } // END YESNO
    
    void ClearScreen()
    {
        system("CLS");                                     
    }// END CLEAR SCREEN
    
    void PauseGame()
    {
        system("pause");
    } // END PAUSE GAME

    void SetConsoleColour(DWORD Colour)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        Attributes = Info.wAttributes;
        SetConsoleTextAttribute(hStdout, Colour);
    } // END SETCONSOLECOLOUR
    
    void ResetConsoleColour()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
    } // END RESETCONSOLECOLOUR



}
#endif

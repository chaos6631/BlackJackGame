/*
* Project Name: Final Project: BlackJack
* Author: Chris Calder #100601097, 
* Date: November 21, 2016
*
* Description:  A library of screen output functions that represent the GUI interface of the GameBlackJack class
*				
*/
#ifndef _BLACKJACKGUI
#define _BLACKJACKGUI

#include "Player.h"
//#include "Dealer.h"
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
    void Delay(double seconds);
    
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
    void GameScreen(Player& player1, Player& dealer);
    
    /**	RoundScreen function
	 * 
	 *
     * @param  player1: The human player object to be referenced
	 * @param  dealer: The dealer player object to be referenced
	 * @return A validated int input by the user.
	*/
    void RoundScreen(Player& player1, Player& dealer);
    
    /*************************
     FUNCTION DEFINITIONS
    **************************/
    void Delay(double seconds)
    {	
    	clock_t start_time = clock();							// Start time for delay
    	clock_t end_time = seconds * 1000 + start_time;			// End time for delay is seconds * 1000 milliseconds after start time
    	while(clock() != end_time);								// Loop to simulate delay	
    } 
    
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
        cout << "===================================================================================================================" << endl
             << "=         ______     __         ______     ______     __  __       __     ______     ______     __  __            =" << endl
             << "=        /\\  == \\   /\\ \\       /\\  __ \\   /\\  ___\\   /\\ \\/ /      /\\ \\   /\\  __ \\   /\\  ___\\   /\\ \\/ /            ="<< endl
             << "=        \\ \\  __<   \\ \\ \\____  \\ \\  __ \\  \\ \\ \\____  \\ \\  _-.    _\\_\\ \\  \\ \\  __ \\  \\ \\ \\____  \\ \\  _-.           =" << endl
             << "=         \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\ /\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\         ="<< endl
             << "=          \\/_____/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_/\\/_/ \\/_____/   \\/_/\\/_/   \\/_____/   \\/_/\\/_/         ="<< endl
             << "===================================================================================================================" << endl; 
    }

    void GameInfo(Player& player1)
    {
        cout << "= Player Name: " << player1.GetPlayerName() << "          Chip Amount: $" << player1.GetPlayerMoneyTotal() << endl
             << "====================================================================================================" << endl;
    }
    
    void GameScreen(Player& player1, Player& dealer)
    {
        system("CLS");
        DisplayBanner();
        GameInfo(player1);
        RoundScreen(player1, dealer);
    }
    
    void RoundScreen(Player& player1, Player& dealer)
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
        cout << "--------------------------------------------------------------" << endl;
        cout << filler << player1.GetPlayerName() << "'s Hand: ";
        player1.ShowCards();
        cout << "           Card Total : " << player1.GetTotalValue()
             << "\n--------------------------------------------------------------" << endl;
        
        filler.clear();
        // If players name is longer than dealers, add space for dealer name
        if(playerNameLength > minLength)                  
        {
            string diff2((playerNameLength - minLength), ' ');        
            filler = diff2;                    
        }    
        cout << filler << dealer.GetPlayerName() << "'s Hand: ";
        dealer.ShowCards();
        cout << "           Card Total : " << dealer.GetTotalValue()
             << "\n--------------------------------------------------------------" << endl;
    }
}
#endif

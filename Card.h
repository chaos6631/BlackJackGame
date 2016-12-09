/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097, Christopher Alexander #100360337
* Date: 
*
* Description:  A Playing Card Class file
*				
*/
#ifndef _PLAYINGCARD
#define _PLAYINGCARD

#include <cstdlib>					// for system()
#include <iomanip> 					// for output formatting
#include <iostream>
#include <stdexcept>
#include <string>					// for string
#include <sstream>					// for stringstream

// Required for Card Symbol Characters
#include <clocale>
#include <cstdio>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <wchar.h>

#pragma execution_character_set( "utf-8" )

using namespace std;

/********************* 
 CARD CLASS DECLARATION
 **********************/ 

class Card 
{
	public:
        //// Card Class: Validation should come from the Deck class to ensure that Card can be used in any game
		//// DEFAULT CONSTRUCTOR
		Card(): m_value(1), m_valueChar('A'), m_suit("Hearts"), m_suitChar('H'), m_isFaceUp(true) {}
		
		//// PARAMATERIZED CONSTRUCTOR
		Card(int value, char valueChar , string suit, char suitChar, bool faceUp = true);
		
		//// COPY CONSTRUCTOR
        Card(const Card &source); // NEW! copy constructor	
		
		//// MUTATORS
        void SetValue(int value) { m_value = value; };
        void SetValueChar(char valueChar) { m_valueChar = valueChar; };
        void SetSuit(string suit) { m_suit = suit; };
        void SetSuitChar(char suitChar) { m_suitChar = suitChar; };
        
		//// ACCESORS
		int GetValue() const { return m_value; };
		char GetValueChar() const { return m_valueChar; };
		string GetSuit() const { return m_suit; };
		char GetSuitChar() const { return m_suitChar;	};
		void ShowCardDetails() const;
		void ShowCardShortDetails() const;
		void OutputSuitChar(char suit) const;
		
		//// OPERATORS
		Card& operator=(const Card &source); // assignment operator	
		operator string () const; // convert the obj to a string.
		
		//// PUBLIC MEMBER VARIABLES
		bool m_isFaceUp; // true if face-up, false if face-down
	
	private:
	    //// MEMBER VARIABLES
		int m_value;
		char m_valueChar;
		string m_suit;
		char m_suitChar;                                        // uses Unicode to display actual suit symbol
		
};

/********************* 
 CARD CLASS DEFINITIONS
 **********************/ 
//// Parameterized Constructor
Card::Card(int value, char valueChar , string suit, char suitChar, bool faceUp)
{
    if(value == 0)
    {
        string errorMsg = "Value of card can't be 0";
        throw out_of_range(errorMsg);
    }
    else
    {
        m_value = value;
        m_valueChar = valueChar;
        m_suit = suit;
        m_suitChar = suitChar;
        m_isFaceUp = faceUp;
    }
}

//// Copy Constructor
Card::Card(const Card &source)
{
    m_value = source.m_value;
    m_valueChar = source.m_valueChar;
    m_suit = source.m_suit;
    m_suitChar = source.m_suitChar;
    m_isFaceUp = source.m_isFaceUp;
}

//// Operator=
Card& Card::operator=(const Card &source)
{
    m_value = source.m_value;
    m_valueChar = source.m_valueChar;
    m_suit = source.m_suit;
    m_suitChar = source.m_suitChar;
    m_isFaceUp = source.m_isFaceUp;
    
    return *this;
}

//// ShowCardDetails() : Used for testing purposes, shows all details
void Card::ShowCardDetails() const 
{    
    string visibility;               // Face-Up, Face-Down
    string value;                    // ValueChar
    if(m_isFaceUp)
    {
        visibility = "Face-Up";
    }
    else
    {
        visibility = "Face-Down";
    }
    
    if (m_valueChar == 'X')
    {
        value = "10";
    }
    else
    {
        value.push_back(m_valueChar);            
    }
	cout << "           Card Details" << endl
	     << "================================" << endl
	     << "Card Visibility: " << visibility << endl
	     << "      Card Suit: " << m_suit << "(" << m_suitChar << ")" << endl
         << "    Card Values: " << m_value << " represented by '" << value << "'\n";
}

//// ShowCardShortDetails() : Used for game shows minimal details in game friendly format
void Card::ShowCardShortDetails() const
{
    string value;                    // ValueChar
    if(m_isFaceUp)
    {       
        if (m_valueChar == 'X')
        {
            value = "10";
        }
        else
        {
            value.push_back(m_valueChar);            
        }
        cout << value;        
        OutputSuitChar(m_suitChar);   
    }
    else
    {
        cout << "??";
    }  
}

//// operator string ()
Card::operator string () const
{
	// declare a stringstream object
	stringstream strOut; 
	// if the card is face-up
	if(m_isFaceUp)
	{
		// build a descriptive string from the obj state
		strOut << GetValueChar() << " of " << GetSuitChar();
	}
	else // card is face-down
	{
		// string indicates face-down
		strOut << "Face-Down";
	}
	// return the string
	return strOut.str();
}

/********************* 
 Custom Function Definitions
 *********************/ 
// The values in this function depend on the type of Deck used, 
// must be changed if different style of deck is required.
// Function can be omitted from ShowCardShortDetails(), and replaced
// with-> cout << " of " << m_suit;
void Card::OutputSuitChar(char suit) const
{
    _setmode(_fileno(stdout), _O_WTEXT);      	// Sets output mode to wide text
    const wchar_t CLUBS[] = L"\u2663";			// Constant for clubs suit symbol using unicode
    const wchar_t SPADES[] = L"\u2660";			// Constant for spades suit symbol using unicode
    const wchar_t HEARTS[] = L"\u2665";			// Constant for hearts suit symbol using unicode
    const wchar_t DIAMONDS[] = L"\u2666";		// Constant for diamonds suit symbol using unicode
    
    if(suit == 'H')
    {
        wprintf(HEARTS);        
    }
    if(suit == 'D')
    {
        wprintf(DIAMONDS);
    }
    if(suit == 'C')
    {
        wprintf(CLUBS);
    }
    if(suit == 'S')
    {
        wprintf(SPADES);
    } 
    
    _setmode(_fileno(stdout), _O_TEXT);          // Returns output mode to std
}

#endif

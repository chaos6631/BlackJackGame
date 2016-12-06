/*
* Project Name: Lab ?:
* Author: Chris Calder #100601097,
* Date: 
*
* Description:  A Playing Card Class file
*				
*/
#ifndef _PLAYINGCARD
#define _PLAYINGCARD

#include <cstdlib>					// for system()
#include <stdexcept>
#include <iomanip> 					// for output formatting
#include <iostream>
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

// Card Class Declaration : Validation should come from the Deck class to ensure that Card can be used in any game
class Card 
{
	public:
	    // Stacic Data Members
//	    static const int MIN_VALUE_AND_SUIT = 0;        // Not used
//		static const int MAX_SUIT = 3;                  // Not used
//		static const int MAX_VALUE = 11;                // Not used
		// Default Constructor
		Card(): m_value(1), m_valueChar('A'), m_suit("Hearts"), m_suitChar('H'), m_isFaceUp(true) {}
		// Paramaterized Constructor
		Card(int value, char valueChar , string suit, char suitChar, bool faceUp = true);
		// Copy Constructor
        Card(const Card &source); // NEW! copy constructor	
		// Mutators
		   //TODO NEED SETS FOR EACH MEMBER VARIABLE
        // Accesors
		int GetValue() const { return m_value; };
		char GetValueChar() const { return m_valueChar; };
		string GetSuit() const { return m_suit; };
		char GetSuitChar() const { return m_suitChar;	};
		void ShowCardDetails() const;
		void ShowCardShortDetails() const;
		void OutputSuitChar(char suit) const;
		// Operators
		Card& operator=(const Card &source); // assignment operator	
		operator string () const; // convert the obj to a string.
		
		// Public member variables
		bool m_isFaceUp; // true if face-up, false if face-down
	private:
	    // Member Variables
		int m_value;
		char m_valueChar;
		string m_suit;
		char m_suitChar;                                        // uses Unicode to display actual suit symbol
		
};

/********************* 
 Card class Definitions
 **********************/ 
// Parameterized Constructor
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

// Copy Constructor
Card::Card(const Card &source)
{
    m_value = source.m_value;
    m_valueChar = source.m_valueChar;
    m_suit = source.m_suit;
    m_suitChar = source.m_suitChar;
    m_isFaceUp = source.m_isFaceUp;
}

// Operator=
Card& Card::operator=(const Card &source)
{
    m_value = source.m_value;
    m_valueChar = source.m_valueChar;
    m_suit = source.m_suit;
    m_suitChar = source.m_suitChar;
    m_isFaceUp = source.m_isFaceUp;
    
    return *this;
}

// ShowCardDetails() : Used for testing purposes, shows all details
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

// ShowCardShortDetails() : Used for game shows minimal details in game friendly format
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

// operator string ()
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
// The values in this function depend on the type of Deck used, must be changed if different style of deck is required
void Card::OutputSuitChar(char suit) const
{
    _setmode(_fileno(stdout), _O_WTEXT);      // Sets output mode to wide text
    const wchar_t CLUBS[] = L"\u2663";
    const wchar_t SPADES[] = L"\u2660";
    const wchar_t HEARTS[] = L"\u2665";
    const wchar_t DIAMONDS[] = L"\u2666";
    
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

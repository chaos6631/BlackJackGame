/*
* Project Name: Lab ?:
* Author: Chris Calder #100601097,
* Date: 
*
* Description:  A C++ program that ....
*				
*/
#ifndef _DECKOFCARDS
#define _DECKOFCARDS

//#include <cstdlib>					// for system()
//#include <stdexcept>
//#include <iomanip> 					// for output formatting
//#include <iostream>
//#include <string>					// for string
//#include <sstream>					// for stringstream
#include "Card.h"
#include <algorithm>  
#include <vector>
// Required for Card Symbol Characters
#include <clocale>
#include <cstdio>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <wchar.h>

#pragma execution_character_set( "utf-8" )

using namespace std;

// Deck Class Declaration
class Deck {       
		
	public:	   
        // Stacic Data Members
	    static const int MAX_CARD_COUNT; 	      // Total number of cards in deck
        static const int MIN_VALUE_INDEX;         // Minimum index for VALUES and VALUE_CHAR vectors
		static const int MAX_VALUE_INDEX;         // Maximum index for VALUES and VALUE_CHAR vectors
	    static const int MIN_SUIT_INDEX;          // Minimum index for SUITS and SUIT_CHARS vectors
		static const int MAX_SUIT_INDEX;          // Maximum index for SUITS and SUIT_CHARS vectors
		
		static const vector<string> SUITS;
        static const vector<char> SUIT_CHARS;         
        static const vector<int> VALUES;
        static const vector<char> VALUE_CHAR; 
        
	    // CONSTRUCTORS
	    Deck();                                     // Default
	    Deck(const Deck &source);                   // Copy constructor
	    Deck& operator=(const Deck &source);        // Assignment operator
	    
	    // MUTATORS
		void FillDeck();        // calls method from Deck
		void Shuffle();         // calls method from Deck
		Card RemoveNextCard();      // Remove the top card from the deck

		// ACCESSORS
		void DisplayRemainingCards() const;
		//void OutputSuitChar(char suit) const;
		int CardsRemaining() const { return m_cards.size(); };                //Returns the number of cards left in the deck  
	private:
	    // MEMBERS
		vector<Card> m_cards;
};

/********************* 
Deck Class Definitions
 *********************/ 
//const string StandardPlayingCard::SUITS[] = { "Spades", "Hearts", "Diamonds", "Clubs" };
const int Deck::MAX_CARD_COUNT = 52;
const int Deck::MIN_VALUE_INDEX = 0;     // Minimum index for VALUES and VALUE_CHAR vectors
const int Deck::MAX_VALUE_INDEX = 12;    // Maximum index for VALUES and VALUE_CHAR vectors
const int Deck::MIN_SUIT_INDEX = 0;      // Minimum index for SUITS and SUIT_CHARS vectors
const int Deck::MAX_SUIT_INDEX = 3;      // Maximum index for SUITS and SUIT_CHARS vectors

// These values depend on the type of Deck used, must be changed if different style of deck is required
const vector<string> Deck::SUITS = { "Hearts", "Diamonds", "Spades", "Clubs"};
const vector<char> Deck::SUIT_CHARS = {'H', 'D', 'S', 'C'}; 
const vector<int> Deck::VALUES =      {2,3,4,5,6,7,8,9,10,10,10,10,1}; // VALUES order corresponds with VALUE_CHAR order
const vector<char> Deck::VALUE_CHAR = {'2','3','4','5','6','7','8','9','X','J','Q','K','A'}; // X represents 10

// Default constructor
Deck::Deck()
{    
    try
    {
        this->FillDeck();
    }
    catch(const range_error& err)
    {
        cerr << err.what() << endl << endl; 
    }
}
// Copy constructor
Deck::Deck(const Deck &source)
{
	m_cards = source.m_cards;
}
// Assignment operator=
Deck& Deck::operator=(const Deck &source)
{
	m_cards = source.m_cards;	
	return *this;
} 
// FillDeck()
void Deck::FillDeck() // **PARAM int DeckCount to be added
{	    
	int value = 0;				// Temp to hold card point value
	char valueChar;  		// Temp to hold card value character
	string suit = "";			// Temp to hold card suit as a string
	char suitChar;  		// Temp to hold card suit as a glyph
	
//	for(int i = 1; i <= deckCount; i++)
//	{
//	    
//    }
	//Check if there are any cards left in the deck, if so remove them
	if(m_cards.size() > 0)
	{
	    m_cards.clear();
    }
    //Set suit attributes
	for(int suitIndex = MIN_SUIT_INDEX; suitIndex <= MAX_SUIT_INDEX; suitIndex++) 
    {
		suit = SUITS[suitIndex];
		suitChar = SUIT_CHARS[suitIndex];
		// Set value attributes
		for(int valueIndex = MIN_VALUE_INDEX; valueIndex <= MAX_VALUE_INDEX; valueIndex++) 
        {
			value = VALUES[valueIndex];
			valueChar = VALUE_CHAR[valueIndex];
			Card newCard(value, valueChar, suit, suitChar);	// Create newcard
	        m_cards.push_back(newCard);						// Add card to deck	        
		}
	}	
    
//    if(m_cards.size() > MAX_CARD_COUNT)
//    {
//        m_cards.clear();                    // Clear the vector of all elements
//        
//		stringstream strOut;                // declare and build an error stringstream object		
//		strOut << "Range argument: " 
//			   << "Unable to create a deck larger than " 
//               << MAX_CARD_COUNT << "cards!!";	  
//        
//        throw range_error(strOut.str());    // throw a range_error exception initialized with the error string        
//    }
}
// DisplayRemainingCards()
void Deck::DisplayRemainingCards() const
{
	vector<Card> tempCards = m_cards;     // Copy deck to a temporary deck
    Card card;                            // Create temp card used to display card values
    
    while(!tempCards.empty())                            // While there are still cards output the current card value
    {
        card = tempCards.back();
        cout << "Card " << tempCards.size() << ": ";
        card.ShowCardShortDetails();
        cout << endl;        
        tempCards.pop_back();
    }    
}
// Shuffle()
void Deck::Shuffle() 
{
	random_shuffle(m_cards.begin(), m_cards.end());	
}
// RemoveNextCard
Card Deck::RemoveNextCard() 
{
	Card cardOut;                   // Temp card
	cardOut = m_cards.back();        // Get value of top card on deck and assign its values to temporary card
    m_cards.pop_back();             // Remove the card from the object from deck
	return cardOut;
}

/********************* 
 Custom Function Definitions
 *********************/ 
// ADD HERE

#endif

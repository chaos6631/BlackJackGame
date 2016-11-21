/*
* Project Name: Lab ?:
* Author: Chris Calder #100601097
* Date:
*
* Description:  Classes for a card deck and cards
*
*/


#include <cstdlib>					// for system()
#include <stdexcept>
#include <algorithm>   
#include <iomanip> 					// for output formatting
#include <iostream>
#include <string>					// for string
#include <sstream>					// for stringstream
#include <stack>
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

//static const vector<string> SUITS = { "Hearts", "Diamonds", "Spades", "Clubs"};
//static const vector<char> SUIT_CHARS = {'H', 'D', 'S', 'C'}; 
////Clubs L"\u2663" //Hearts L"\u2665" //Spades L"\u2660" //Diamonds L"\u2666"
//static const vector<int> VALUES = {11,2,3,4,5,6,7,8,9,10,10,10,10};
//static const vector<char> VALUE_CHAR = {'A',2,3,4,5,6,7,8,9,10,'J','Q','K'};
//
//// Card Class Declaration : Validation should come from the Deck class to ensure that Card can be used in any game
//class Card 
//{
//	public:
//	    // Stacic Data Members
//	    static const int MIN_VALUE_AND_SUIT = 0;
//		static const int MAX_SUIT = 3;
//		static const int MAX_VALUE = 12;
//		// Default Constructor
//		Card(): m_value(1), m_valueChar('A'), m_suit("Hearts"), m_suitChar('H') {}
//		// Paramaterized Constructor
//		Card(int value, char valueChar , string suit, char suitChar);
//		// Copy Constructor
//        Card(const Card &source); // NEW! copy constructor	
//		// Mutators
//        // Accesors
//		int GetValue() { return m_value; };
//		char GetValueChar() { return m_valueChar; };
//		string GetSuit()  { return m_suit; };
//		char GetSuitChar() { return m_suitChar;	};
//		void ShowCardDetails() const;
//		// Operators
//		Card& operator=(const Card &source); // assignment operator	
//	private:
//	    // Member Variables
//		int m_value;
//		char m_valueChar;
//		string m_suit;
//		char m_suitChar;                                        // uses Unicode to display actual suit symbol
//};
//
//// Deck Class Declaration
//class Deck {
////        // Stacic Data Members
//	    static const int CARD_COUNT = 52; 	      // Total number of cards in deck
//        static const int MIN_VALUE_INDEX = 0;     // Minimum index for VALUES and VALUE_CHAR vectors
//		static const int MAX_VALUE_INDEX = 12;    // Maximum index for VALUES and VALUE_CHAR vectors
//	    static const int MIN_SUIT_INDEX = 0;      // Minimum index for SUITS and SUIT_CHARS vectors
//		static const int MAX_SUIT_INDEX = 3;      // Maximum index for SUITS and SUIT_CHARS vectors
//		
//	public:	    
//	    // CONSTRUCTOR
//	    // MUTATORS
//		void FillDeck(int cardCount);    // calls method from Deck
////		void shuffle();     // calls method from Deck
////		Card removeCard(); //
//		// ACCESSORS
//		void DisplayRemainingCards() const;
//	private:
//	    // MEMBERS
//		stack<Card> m_cards;
//};
//
///** THIS FUNCTION WILL BE NEEDED IN THE ROUND CLASS/FUNCTION TO DISPLAY SYMBOLS ***/
//void OutputSuitChar(char suit); // Function needed to output suit symbol without disrupting stdOut for rest of program
//
//int main() 
//{
//    // Needed for random_shuffle to work should only be implemented once so in blackjack. Cpp main
//    srand(std::time(0));
//    SetConsoleOutputCP(65001);    
//    try
//    {
//        Card newCard;
//        Card oldCard;
//        stack<Card> newDeck;
//        newDeck.push(newCard);
////        newCard.ShowCardDetails();	
////	    OutputSuitChar(newCard.GetSuitChar());        
////        cout << endl << newCard.GetSuitChar();          
//        oldCard = newDeck.top();	    
//        oldCard.ShowCardDetails();	
//	    OutputSuitChar(oldCard.GetSuitChar());        
//        cout << endl << oldCard.GetSuitChar();
//    }
//    catch(const exception& ex)
//    {
//        cerr << endl << ex.what() << endl;
//    }    
//    catch(...)
//    {
//        cerr << endl << "FATAL ERROR" << endl;
//    }
//        
//	cin.get();
//	return 0;    
//}
//
//// Custom Function Definitions
//void OutputSuitChar(char suit)
//{
//    _setmode(_fileno(stdout), _O_WTEXT);      // Sets output mode to wide text
//    const wchar_t CLUBS[] = L"\u2663";
//    const wchar_t SPADES[] = L"\u2660";
//    const wchar_t HEARTS[] = L"\u2665";
//    const wchar_t DIAMONDS[] = L"\u2666";
//    
//    if(suit == 'H')
//    {
//        wprintf(HEARTS);        
//    }
//    if(suit == 'D')
//    {
//        wprintf(DIAMONDS);
//    }
//    if(suit == 'C')
//    {
//        wprintf(CLUBS);
//    }
//    if(suit == 'S')
//    {
//        wprintf(SPADES);
//    } 
//    
//    _setmode(_fileno(stdout), _O_TEXT);          // Returns output mode to std
//}
///********************* 
// Card class Definitions
// **********************/ 
//// Parameterized Constructor
//Card::Card(int value, char valueChar , string suit, char suitChar)
//{
//    if(value == 0)
//    {
//        string errorMsg = "Value of card can't be 0";
//        throw out_of_range(errorMsg);
//    }
//    else
//    {
//        m_value = value;
//        m_valueChar = valueChar;
//        m_suit = suit;
//        m_suitChar = suitChar;
//    }
//}
//
//// Copy Constructor
//Card::Card(const Card &source)
//{
//    m_value = source.m_value;
//    m_valueChar = source.m_valueChar;
//    m_suit = source.m_suit;
//    m_suitChar = source.m_suitChar;
//}
//
//// Operator=
//Card& Card::operator=(const Card &source)
//{
//    m_value = source.m_value;
//    m_valueChar = source.m_valueChar;
//    m_suit = source.m_suit;
//    m_suitChar = source.m_suitChar;
//    
//    return *this;
//}
//
//void Card::ShowCardDetails() const 
//{    
//	cout << "           Card Details" << endl
//	     << "================================" << endl
//	     << "  Card Suit: " << m_suit << "(" << m_suitChar << ")" << endl
//         << "Card Values: " << m_value << " represented by '" << m_valueChar << "'\n";
//}
//
///********************* 
//Deck Class Definitions
// *********************/ 
//
//void Deck::FillDeck(int cardCount) 
//{	
//	int value = 0;				// Temp to hold card point value
//	char valueChar;  		// Temp to hold card value character
//	string suit = "";			// Temp to hold card suit as a string
//	char suitChar;  		// Temp to hold card suit as a glyph
//	for(int i = 0; i < cardCount; i++ ) 
//    {
//		//Set suit attributes
//		for(int j = 0; j < 4; j++) {
//			suit = SUITS[j];
//			suitChar = SUIT_CHARS[j];
//			// Set value attributes
//			for(int k = 0; k < 13; k++) {
//				value = VALUES[k];
//				valueChar = VALUE_CHAR[k];
//			}
//		}
//		Card newCard(value, valueChar, suit, suitChar);	// Create newcard
//		m_cards.push(newCard);						// Add card to deck
//	}
//}

//void Deck::DisplayRemainingCards() 
//{
//	for(int i =0; i < m_cards.count(); i++) 
//	{
//		wcout  << L(m_cards[i].GetSuitChar()) 
//					 << m_cards[i].GetValueChar() << endl;
//	}
//}
//
//void Deck::Shuffle() 
//{
//	random_shuffle(m_card.begin(), m_card.end());	
//}
//
//Card Deck::RemoveCard() 
//{
//	Card cardOut;
//	cardOut = m_cards.top();
//	return cardOut;
//}

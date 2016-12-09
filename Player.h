/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097, Christopher Alexander #100360337
* Date: November 8, 2016
*
* Description:  A Player class that reperesents an instance of a player in a Blackjack game.
*				
*/

#ifndef _PLAYER
#define _PLAYER

#include "Card.h"
//#include <cstdlib>					// for system()
//#include <stdexcept>
//#include <iomanip> 					// for output formatting
//#include <iostream>
//#include <string>					    // for string
//#include <sstream>					// for stringstream
#include <vector>

using namespace std;

class Player
{
    public:
        // STATIC DATA MEMBERS
        static const double DEFAULT_MONEY_AMOUNT;
        // DEFAULT CONSTRUCTOR
        Player(): m_playerName("Player1"), m_money(DEFAULT_MONEY_AMOUNT), m_currentBet(0) {}
        // PARAMETERIZED CONSTRUCTOR
        Player(string name, double money = DEFAULT_MONEY_AMOUNT);
        // ACCESSORS
        void ShowCards() const;                                  // Display all cards in the regular hand     
        void ShowSplitCards() const;                             // Display all cards in the split hand         
        string GetPlayerName() const { return m_playerName; };
        double GetPlayerMoneyTotal() const { return m_money; };  //OVERRIDE IN DEALER CLASS
        double GetCurrentBet() const { return m_currentBet; };
        double GetCurrentSplitBet() const { return m_splitBet; };
        int GetTotalValue() const ;                              // Get the total value of all the cards in the hand   
        int GetSplitTotalValue() const;                             // Get the total value of all the cards in the split hand  
        bool CanSplit();                                         // True if players first two cards are same face char, false if not
        // MUTATORS
        void AddCard(Card newCard)    ;            // Add a card to the hand
        void Bet(double amount);                   // OVERRIDE IN DEALER CLASS
    	void Stand();                              // Does Nothing at the moment
    	void Hit(Card newCard, bool isSplitHand);  // Gets a new card and places it in either m_hand or m_splitHand depending on isSplitHand
    	void DoubleDown(double amount);            // Doubles the current bet
    	void ClearHand();                          // Removes all cards from hand
    	void CollectMoney(double amount);          // Add winnings to m_money 	
    	void SplitHand();                          // Splits m_hand placing the second card into m_splithand        
    protected:
        string m_playerName;       // Player's name
        vector<Card> m_hand;       // Vector containing card objects that make up the hand  
    private:      
    	double m_money;            // Total funds available
        double m_currentBet;	   // Current bet amount for the round
    	vector<Card> m_splitHand;  // Vector containing card objects that make up a split hand    	
        double m_splitBet;         // The amount of original bet, used for clarity, could have 
                                   //  just referenced m_currentBet as a split uses same amount 
                                   //  as original bet. 
};


/********************* 
 Player Class Definitions
 *********************/ 
 
const double Player::DEFAULT_MONEY_AMOUNT = 100;

// Parameterized Constructor
Player::Player(string name, double money)
{
    m_playerName = name;    
    m_money = money;
    m_currentBet = 0;
}

void Player::ShowCards() const
{
    Card card;                            // Create temp card used to display card values    

    for(int i = 0; i < m_hand.size(); i++)
    {
        card = m_hand.at(i);
        cout << " | ";
        card.ShowCardShortDetails();
        if(i == (m_hand.size() - 1))
        {
            cout << " | ";    
        }        
    }  
}

void Player::ShowSplitCards() const
{
    Card card;                            // Create temp card used to display card values    

    for(int i = 0; i < m_splitHand.size(); i++)
    {
        card = m_splitHand.at(i);
        cout << " | ";
        card.ShowCardShortDetails();
        if(i == (m_splitHand.size() - 1))
        {
            cout << " | ";    
        }        
    }  
}

int Player::GetTotalValue() const
{
    int total = 0;
    int aceCount = 0;    
    //cout << "checking total\n";
    for(int i = 0;i < m_hand.size();i++)
    {     
        if(m_hand[i].GetValue() == 1)
        {
            aceCount += 1;
        }          
		else
		{
			total += m_hand[i].GetValue();
		}
    }    
    if(aceCount == 1)
        {
            if(total <= 10)
            {
                total += 11;
            }
            else
            {
                total += 1;    
            }
        }
        if(aceCount == 2)
        {
            if(total <= 10 && (total + 12) <= 21)
            {
                total += 12;
            }
            else
            {
                total += 2;    
            }
        }
        if(aceCount == 3)
        {
            if(total <= 10 && (total + 13) <= 21)
            {
                total += 13;
            }
            else
            {
                total += 3;    
            }
        }
        if(aceCount == 4)
        {
            if(total <= 10 && (total + 14) <= 21)
            {
                total += 14;
            }
            else
            {
                total += 4;    
            }
        } 
    return total;
}

int Player::GetSplitTotalValue() const
{
    int total = 0;
    int aceCount = 0;    
    //cout << "checking total\n";
    for(int i = 0;i < m_splitHand.size();i++)
    {     
        if(m_splitHand[i].GetValue() == 1)
        {
            aceCount += 1;
        }          
		else
		{
			total += m_splitHand[i].GetValue();
		}
    }    
    if(aceCount == 1)
        {
            if(total <= 10)
            {
                total += 11;
            }
            else
            {
                total += 1;    
            }
        }
        if(aceCount == 2)
        {
            if(total <= 10 && (total + 12) <= 21)
            {
                total += 12;
            }
            else
            {
                total += 2;    
            }
        }
        if(aceCount == 3)
        {
            if(total <= 10 && (total + 13) <= 21)
            {
                total += 13;
            }
            else
            {
                total += 3;    
            }
        }
        if(aceCount == 4)
        {
            if(total <= 10 && (total + 14) <= 21)
            {
                total += 14;
            }
            else
            {
                total += 4;    
            }
        } 
    return total;
}

void Player::SplitHand()
{
    if(CanSplit())
    {
        Card splitCard = m_hand.back();
        m_hand.pop_back();
        m_splitHand.push_back(splitCard);
        m_splitBet = m_currentBet;
        Bet(m_splitBet);
    }
    else
    {
        throw invalid_argument("Error::Cards must be equal value characters to split!!\n");
    }
}

bool Player::CanSplit()
{
    bool canSplit = false;
    if(m_hand.size() > 0)
    {
        if(m_hand[0].GetValueChar() == m_hand[1].GetValueChar())
        {
            canSplit = true;
        }
    }
    return canSplit;
}

void Player::AddCard(Card newCard)
{
    m_hand.push_back(newCard);
}

void Player::Bet(double amount)
{
    double maxBetAmount = m_money;
    if(amount <= maxBetAmount && amount >= 0)
    {
        m_money -= amount;
        m_currentBet = amount;
        cout << "You have bet $" << amount << endl;
    }
    else
    {
        throw invalid_argument("The amount bet can't be more than the player has available or less than zero!!");
    }
}

void Player::Stand()
{
    
}

void Player::Hit(Card newCard, bool isSplitHand)
{   
    if(isSplitHand)   // If isSplitHand is true put the new card in m_splitHand
    {
        m_splitHand.push_back(newCard);
    }
    else              // If isSplitHand is false put the new card in m_hand
    {
        m_hand.push_back(newCard);    
    }
}

void Player::DoubleDown(double amount)
{    
    double maxBetAmount = m_money;
        
    if(m_currentBet <= maxBetAmount && m_currentBet >= 0)
    if(amount <= maxBetAmount && amount >= 0)
    {
        m_money -= m_currentBet;
        m_currentBet += m_currentBet;        
    }
    else
    {
        throw invalid_argument("The amount bet can't be more than the player has available or less than zero!!");
    }
}

void Player::ClearHand()
{
    m_hand.clear();
}

void Player::CollectMoney(double amount)
{
    m_money += amount;
}




#endif

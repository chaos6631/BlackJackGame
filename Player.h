/*
* Project Name: Final Project: Blackjack
* Author: Chris Calder #100601097,
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
        void ShowCards();                                                 // Display all cards as player
        string GetPlayerName() const { return m_playerName; };
        double GetPlayerMoneyTotal() const { return m_money; };           //OVERRIDE IN DEALER CLASS
        double GetCurrentBet() const { return m_currentBet; };
        int GetTotalValue() const ;                                       // Get the total value of all the cards in the hand  
        bool CanSplit();                                                  // True if players first two cards are same face char, false if not
        //int GetNumOfCards() const;                                      // Get the total number of cards in the hand
        
        // MUTATORS
        void AddCard(Card newCard)    ;                                   // Add a card to the hand
        void Bet(double amount);                                          //OVERRIDE IN DEALER CLASS
    	void Stand();
    	void Hit(Card newCard);
    	void DoubleDown(double amount);
    	void ClearHand();
    	void CollectMoney(double amount);
    	//void SplitHand()                                                // NOT REQUIRED BUT IS OPTION //OVERRIDE IN DEALER CLASS
    protected:
        string m_playerName;
        vector<Card> m_hand;                           // Vector containing card objects that make up the hand
    private:      
    	double m_money;                                // Total funds available
        double m_currentBet;	                       // Current bet amount for the round
//    	vector<Card> m_split hand;                     // NOT REQUIRED BUT IS OPTION    	
//      double m_splitBet;                             // the amount of original bet 	
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

void Player::ShowCards()
{
    Card card;                            // Create temp card used to display card values    

    for(int i = 0; i < m_hand.size(); i++)
    {
        card = m_hand.at(i);
        cout << " | ";
        card.ShowCardShortDetails();
        if(i == (m_hand.size() -1))
        {
            cout << " | ";    
        }        
    }  
}

int Player::GetTotalValue() const
{
    int total = 0;
    int aceCount = 0;
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
    }
//    for(int i = 0;i < m_hand.size();i++)
//    {       
//        if(total > 10 && m_hand[i].GetValue() == 11)
//		{
//			total += 1;
//		}
//		else
//		{
//			total += m_hand[i].GetValue();
//		}
//    }
    return total;
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
    cout << "You have chosen to Stand!" << endl;
}

void Player::Hit(Card newCard)
{
    //cout << "You have chosen to Hit!" << endl;
    m_hand.push_back(newCard);
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

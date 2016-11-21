#include <vector>
#include <string>



Public class Player
{
	Hand m_hand
	Hand m_split hand
	double m_money
	bool m_hasSplit
	void Bet(double amount) 
	void SplitHand() 
	void Hit(Card newCard) 
} 
Public class Dealer
{
	Hand m_hand
	Deck  m_gameDeck
	void Hit(Card newCard)
	void filldeck()    // calls method from Deck
	void shuffle()     // calls method from Deck
	void givecard() // calls method from Deck
} 
Public class Hand
{

    public:
    	// Constructor
        Hand(Card card1, Card card2) ;
        
        void display()        ;
        void displayAsDealer();
        void addCard(Card)    ;
    
        int getNumOfCards();
        int getTotalValue()  ;
    	
    private:
        std::vector<Card> m_cards;
} 
Int Hand::GetTotalValue() 
{
	int total =0;
	for(int i = 0; i < m_cards.count; i ++) 
	{
		if(total > 10 && m_card[i ].GetValue() == 11)
		{
			total += 1;
		}
		else
		{
			total += m_cards[i ].GetValue();
		}
	}
	return total;
}




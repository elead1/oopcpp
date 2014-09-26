/*
 * Hand.h
 * Author: Eric Leadbetter
 * Purpose: Holds cards making up a poker hand, determines ranking of hand.
 */
// Include for testing.
#include <iostream>

#include "Hand.h"

const int Hand::MAXCARDS;

Hand::Hand( const std::array<Card, Hand::MAXCARDS> &cards )
{
	for(unsigned int i = 0; i < cards.size(); i++)
	{
		if(!cards.at(i).isValid())
		{
			throw std::invalid_argument("cards does not have 5 valid Cards");
		}
		this->myCards.at(i) = Card(cards.at(i));
		this->currentCards++;
	}
	this->probability = this->calcProbability();
}

void Hand::addCard( const Card &c )
{
	if(this->isFull())
	{
		throw std::runtime_error("Hand already full.");
	}
	//Sort descending so all invalid/unset cards are at end.
	std::sort(std::begin(myCards), std::end(myCards),
			Card::reverseSortByRank);

	//currentCards is equal to the index of the last set card + 1,
	//so it is the index of the first unset card.
	this->myCards.at(this->currentCards) = Card(c);
}

bool Hand::isFull( void ) const
{
	if(this->currentCards == Hand::MAXCARDS)
	{
		return true;
	}
	return false;
}

void Hand::clear( void )
{
	for(int i = 0; i < this->currentCards; i++)
	{
		this->myCards.at(i) = Card();
		this->currentCards--;
	}
}

double Hand::rank( void ) const
{
	return this->calcProbability();
}

std::string Hand::toString( void )
{
	std::string handStr = "";
	std::sort(std::begin(this->myCards), std::end(this->myCards),
			Card::sortByRank);
	for(Card c : this->myCards)
	{
		handStr += c.toString();
		handStr += ",";
	}
	return handStr;
}

double Hand::calcProbability( void ) const
{
	return 0.0;
}

int main()
{
	std::array<Card, 5> cardArr;
	//Test printing empty hand.
	Hand h;
	std::cout << h.toString() << std::endl;

	std::array<Card, 5> cardArr2 = {Card(Rank::ACE, Suit::CLUBS),
			Card(Rank::EIGHT, Suit::DIAMONDS),
			Card(Rank::JACK, Suit::HEARTS),
			Card(Rank::TWO, Suit::CLUBS),
			Card(Rank::QUEEN, Suit::SPADES)
	};
	//Test making hand from card array.
	Hand h2(cardArr2);
	std::cout << h2.toString() << std::endl;

	//Test isFull
	std::cout << "h2 isFull: " << h2.isFull() << std::endl;
	std::cout << "h1 isFull: " << h.isFull() << std::endl;

	//Test clear
	h2.clear();
	std::cout << "h2 isFull after clear: " << h2.isFull() << std::endl;

	//Test addCard & getHighCard (and getNthHighCard)
	h.addCard(Card(Rank::KING, Suit::HEARTS));
	std::cout << "h after addCard: " << h.toString() << std::endl;
	std::cout << "h highest card after addCard: "
			<< h.getHighCard().toString() << std::endl;
}

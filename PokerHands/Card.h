/*
 * Card.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulates the characteristics of a standard playing card.
 */
#ifndef Card_H
#define Card_H

#include "Rank.h"
#include "Suit.h"

/**
 * \class Card
 * Encapsulates the characteristics of a standard playing card.
 */
class Card
{
	public:
		/**
		 * \fn Card( Rank, Suit )
		 * Creates new Card object and initializes card's
		 * rank and suit to the parameters.
		 * @param r the Rank of this Card
		 * @param s the Suit of this card
		 */
		Card( Rank r, Suit s)
			: myRank(r), mySuit(s) {}

		/**
		 * \fn toString( void ) const
		 * Returns a string representing the Card.
		 * @return A string representing the Card. Ex: a 5 of diamonds
		 * would return as "5D".
		 */
		std::string toString( void ) const;

		/**
		 * \fn getRank( void ) const
		 * @return The Rank of this Card.
		 */
		Rank getRank( void ) const
		{
			return myRank;
		}

		/**
		 * \fn getSuit( void ) const
		 * @return The Suit of this Card.
		 */
		Suit getSuit( void ) const
		{
			return mySuit;
		}

	private:
		Rank myRank;
		Suit mySuit;
};


#endif

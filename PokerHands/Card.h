/*
 * Card.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulates the characteristics of a standard playing card.
 */
#ifndef Card_H
#define Card_H

#include <string>
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
		 * \fn Card( void )
		 * Dummy constructor.
		 */
		Card( void )
			: myRank(Rank::INVALIDRANK), mySuit(Suit::INVALIDSUIT){}
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
		 * \fn Card( const Card &toCopy )
		 * Copy constructor.
		 */
		Card( const Card &toCopy )
		{
			this->myRank = toCopy.getRank();
			this->mySuit = toCopy.getSuit();
		}
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

		/**
		 * \fn bool isValid( void ) const
		 * @return true if the Card is valid (rank and suit >= 0), else false
		 */
		bool isValid( void ) const
		{
			if((this->myRank == Rank::INVALIDRANK)
					|| (this->mySuit == Suit::INVALIDSUIT))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		/**
		 * \fn sortByRank( Card, Card )
		 * A sort function to sort Cards based on Rank.
		 * @param lhs The 'left' Card to compare
		 * @param rhs The 'right' Card to compare
		 * @return true if lhs.rank is less than rhs.rank, false otherwise
		 */
		static bool sortByRank(const Card &lhs, const Card &rhs)
		{
			return lhs.myRank < rhs.myRank;
		}
		/**
		 * \fn reverseSortByRank( Card, Card )
		 * Allows for sorting of Cards in descending order.
		 * @param lhs The 'left' Card to compare
		 * @param rhs The 'right' Card to compare
		 * @return true if lhs.rank is greater than rhs.rank, false otherwise
		 */
		static bool reverseSortByRank(const Card &lhs, const Card &rhs)
		{
			return lhs.myRank > rhs.myRank;
		}

	private:
		Rank myRank;
		Suit mySuit;
}; // end class Card


#endif

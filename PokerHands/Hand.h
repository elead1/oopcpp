/*
 * Hand.h
 * Author: Eric Leadbetter
 * Purpose: Holds cards making up a poker hand, determines ranking of hand.
 */
#ifndef Hand_H
#define Hand_H
#include <iostream>
#include <array>
#include <algorithm>
#include <stdexcept>
#include "Card.h"

/**
 * \class Hand
 * Holds the cards making up a poker hand. Has the capability to
 * generate the probability of being dealt the hand, useful for ranking
 * hands.
 */

class Hand
{

	public:
		static const int MAXCARDS = 5;
		/**
		 * \fn Hand( void )
		 * Default Hand constructor. Initializes with empty Card array. Useful
		 * for dynamically generating a hand.
		 */
		Hand( void )
			: probability(0.0) {}
		/**
		 * \fn Hand( const std::array<Card, Hand::MAXCARDS> &cards )
		 * Instantiates a new Hand containing the given Card objects.
		 * Calculates the probability of the Hand right away. It is an
		 * exception when cards does not have 5 elements.
		 * @param cards The array of Cards to make up this Hand.
		 */
		Hand( const std::array<Card, Hand::MAXCARDS> &cards );
		/**
		 * \fn void addCard( Card c )
		 * Adds the given card to the Hand. If the Hand is filled by this
		 * card, the probability of the Hand is calculated. Throws an
		 * exception if the Hand is full.
		 * @param c The Card to add to the Hand.
		 */
		void addCard( const Card &c);
		/**
		 * \fn bool isFull( void ) const
		 * @return true if the Hand has 5 cards in it, false otherwise.
		 */
		bool isFull( void ) const;
		/**
		 * \fn void clear( void )
		 * Empties the Hand of Cards.
		 */
		void clear( void );
		/**
		 * \fn double rank( void )
		 * Throws an exception if the Hand is not full.
		 * @return The calculated probability of achieving this Hand.
		 */
		double rank( void ) const;
		/**
		 * \fn Card getNthHighCard( int height )
		 * It is an exception if height < 1 or height > 5.
		 * @return The height-th highest ranked card in the hand.
		 */
		Card getNthHighCard( int height )
		{
			std::sort(std::begin(this->myCards), std::end(this->myCards),
					Card::descendingSortByRank);
			return this->myCards.at(height - 1);
		}
		/**
		 * \fn Card getHighCard( void )
		 * @return The highest ranked card in the hand, for breaking ties.
		 */
		Card getHighCard( void )
		{
			return this->getNthHighCard(1);
		}
		/**
		 * \fn string toString( void )
		 * @return Returns a comma separated, ascendingly sorted string
		 * representing the Hand. For example, "2D,3S,3D,5H,QC" represents
		 * a Hand containing: 2 of diamonds, 3 of spades, 3 of diamonds,
		 * 5 of hearts, and queen of clubs.
		 */
		std::string toString( void );
		/**
		 * \fn int handPerCardCompare( Hand, Hand )
		 * Sorts each Hand descending, then does pairwise comparison of cards
		 * in each Hand. Throws exception if lhs or rhs is not a full
		 * 5-Card Hand.
		 * @param lhs The 'left' Hand to compare
		 * @param rhs The 'right' Hand to compare
		 * @return 1 if lhs has higher cumulative Rank than rhs,
		 * -1 if rhs is higher than lhs,
		 * 0 if the Hands are equal
		 */
		static int handPerCardCompare( Hand &lhs, Hand &rhs );

	private:
		enum HandTypes{STRAIGHTFLUSH, FOUROFAKIND, FULLHOUSE, FLUSH, STRAIGHT,
				THREEOFAKIND, TWOPAIR, PAIR, HIGHCARD, HANDTYPECOUNT};
		//Probability of each hand type.
		static constexpr std::array<double, HandTypes::HANDTYPECOUNT>
		handProbTable = {{ // had to move identifier here to avoid linewrap
				0.001539, 0.0240, 0.144, 0.197, 0.392, 2.11, 4.75, 42.3, 50.1
		}};
		static const int NUMRANKS = 13;
		static const int NUMSUITS = 4;
		int currentCards = 0; //Count of current number of cards in hand
		std::array<Card, MAXCARDS> myCards = {};
		double probability;
		double calcProbability( void );
};

#endif

/*
 * Card.cpp
 * Author: Eric Leadbetter
 * Purpose: Encapsulates the characteristics of a standard playing card.
 */

#include <sstream>
#include "Card.h"

std::string Card::toString( void ) const
{
	std::string cardRep = "";
	switch(this->myRank)
	{
		case Rank::ACE:
			cardRep += "A";
			break;
		case Rank::KING:
			cardRep += "K";
			break;
		case Rank::QUEEN:
			cardRep += "Q";
			break;
		case Rank::JACK:
			cardRep += "J";
			break;
		case Rank::TEN:
			cardRep += "T";
			break;
		case Rank::NINE:
		case Rank::EIGHT:
		case Rank::SEVEN:
		case Rank::SIX:
		case Rank::FIVE:
		case Rank::FOUR:
		case Rank::THREE:
		case Rank::TWO:
		{
			std::stringstream tmpSS;
			// Add 1 because TWO is element #2 (index 1)
			tmpSS << (this->myRank + 1);
			cardRep += tmpSS.str();
			break;
		}
		default:
			break;
	} // end switch

	switch(this->mySuit)
	{
		case Suit::CLUBS:
			cardRep += "C";
			break;
		case Suit::DIAMONDS:
			cardRep += "D";
			break;
		case Suit::HEARTS:
			cardRep += "H";
			break;
		case Suit::SPADES:
			cardRep += "S";
			break;
		default:
			break;
	} // end switch

	return cardRep;
} // end toString()

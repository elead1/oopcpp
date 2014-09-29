/*
 * Hand.h
 * Author: Eric Leadbetter
 * Purpose: Holds cards making up a poker hand, determines ranking of hand.
 */
// Include for testing.
#include <iostream>

#include "Hand.h"

const int Hand::MAXCARDS;
const int Hand::NUMRANKS;
const int Hand::NUMSUITS;
constexpr std::array<double, Hand::HandTypes::HANDTYPECOUNT> Hand::handProbTable;

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
} // end Hand(array)

void Hand::addCard( const Card &c )
{
	if(this->isFull())
	{
		throw std::runtime_error("Hand already full.");
	}
	//Sort descending so all invalid/unset cards are at end.
	std::sort(myCards.begin(), myCards.begin(),
			Card::descendingSortByRank);

	//currentCards is equal to the index of the last set card + 1,
	//so it is the index of the first unset card.
	this->myCards.at(this->currentCards) = Card(c);
	this->currentCards++;

	//If hand is now full, calculate probability.
	if(this->currentCards == Hand::MAXCARDS)
	{
		this->probability = this->calcProbability();
	}
} // end addCard(Card)

bool Hand::isFull( void ) const
{
	if(this->currentCards == Hand::MAXCARDS)
	{
		return true;
	}
	return false;
} //end isFull()

void Hand::clear( void )
{
	for(int i = 0; i < this->currentCards; i++)
	{
		this->myCards.at(i) = Card();
		this->currentCards--;
	}
} // end clear()

double Hand::rank( void ) const
{
	return this->probability;
} // end rank()

std::string Hand::toString( void )
{
	std::string handStr = "";
	std::sort(std::begin(this->myCards), std::end(this->myCards),
			Card::ascendingSortByRank);
	for(Card c : this->myCards)
	{
		handStr += c.toString();
		handStr += ",";
	}
	return handStr;
} // end toString()

double Hand::calcProbability( void )
{
	 //number of Cards in Hand of each Rank; indexes are ascending (e.g. TWO is index 0)
	std::array<int, Hand::NUMRANKS> rankCounts = {};
	//number of Cards in Hand of each Suit; indexes are 0 = CLUBS, 1 = DIAMONDS, 2 = HEARTS...
	std::array<int, Hand::NUMSUITS> suitCounts = {};
	//sort the array because sorted arrays are the best (also for determining straights)
	std::sort(this->myCards.begin(), this->myCards.end(),
				Card::descendingSortByRank);
	//Start with high card probability (highest)
	double probability = Hand::handProbTable[Hand::HandTypes::HIGHCARD];
	//Flags for hands that require multidimensional data
	bool threeOfKindFound = false;
	bool pairFound = false;
	bool straightFound = true;
	bool flushFound = false;
	Card lastCard(Rank::INVALIDRANK, Suit::INVALIDSUIT);

	//Generate stats for the five Cards
	for(Card c : this->myCards)
	{
		//Compare Card ranks for all Cards after first Card in Hand.
		//If this Card's rank isn't 1 less than previous Card's rank, no straight.
		if((lastCard.getRank() != Rank::INVALIDRANK) &&
				(c.getRank() + 1 != lastCard.getRank()))
		{
			straightFound = false;
		}

		switch(c.getRank())
		{
			case Rank::TWO:
				rankCounts[0]++;
				break;
			case Rank::THREE:
				rankCounts[1]++;
				break;
			case Rank::FOUR:
				rankCounts[2]++;
				break;
			case Rank::FIVE:
				rankCounts[3]++;
				break;
			case Rank::SIX:
				rankCounts[4]++;
				break;
			case Rank::SEVEN:
				rankCounts[5]++;
				break;
			case Rank::EIGHT:
				rankCounts[6]++;
				break;
			case Rank::NINE:
				rankCounts[7]++;
				break;
			case Rank::TEN:
				rankCounts[8]++;
				break;
			case Rank::JACK:
				rankCounts[9]++;
				break;
			case Rank::QUEEN:
				rankCounts[10]++;
				break;
			case Rank::KING:
				rankCounts[11]++;
				break;
			case Rank::ACE:
				rankCounts[12]++;
				break;
			default:
				break;
		} // end switch

		switch(c.getSuit())
		{
			case Suit::CLUBS:
				suitCounts[0]++;
				break;
			case Suit::DIAMONDS:
				suitCounts[1]++;
				break;
			case Suit::HEARTS:
				suitCounts[2]++;
				break;
			case Suit::SPADES:
				suitCounts[3]++;
				break;
			default:
				break;
		} // end switch
		lastCard = c;
	} // end for

	/* PURE RANK-BASED HAND RANKINGS*/

	//Determine any four of a kind, full house, three of a kind, two pair, pairs
	for(int count: rankCounts)
	{
		//Four of a kind
		if(count == 4)
		{
			double fourOfAKindProb = Hand::handProbTable[Hand::HandTypes::FOUROFAKIND];
			probability = (fourOfAKindProb < probability ? fourOfAKindProb : probability);
		}
		//Full house
		if(count == 3 &&
				pairFound)
		{
			double fullhouseProb = Hand::handProbTable[Hand::HandTypes::FULLHOUSE];
			probability = (fullhouseProb < probability ? fullhouseProb : probability);
		}
		//Three of a kind
		else if(count == 3 &&
				!pairFound)
		{
			threeOfKindFound = true;
		}
		//two pair
		if(count == 2 &&
				pairFound)
		{
			double twoPairProb = Hand::handProbTable[Hand::HandTypes::TWOPAIR];
			probability = (twoPairProb < probability ? twoPairProb : probability);
		}
		//one pair
		else if(count == 2 &&
				!pairFound)
		{
			pairFound = true;
		}
	} // end for

	//check for three of a kind
	if(threeOfKindFound)
	{
		double threeofKindProb = Hand::handProbTable[Hand::HandTypes::THREEOFAKIND];
		probability = (threeofKindProb < probability ? threeofKindProb : probability);
	}
	//check pair
	if(pairFound)
	{
		double pairProb = Hand::handProbTable[Hand::HandTypes::PAIR];
		probability = (pairProb < probability ? pairProb : probability);
	}

	/*PURE SUIT-BASED RANKINGS*/
	//Determine any flushes
	for(int count: suitCounts)
	{
		if(count == Hand::MAXCARDS)
		{
			double flushProb = Hand::handProbTable[Hand::HandTypes::FLUSH];
			probability = (flushProb < probability ? flushProb : probability);
			flushFound = true;
		}
	} // end for

	//Check for straight flush
	if(flushFound &&
			straightFound)
	{
		double straightFlushProb = Hand::handProbTable[Hand::HandTypes::STRAIGHTFLUSH];
		probability = (straightFlushProb < probability ? straightFlushProb : probability);
	}
	//Check for plain straight
	else if(straightFound &&
		!flushFound)
	{
		double straightProb = Hand::handProbTable[Hand::HandTypes::STRAIGHT];
		probability = (straightProb < probability ? straightProb : probability);
	}
	return probability;
} // end calcProbability()

int Hand::handPerCardCompare( Hand &lhs, Hand &rhs )
{
	if(!lhs.isFull()
			|| !rhs.isFull())
	{
		throw std::invalid_argument("lhs or rhs is not a full 5-Card Hand.");
	}
	std::sort(lhs.myCards.begin(), lhs.myCards.end(), Card::ascendingSortByRank);
	std::sort(rhs.myCards.begin(), rhs.myCards.end(), Card::ascendingSortByRank);
	for(int i = 0; i < Hand::MAXCARDS; i++)
	{
		if(lhs.myCards[i].getRank() < rhs.myCards[i].getRank())
		{
			return -1;
		}
		else if(lhs.myCards[i].getRank() > rhs.myCards[i].getRank())
		{
			return 1;
		}
	}
	return 0; // Hands are equal.
} //end handPerCardCompare()

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

	//Test hand comparison
	std::array<Card, 5> hand1Deck = {Card(Rank::ACE, Suit::CLUBS),
			Card(Rank::THREE, Suit::CLUBS),
			Card(Rank::NINE, Suit::CLUBS),
			Card(Rank::TEN, Suit::CLUBS),
			Card(Rank::SEVEN, Suit::CLUBS)};
	Hand hand1(hand1Deck);
	std::array<Card, 5> hand2Deck = {Card(Rank::ACE, Suit::SPADES),
			Card(Rank::TWO, Suit::SPADES),
			Card(Rank::SIX, Suit::SPADES),
			Card(Rank::FOUR, Suit::SPADES),
			Card(Rank::EIGHT, Suit::SPADES)};
	Hand hand2(hand2Deck);

	std::cout << "Probability of hand 1 (" << hand1.toString() << "): "
			<< hand1.rank() << std::endl;
	std::cout << "Probability of hand 2 (" << hand2.toString() << "): "
			<< hand2.rank() << std::endl;
	if(hand1.rank() < hand2.rank())
	{
		std::cout << "Winning hand is hand 1." << std::endl;
	}
	else if(hand1.rank() > hand2.rank())
	{
		std::cout << "Winning hand is hand 2." << std::endl;
	}
	//Ranks are equal, compare individual cards
	else
	{
		std::cout << "Ranks equal, comparing individual cards." << std::endl;
		switch(Hand::handPerCardCompare(hand1, hand2))
		{
			case -1:
				std::cout << "Hand 2 winner!" << std::endl;
				break;
			case 1:
				std::cout << "Hand 1 winner!" << std::endl;
				break;
			case 0:
				std::cout << "Tie!" << std::endl;
				break;
			default:
				break;
		}
	}
}


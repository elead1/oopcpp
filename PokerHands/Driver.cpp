/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Purpose: Receive input from a libconfig config file about several pairs
 * of poker hands.
 * Then, compares each pair of hands and returns which hand won.
 */

#include <libconfig.h++>
#include <iostream>
#include <sstream>
#include <climits>
#include "Rank.h"
#include "Suit.h"
#include "Card.h"
#include "Hand.h"

void loadHandsFromConfig(const libconfig::Config *conf, // Config to read
		std::array<std::array<Hand, 3>, 9> *handsToCompare, // Hands Matrix
		int lowerI, // Starting index for hands (from config file)
		int upperI, // Number of hands to read starting from lowerI
		int upperJ = 2, // Number of hands of each type to read
		int jOffset = 0) // For varying the number of hands for each type
{
	for(int i = lowerI; i < upperI; i++)
	{
		for(int j = 0; j < upperJ; j++)
		{
			int confHand = i * 2 + j + jOffset;
			std::stringstream confNameBase;
			confNameBase << "hand" << confHand << ".";
			//Build each card from config
			for(int k = 0; k < 5; k++)
			{
				std::stringstream confNameCard;
				confNameCard << "card" << k << ".";
				std::string baseQuery = confNameBase.str() + confNameCard.str();
				//Names of config parameters
				std::string suitQuery = baseQuery + "suit";
				std::string rankQuery = baseQuery + "rank";
				//Default values, to be overridden by lookup().
				std::string suitVal = "";
				const char *rankVal;
				conf->lookupValue(suitQuery, suitVal);
				conf->lookupValue(rankQuery, rankVal);

				Rank tmpRank = Rank::INVALIDRANK;
				Suit tmpSuit = Suit::INVALIDSUIT;
				//Get suit
				if(suitVal == "clubs")
				{
					tmpSuit = Suit::CLUBS;
				}
				else if(suitVal == "diamonds")
				{
					tmpSuit = Suit::DIAMONDS;
				}
				else if(suitVal == "hearts")
				{
					tmpSuit = Suit::HEARTS;
				}
				else if(suitVal == "spades")
				{
					tmpSuit = Suit::SPADES;
				}
				//Get rank
				switch(*rankVal)
				{
					case '2':
						tmpRank = Rank::TWO;
						break;
					case '3':
						tmpRank = Rank::THREE;
						break;
					case '4':
						tmpRank = Rank::FOUR;
						break;
					case '5':
						tmpRank = Rank::FIVE;
						break;
					case '6':
						tmpRank = Rank::SIX;
						break;
					case '7':
						tmpRank = Rank::SEVEN;
						break;
					case '8':
						tmpRank = Rank::EIGHT;
						break;
					case '9':
						tmpRank = Rank::NINE;
						break;
					case 'T':
						tmpRank = Rank::TEN;
						break;
					case 'J':
						tmpRank = Rank::JACK;
						break;
					case 'Q':
						tmpRank = Rank::QUEEN;
						break;
					case 'K':
						tmpRank = Rank::KING;
						break;
					case 'A':
						tmpRank = Rank::ACE;
						break;
					default:
						break;
				} // end switch
				Card c(tmpRank, tmpSuit);
				handsToCompare->at(i).at(j).addCard(c);
			} // end for k
		} // end for j
	} // end for i
} // end loadHandsFromConfig

int main()
{
	//2D matrix of Hands. 3 cols because 3 two pairs must be compared. [2]
	//will be empty for other rows.
	std::array<std::array<Hand, 3>, 9> handsToCompare;
	//Config object from libconfig
	libconfig::Config conf;
	try
	{
		conf.readFile("./pokerhands.conf");
	}
	catch (libconfig::ParseException pe)
	{
		std::cout << "ParseException text: " << pe.getError() << std::endl;
		std::cout << "ParseException line: " << pe.getLine() << std::endl;
		return -1;
	}

	loadHandsFromConfig(&conf, &handsToCompare, 0, 6);
	//There are three Two Pair hands in the config
	loadHandsFromConfig(&conf, &handsToCompare, 6, 7, 3);
	//The three Two Pair hands interrupt the normal pattern,
	//so our hand index needs an offset
	loadHandsFromConfig(&conf, &handsToCompare, 7, 9, 2, 1);

	for(auto row: handsToCompare)
	{
		double winningProb = INT_MAX;
		int winner = -1;
		int tyingHand = -1;
		bool tie = false;
		std::cout << "Comparing:" << std::endl;
		for(int i = 0; i < 3; i++)
		{
			if(!row[i].isFull())
			{
				continue;
			}
			std::cout << "\tHand " << i << ": "
					<< row[i].toString() << std::endl;
			if(row[i].rank() < winningProb)
			{
				winningProb = row[i].rank();
				winner = i;
			}
			else if(row[i].rank() == winningProb)
			{
				tie = true;
				tyingHand = i;
			}
		} // end for

		//Break ties.
		if(tie)
		{
			//winner will be set to the hand examined before a tie occurred.
			int pairwiseResult = Hand::handPerCardCompare(row[winner],
					row[tyingHand]);
			switch(pairwiseResult)
			{
				case -1:
					winner = tyingHand;
					tie = false;
					break;
				case 0:
					break;
				case 1:
					tie = false;
					break;
				default:
					break;
			} // end switch
		} // end if

		if(!tie)
		{
			std::cout << "Hand " << winner << " is the winner!" << std::endl;
			std::cout << "=-=-=-=-=-=-=" << std::endl;
		}
		else
		{
			std::cout << "There is a tie between Hand " << winner
					<< " and Hand " << tyingHand << "!" << std::endl;
		}
	} //end for

	return 0;
}


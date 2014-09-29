/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Purpose: Receive input from a libconfig config file about several pairs of poker hands.
 * Then, compares each pair of hands and returns which hand won.
 */

#include <libconfig.h++>
#include <iostream>
#include <sstream>
#include "Rank.h"
#include "Suit.h"
#include "Card.h"
#include "Hand.h"


int main()
{
	//2D matrix of Hands. 3 cols because 3 two pairs must be compared. [2] will be
	//empty for other rows.
	std::array<std::array<Hand, 3>, 9> handsToCompare;
	//Config object from libconfig
	libconfig::Config conf;

	conf.readFile("./pokerhands.conf");

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			int confHand = i * 9 + j;
			std::stringstream confNameBase = "hand";
			confNameBase << confHand << ".";
			//Build each card from config
			for(int k = 0; k < 5; k++)
			{
				std::stringstream confNameCard = "card";
				confNameCard << k << ".";
				std::string baseQuery = confNameBase.str() + confNameCard.str();
				//Names of config parameters
				std::string suitQuery = baseQuery + "suit";
				std::string rankQuery = baseQuery + "rank";
				//Default values, to be overridden by lookup().
				std::string suitVal = "";
				char rankVal = '\0';
				conf.lookup(suitQuery, &suitVal);
				conf.lookup(rankQuery, &rankVal);

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
				switch(rankVal)
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
				handsToCompare[i][j].addCard(Card(tmpRank, tmpSuit));
			} // end for k
		} // end for j
	} // end for i
	return 0;
}


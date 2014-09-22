/*
 * GameBoard.cpp
 * Author: eric
 * Purpose: 
 */

#include <iostream>
#include <sstream>
#include <cmath>
#include "GameBoard.h"

#define PLAYER1 1
#define PLAYER2 2
GameBoard::GameBoard( char p1Symbol, char p2Symbol )
{
	player1Symbol = p1Symbol;
	player2Symbol = p2Symbol;
	//std::cout << "player1  symbol param: " << p1Symbol << "\nplayer1 symbol member: " << player1Symbol << std::endl;
	//std::cout << "player2  symbol param: " << p2Symbol << "\nplayer2 symbol member: " << player2Symbol << std::endl;
	for(int i = 0; i <= CELLSPERROW; i++)
	{
		for(int j = 0; j <= CELLSPERCOL; j++)
		{
			//Row-major indexing
			Point tmp(i + 1, j + 1);
			cells[point2CellIndex(tmp)] = tmp;
		} // end column loop
	} // end row loop
} // end GameBoard( char, char )

char GameBoard::getP1Symbol( void ) const
{
	return player1Symbol;
}

char GameBoard::getP2Symbol( void ) const
{
	return player2Symbol;
}

bool GameBoard::addMove( int player, Point p)
{
	std::cout << "Player 1 symbol: " << player1Symbol << std::endl;
	int cellToPlaceIdx = point2CellIndex(p);
	//Point cellToPlace(cells[point2CellIndex(p)]);
	// Null character is not allowed symbol, so represents empty cell.
	if(cells[cellToPlaceIdx].isEmpty())
	{
		if(player == PLAYER1)
		{
			std::cout << "Player 1 symbol: " << player1Symbol << std::endl;
			cells[cellToPlaceIdx].setContents(player1Symbol);
			return true;
		}
		else if(player == PLAYER2)
		{
			std::cout << "Player 2 symbol: " << player2Symbol << std::endl;
			cells[cellToPlaceIdx].setContents(player2Symbol);
			return true;
		}
		//Invalid player.
		else
		{
			return false;
		}
	}
	//Cell already filled, invalid move.
	else
	{
		return false;
	}
} //end addMove(int, Point)

/*GameState GameBoard::getGameStatus( void )
{
	int cellsFilled = 0;

	for(int i = 0; i < NUMCELLS; i++)
	{
		if(cells[i].getContents().compare("") != 0)
		{
			cellsFilled++; // Contents are not null char, so cell is filled.
			//Check for winners
			if(cells[i].getContents().compare(player1Symbol) == 0 && isWinner(player1Symbol, cells[i]))
			{
				return GameState::PLAYER1WIN;
			}
			if(cells[i].getContents().compare(player2Symbol) == 0 && isWinner(player2Symbol, cells[i]))
			{
				return GameState::PLAYER2WIN;
			}
			//If no winner, and all cells filled, tie.
			if(cellsFilled == NUMCELLS)
			{
				return GameState::TIE;
			}

		} // end if
	} // end for
	return GameState::ONGOING;
} // end getGameStatus(void)*/

std::string GameBoard::getParseableBoard( void )
{
	std::string boardCopy = "";
	//Encode the contents of each cell into the board representation.
	for(int i = 0; i < NUMCELLS; i++)
	{
		boardCopy += Point(cells[i]).getContents();
	}
	return boardCopy;
} //end getParseableBoard(void)


std::string GameBoard::getPrintableBoard( void )
{
	std::string board = "";
	for(int i = 0; i < NUMCELLS; i++)
	{
		//Empty cell
		if(cells[i].isEmpty())
		{
			board += ' ';
			board += ' ';
			board += ' ';
		}
		//Filled cell
		else
		{
			board += ' ';
			board += cells[i].getContents();
			board += ' ';
		}
		//Last cell, no borders needed
		if(i == NUMCELLS - 1)
		{
			break;
		}
		switch((i + 1) % 3)
		{
			case 2:
			case 1:
				board += '|';
				break;
			case 0:
				board += '\n';
				board += "-----------\n";
				break;
		} // end switch
	} // end for
	return board;
} // end getPrintableBoard(void)

/*bool GameBoard::isWinner( char symbol, Point startHere )
{
	//Possible wins are:
	// * horizontal (x-1, x, x+1)
	// * vertical (y-1, y, y+1)
	// * diagonal:
	//   * ({x-1,y-1}, {x,y}, {x+1,y+1})
	//   * ({x+1,y-1}, {x,y}, {x-1,y+1})

	//Check horizontal; only check horizontal for cells in middle column
	int middleColX = floor(CELLSPERCOL * 1.0 / 2);
	Point leftNeighborPoint(startHere.getX() - 1, startHere.getY());
	Point rightNeighborPoint(startHere.getX() + 1, startHere.getY());
	Point boardLeftNeighbor = cells[point2CellIndex(leftNeighborPoint)];
	Point boardRightNeighbor = cells[point2CellIndex(rightNeighborPoint)];
	if(startHere.getX() - 1 == middleColX)
	{
		if((boardLeftNeighbor.getContents() == symbol)
				&& (boardRightNeighbor.getContents() == symbol))
		{
			return true;
		}
	}

	//Check vertical; only check vertical for cells in middle row
	int middleRowY = floor(CELLSPERROW * 1.0 / 2);
	Point upNeighborPoint(startHere.getX(), startHere.getY() - 1);
	Point downNeighborPoint(startHere.getX(), startHere.getY() + 1);
	Point boardUpNeighbor = cells[point2CellIndex(upNeighborPoint)];
	Point boardDownNeighbor = cells[point2CellIndex(downNeighborPoint)];
	if(startHere.getY() - 1 == middleRowY)
	{
		if((boardUpNeighbor.getContents() == symbol)
				&& (boardDownNeighbor.getContents() == symbol))
		{
			return true;
		}
	}

	//Check diagonals; only check diagonals for center cell
	int centerCellIndex = (floor(CELLSPERROW * 1.0 / 2) * CELLSPERROW + floor(CELLSPERCOL * 1.0 / 2));
	Point diagUpLeftNeighbor(startHere.getX() - 1, startHere.getY() - 1);
	Point diagUpRightNeighbor(startHere.getX() + 1, startHere.getY() - 1);
	Point diagDownLeftNeighbor(startHere.getX() - 1, startHere.getY() + 1);
	Point diagDownRightNeighbor(startHere.getX() + 1, startHere.getY() + 1);
	Point boardUpLeftNeighbor = cells[point2CellIndex(diagUpLeftNeighbor)];
	Point boardUpRightNeighbor = cells[point2CellIndex(diagUpLeftNeighbor)];
	Point boardDownLeftNeighbor = cells[point2CellIndex(diagDownLeftNeighbor)];
	Point boardDownRightNeighbor = cells[point2CellIndex(diagDownRightNeighbor)];
	if(point2CellIndex(startHere) == centerCellIndex)
	{
		if((boardUpLeftNeighbor.getContents() == symbol
				&& boardDownRightNeighbor.getContents() == symbol))
		{
			return true;
		}
		if((boardUpRightNeighbor.getContents() == symbol
				&& boardDownLeftNeighbor.getContents() == symbol))
		{
			return true;
		}
	}

	//No other options, no winner.
	return false;
}*/

int GameBoard::point2CellIndex(Point p)
{
	return (p.getX() - 1) * CELLSPERROW + (p.getY() - 1);
}

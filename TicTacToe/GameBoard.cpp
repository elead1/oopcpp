/*
 * GameBoard.cpp
 * Author: eric
 * Purpose: 
 */

#include <sstream>
#include "GameBoard.h"

#define PLAYER1 1
#define PLAYER2 2
GameBoard::GameBoard( char player1Symbol, char player2Symbol )
	: GameBoard::player1Symbol(player1Symbol), GameBoard::player2Symbol(player2Symbol)
{
	for(int i = 0; i <= cellsPerRow; i++)
	{
		for(int j = 0; j <= cellsPerRow; j++)
		{
			cells[i + j] = Point(i + 1, j + 1);
		} // end column loop
	} // end row loop
} // end GameBoard( char, char )

bool GameBoard::addMove( int player, Point p)
{
	Point cellToPlace = cells[p.getX() - 1 + p.getY() - 1];
	// Null character is not allowed symbol, so represents empty cell.
	if(cellToPlace.getContents() == '\0')
	{
		if(player == PLAYER1)
		{
			cellToPlace.setContents(player1Symbol);
			return true;
		}
		else if(player == PLAYER2)
		{
			cellToPlace.setContents(player2Symbol);
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

GameState GameBoard::getGameStatus( void )
{
	int cellsFilled = 0;

	for(int i = 0; i < numCells; i++)
	{
		if(checkWinner(player1Symbol, cells[i]))
		{
			return GameState::PLAYER1WIN;
		}
		if(checkWinner(player2Symbol, cells[i]))
		{
			return GameState::PLAYER2WIN;
		}
		if(cells[i].getContents() != '\0')
		{
			cellsFilled++;
			if(cellsFilled == numCells)
			{
				return GameState::TIE;
			}
		} // end if
	} // end for
} // end getGameStatus(void)

Point* GameBoard::getBoard( void )
{
	Point copy[numCells];
	//Make deep copy of cells array to protect the actual game board.
	for(int i = 0; i < numCells; i++)
	{
		copy[i] = Point(cells[i]);
	}
	return copy;
} //end getBoard(void)

std::string GameBoard::getPrintableBoard( void )
{
	std::string board = "";
	for(int i = 0; i < numCells; i++)
	{
		//Empty cell
		if(cells[i].getContents() == '\0')
		{
			board << ' ' << ' ' << ' ';
		}
		//Filled cell
		else
		{
			board << ' ' << cells[i].getContents() << ' ';
		}
		//Last cell, no borders needed
		if(i == numCells - 1)
		{
			break;
		}
		switch(i % 2)
		{
			case 2:
			case 1:
				board << '|';
				break;
			case 0:
				board << '\n';
				board << '-----------\n';
				break;
		} // end switch
	} // end for
	return board;
} // end getPrintableBoard(void)

bool GameBoard::checkWinner( char symbol, Point startHere )
{
	//Possible wins are:
	// * horizontal (x-1, x, x+1)
	// * vertical (y-1, y, y+1)
	// * diagonal:
	//   * ({x-1,y-1}, {x,y}, {x+1,y+1})
	//   * ({x+1,y-1}, {x,y}, {x-1,y+1})
}

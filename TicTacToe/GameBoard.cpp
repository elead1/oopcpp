/*
 * GameBoard.cpp
 * Author: Eric Leadbetter
 * Purpose: Represents a TicTacToe gameboard, providing capabilities to retrieve the board
 * and to add new moves to the board.
 */

#include <iostream>
#include <cmath>
#include "GameBoard.h"

//Constants to refer to each player by 'name'
#define PLAYER1 1
#define PLAYER2 2

/*
 * GameBoard(char, char)
 * Purpose: Create a new GameBoard with specified chars as player 1 and player 2's symbols.
 * Input: p1Symbol, p2Symbol the symbols to assign to the players.
 */
GameBoard::GameBoard( char p1Symbol, char p2Symbol )
{
	player1Symbol = p1Symbol;
	player2Symbol = p2Symbol;
	for(int i = 0; i < CELLSPERROW; i++)
	{
		for(int j = 0; j < CELLSPERCOL; j++)
		{
			//Row-major indexing
			Point tmp(i + 1, j + 1);
			cells[point2CellIndex(tmp)] = tmp;
		} // end column loop
	} // end row loop
} // end GameBoard( char, char )

/*
 * getP1Symbol( void ) const
 * Purpose: Return the first player's symbol.
 */
char GameBoard::getP1Symbol( void ) const
{
	return player1Symbol;
} // end getP1Symbol()

/*
 * getP2Symbol( void ) const
 * Purpose: Return the second player's symbol.
 */
char GameBoard::getP2Symbol( void ) const
{
	return player2Symbol;
} // end getP2Symbol()

/*
 * addMove(int, Point)
 * Purpose: Make a move for the given player at the cell specified by the Point.
 * Input: player - the index for the player making a move (1 or 2); p - the Point to place the
 * player's symbol at.
 * Output: true if the move is successful, false if the desired cell is already filled
 */
bool GameBoard::addMove( int player, Point p)
{
	int cellToPlaceIdx = point2CellIndex(p);

	if(cells[cellToPlaceIdx].isEmpty())
	{
		if(player == PLAYER1)
		{
			cells[cellToPlaceIdx].setContents(player1Symbol);
			return true;
		}
		else if(player == PLAYER2)
		{
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

/*
 * getGameStatus( void )
 * Purpose: Return the enum value from GameState that represents the current state of the
 * GameBoard. States are ONGOING (empty cells still exist, no winner), TIE (no empty cells),
 * PLAYER1WIN (player 1 has won), and PLAYER2WIN (player 2 has won).
 * Output: A value of GameState matching the game board's state.
 */
GameState GameBoard::getGameStatus( void )
{
	int cellsFilled = 0; //Track how many cells are filled to determine TIE.

	for(int i = 0; i < NUMCELLS; i++)
	{
		if(!cells[i].isEmpty())
		{
			cellsFilled++; // Cell is filled.
			//Check for winners
			if(cells[i].getContents() == player1Symbol
					&& isWinner(player1Symbol, cells[i]))
			{
				return GameState::PLAYER1WIN;
			}
			if(cells[i].getContents() == player1Symbol
					&& isWinner(player2Symbol, cells[i]))
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
} // end getGameStatus(void)

/*
 * getParseableBoard( void )
 * Purpose: Return a representation of the board as a string for ease of parsing. Each
 * element of the string is one cell of the board. A space (' ') represents an empty cell.
 * Output: A string representation of the board.
 */
std::string GameBoard::getParseableBoard( void )
{
	std::string boardCopy = "";
	//Encode the contents of each cell into the board representation, one character per cell.
	for(int i = 0; i < NUMCELLS; i++)
	{
		boardCopy += cells[i].getContents();
	}
	return boardCopy;
} //end getParseableBoard(void)

/*
 * getPrintableBoard( void )
 * Purpose: Generate a formatted, ASCII art representation of the board for console printing.
 * Output: A string containing the formatted ASCII art representation of the board.
 */
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

/*
 * isWinner( char, Point )
 * Purpose: Determines if the given symbol is a winner, starting from a given point. Since
 * this is only called by getGameStatus(), and getGameStatus() tests for a winner at every
 * cell, we only need to test from the centered cells since a win from a non-centered cell
 * will be picked up in a win from a centered cell.
 * Possible wins are:
 * > horizontal (x-1, x, x+1)
 * > vertical (y-1, y, y+1)
 * > diagonal:
 *     > ({x-1,y-1}, {x,y}, {x+1,y+1})
 *     > ({x+1,y-1}, {x,y}, {x-1,y+1})
 * Input: symbol - the symbol to evaluate for a win; startHere - the Point to examine around.
 * Output: true if the given symbol has a winning sequence from the given Point, else false.
 */
bool GameBoard::isWinner( char symbol, Point startHere )
{
	//

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
	int centerCellIndex = (floor(CELLSPERROW * 1.0 / 2) * CELLSPERROW
			+ floor(CELLSPERCOL * 1.0 / 2));
	Point diagUpLeftNeighbor(startHere.getX() - 1, startHere.getY() - 1);
	Point diagUpRightNeighbor(startHere.getX() + 1, startHere.getY() - 1);
	Point diagDownLeftNeighbor(startHere.getX() - 1, startHere.getY() + 1);
	Point diagDownRightNeighbor(startHere.getX() + 1, startHere.getY() + 1);
	Point boardUpLeftNeighbor = cells[point2CellIndex(diagUpLeftNeighbor)];
	Point boardUpRightNeighbor = cells[point2CellIndex(diagUpRightNeighbor)];
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

	//No other options, not a winner.
	return false;
}

/*
 * point2CellIndex( Point )
 * Purpose: Calculate the index for the cells array based on the given Point's x and y value.
 * Input: p - A Point with coordinates to generate an index from.
 * Output: An integer index into the cells array for the given Point.
 */
int GameBoard::point2CellIndex(Point p)
{
	return (p.getX() - 1) * CELLSPERROW + (p.getY() - 1);
}

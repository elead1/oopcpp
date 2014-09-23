/*
 * GameBoard.h
 * Author: Eric Leadbetter
 * Purpose: Represents a TicTacToe gameboard, providing capabilities to retrieve the board
 * and to add new moves to the board.
 */
#ifndef GameBoard_H
#define GameBoard_H

#include <cstring>
#include "Point.h"
#include "GameState.h"

class GameBoard
{
	public:
		GameBoard( void ) //Defaults the players' symbols to 'X' and 'O'
			: GameBoard('X', 'O'){}
		GameBoard( char player1Symbol, char player2Symbol );
		bool addMove( int player, Point p);
		GameState getGameStatus( void );
		std::string getParseableBoard( void );
		std::string getPrintableBoard( void );
		char getP1Symbol( void ) const;
		char getP2Symbol( void ) const;
		const static int NUMCELLS = 9; //Constant for the number of cells in the board.
	private:
		const static int CELLSPERROW = 3; //Private constant for number of cells in a row
		const static int CELLSPERCOL = 3; //Private constant for number of cells in a column
		Point cells[NUMCELLS]; //Holds the Points making up the board. Indexed by row-major.
		char player1Symbol; //The first player's chosen symbol
		char player2Symbol; //The second player's chosen symbol
		bool isWinner(char symbol, Point startHere );
		int point2CellIndex(Point p);
};

#endif

/*
 * GameBoard.h
 * Author: Eric Leadbetter
 * Purpose:
 */
#ifndef GameBoard_H
#define GameBoard_H
#include <cstring>
#include "Point.h"
#include "GameState.h"

class GameBoard
{
	public:
		GameBoard( void )
			: GameBoard(88, 79){}
		GameBoard( char player1Symbol, char player2Symbol );
		bool addMove( int player, Point p);
		GameState getGameStatus( void );
		std::string getParseableBoard( void );
		std::string getPrintableBoard( void );
		char getP1Symbol( void ) const;
		char getP2Symbol( void ) const;
	private:
		const static int NUMCELLS = 9;
		const static int CELLSPERROW = 3;
		const static int CELLSPERCOL = 3;
		Point cells[NUMCELLS];
		char player1Symbol;
		char player2Symbol;
		bool isWinner(char symbol, Point startHere );
		int point2CellIndex(Point p);
};

#endif

/*
 * GameBoard.h
 * Author: Eric Leadbetter
 * Purpose: 
 */
#include "Point.h"
#include "GameState.h"

class GameBoard
{
	public:
		GameBoard( void );
		GameBoard( char player1Symbol, char player2Symbol );
		bool addMove( int player, Point p);
		GameState getGameStatus( void );
		Point* getBoard( void );
	private:
		Point cells[9];
		char player1Symbol;
		char player2Symbol;
};




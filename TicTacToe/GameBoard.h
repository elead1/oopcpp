/*
 * GameBoard.h
 * Author: Eric Leadbetter
 * Purpose: 
 */
#include <cstring>
#include "Point.h"
#include "GameState.h"

class GameBoard
{
	public:
		GameBoard( void )
			: GameBoard('X', 'O'){}
		GameBoard( char player1Symbol, char player2Symbol );
		bool addMove( int player, Point p);
		GameState getGameStatus( void );
		Point* getBoard( void );
		std::string getPrintableBoard( void );
	private:
		const int numCells = 9;
		const int cellsPerRow = 3;
		Point cells[numCells];
		char player1Symbol;
		char player2Symbol;
		bool checkWinner(char symbol, Point startHere );
};




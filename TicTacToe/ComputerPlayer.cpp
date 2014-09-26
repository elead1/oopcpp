/*
 * ComputerPlayer.cpp
 * Author: Eric Leadbetter
 * Purpose: Provides an automated player to contend with the user in a game of Tic Tac Toe.
 */

#include "ComputerPlayer.h"
#include "GameState.h"
#include "GameBoard.h"

/*
 * makeMove( std::string )
 * Purpose: Generate a move based on the provided game board representation.
 * Input: board - A string with each element representing one cell of a tic tac toe board.
 * Output: A Point corresponding to a cell at which the computer player wishes to make a move.
 */
Point ComputerPlayer::makeMove( std::string board )
{
	Point random = findMove(board);
	return random;
}

/*
 * findMove( std::string )
 * Purpose: Find a general move on the board; no guarantee of winning move.
 * Input: board - A string with each element representing one cell of a tic tac toe board.
 * Output: A Point corresponding to an empty cell at which to make a move.
 */
Point ComputerPlayer::findMove( std::string board )
{
	for(int i = 0; i < board.length(); i++)
	{
		if(board[i] == ' ')
		{
			//Indices are mapped to Points using row-major order.
			int y = i % BOARDYDIM;
			int x = (i - y) / BOARDYDIM;
			return Point(x + 1, y + 1);
		}
	}
	//Return an invalid point (on a Tic Tac Toe board) if there are no available moves.
	return Point(-1, -1);
}

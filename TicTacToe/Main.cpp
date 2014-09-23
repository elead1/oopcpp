/*
 * Main.cpp
 * Author: Eric Leadbetter
 * Date: 9/19/2014
 * Class: 605.401 Programming in C++, Hal Pierson, Doug Ferguson
 * Purpose: Drives the tic tac toe game.
 */

#include <iostream>
#include "GameBoard.h" // Includes GameState.h and Point.h
#include "ComputerPlayer.h"

#define USERPLAYER 1
#define COMPUTERPLAYER 2

/*
 * reportGameState( GameBoard )
 * Purpose: To print out the state of the game if the game is over.
 * Input: board - the GameBoard with the state to evaluate.
 * Output: 0 if in a valid state, -1 if invalid (should never occur).
 */
int reportGameState(GameBoard board)
{
	switch(board.getGameStatus())
	{
		case GameState::ONGOING:
			break;
		case GameState::TIE:
			std::cout << "Game over! No more moves. It's a tie!" << std::endl;
			break;
		case GameState::PLAYER1WIN:
			std::cout << "Game over! Player 1 wins!" << std::endl;
			break;
		case GameState::PLAYER2WIN:
			std::cout << "Game over! Player 2 wins!" << std::endl;
			break;
		default:
			std::cout << "Error. Invalid gamestate. Exiting." << std::endl;
			return -1;
	} // end switch
	return 0;
} //end reportGameState( GameBoard )

int main()
{
	GameState state = GameState::ONGOING; //Initialize loop control
	ComputerPlayer pc; //Create new computer player
	GameBoard board; //Create a new game board
	//Define input variables
	int xMove;
	int yMove;

	//Display initial board
	std::cout << board.getPrintableBoard() << std::endl;

	while(state == GameState::ONGOING)
	{
		//Get user input
		std::cout << "Enter move as cell coordinates (top-left would be \"1 1\"): ";
		std::cin >> xMove;
		std::cin >> yMove;

		//Create a Point to make move from user's input.
		Point move(xMove, yMove);
		//If move is invalid, skip rest of loop and get new input.
		if(!board.addMove(USERPLAYER, move))
		{
			continue;
		}

		//Print updated board.
		std::cout << board.getPrintableBoard() << std::endl;

		//Make sure user player didn't make last possible move.
		if(board.getGameStatus() != GameState::ONGOING)
		{
			return reportGameState(board);
		}

		//makeMove() is guaranteed to make a valid move
		Point pcMove = pc.makeMove(board.getParseableBoard());
		board.addMove(COMPUTERPLAYER, pcMove);

		//Print updated board.
		std::cout << "Computer makes a move!" << std::endl;
		std::cout << board.getPrintableBoard() << std::endl;

		//If game is over, finish up.
		if(board.getGameStatus() != GameState::ONGOING)
		{
			return reportGameState(board);
		}
	} // end while
} // end main


//Test Point class
/*
int main()
{
	Point p(1, 1);
	std::cout << "(" << p.getX() << ", " << p.getY() << ")" << std::endl;
	p.setContents('Q');
	std::cout << "contents: " << p.getContents() << std::endl;
	return 0;
}
*/

//Test GameBoard class
/*
int main()
{
	GameBoard board;
	std::cout << board.getPrintableBoard() << std::endl;
	board.addMove(USERPLAYER, Point(1,3));
	std::cout << board.getPrintableBoard() << std::endl;
	board.addMove(USERPLAYER, Point(2,2));
	std::cout << board.getPrintableBoard() << std::endl;
	std::cout << "Game status: " << board.getGameStatus() << std::endl;
	board.addMove(USERPLAYER, Point(3,1));
	std::cout << board.getPrintableBoard() << std::endl;
	std::cout << "Game status: " << board.getGameStatus() << std::endl;
	return 0;
}
*/

//Test ComputerPlayer class
/*
int main()
{
	ComputerPlayer pc;
	Point pcMove = pc.makeMove("X        ");
	std::cout << "Computer move: (" << pcMove.getX() << ", " << pcMove.getY() << ")" << std::endl;
	return 0;
}
*/

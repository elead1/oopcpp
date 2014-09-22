/*
 * Main.cpp
 * Author: eric
 * Purpose: 
 */

#include <iostream>
#include "GameBoard.h" // Includes GameState.h and Point.h
#include "ComputerPlayer.h"

#define USERPLAYER 1
#define COMPUTERPLAYER 2

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
}

int main()
{
	GameState state = GameState::ONGOING;
	ComputerPlayer pc;
	GameBoard board;
	int xMove;
	int yMove;

	while(state == GameState::ONGOING)
	{
		std::cout << board.getPrintableBoard() << std::endl;
		std::cout << "Enter move as cell coordinates (top-left would be \"1 1\"): ";
		std::cin >> xMove;
		std::cin >> yMove;
		Point move(xMove, yMove);
		if(!board.addMove(USERPLAYER, move))
		{
			continue;
		}
		std::cout << board.getPrintableBoard() << std::endl;
		//Make sure user player didn't make last possible move.
		if(board.getGameStatus() != GameState::ONGOING)
		{
			return reportGameState(board);
		}
		//makeMove() is guaranteed to make a valid move
		Point pcMove = pc.makeMove(board.getParseableBoard());
		board.addMove(COMPUTERPLAYER, pcMove);
		std::cout << board.getPrintableBoard() << std::endl;
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

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
		//makeMove() is guaranteed to make a valid move
		Point pcMove = pc.makeMove(board.getBoard());
		std::cout << board.getPrintableBoard() << std::endl;
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
	} // end while
} // end main


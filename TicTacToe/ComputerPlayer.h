/*
 * ComputerPlayer.h
 * Author: Eric Leadbetter
 * Purpose: Provides an automated player to contend with the user in a game of Tic Tac Toe.
 */
#ifndef ComputerPlayer_H
#define ComputerPlayer_H

#include <iostream>
#include <time.h>
#include "Point.h"

class ComputerPlayer
{
	public:
		Point makeMove( std::string board );
	private:
		Point findMove( std::string board );
		const static int BOARDXDIM = 3; //Used internally in index calculations
		const static int BOARDYDIM = 3; //Used internally in index calculations
};


#endif

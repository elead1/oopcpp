/*
 * ComputerPlayer.h
 * Author: Eric Leadbetter
 * Purpose: 
 */
#ifndef ComputerPlayer_H
#define ComputerPlayer_H
#include <iostream>
#include "Point.h"

class ComputerPlayer
{
	public:
		Point makeMove( std::string board );
	private:
		Point findWin( std::string board );
		Point findMove( std::string board );
		const static int BOARDXDIM = 3;
		const static int BOARDYDIM = 3;
};


#endif

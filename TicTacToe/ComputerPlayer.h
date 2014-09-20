/*
 * ComputerPlayer.h
 * Author: Eric Leadbetter
 * Purpose: 
 */

#include "Point.h"

class ComputerPlayer
{
	public:
		Point makeMove( Point* board );
	private:
		Point findWin( Point* board );
		Point findMove( Point* board );
};




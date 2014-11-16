/*
 * Elevator.cpp
 * Author: eric
 * Purpose: 
 */

#include "Elevator.h"

void Elevator::moveUp()
{
	if(this->state == STOPPED
			&& this->previousFloor == 100)
	{
		throw std::logic_error("Already at top floor.");
	}
	if(this->state == STOPPED)
	{
		this->timeSinceStateChange = 0;
	}

	this->state = MOVING_UP;
}

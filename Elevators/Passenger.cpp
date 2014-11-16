/*
 * Passenger.cpp
 * Author: eric
 * Purpose: 
 */

#include "Passenger.h"

void Passenger::increaseTimer()
{
	if(this->state == WAITING)
	{
		this->waitingTime++;
	}
	else if(this->state == RIDING)
	{
		this->ridingTime++;
	}
}

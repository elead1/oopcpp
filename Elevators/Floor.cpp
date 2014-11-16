/*
 * Floor.cpp
 * Author: eric
 * Purpose: 
 */

#include "Floor.h"

void Floor::queuePassenger(const Passenger &passenger)
{
	this->passengerLine.push(passenger);
}

void Floor::loadPassenger(Elevator &elevator)
{
	int freeSpace = elevator.getAvailableSpace();
	int passengersWaiting = this->passengerLine.size();
	//Load the lesser of the two values so we don't run out of passengers
	//or space.
	int numPassengersToLoad = (freeSpace > passengersWaiting ?
			passengersWaiting : freeSpace);
	for(int i = 0; i < numPassengersToLoad; i++)
	{
		Passenger p = this->passengerLine.pop();
		p.setRiding();
		elevator.addPassenger(p);
	}
}

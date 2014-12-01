/*
 * Floor.cpp
 * Author: eric
 * Purpose: 
 */

#include "Floor.h"

void Floor::queuePassenger(const Passenger &passenger)
{
	this->passengerLine.push_back(passenger);
} // end queuePassenger

void Floor::loadPassengers(Elevator &elevator)
{
	int freeSpace = elevator.getAvailableSpace();
	int passengersWaiting = this->passengerLine.size();
	//Load the lesser of the two values so we don't run out of passengers
	//or space.
	int numPassengersToLoad = (freeSpace > passengersWaiting ?
			passengersWaiting : freeSpace);
	for(int i = 0; i < numPassengersToLoad; i++)
	{
		Passenger p = this->passengerLine.front();
		this->passengerLine.pop_front();
		p.setRiding();
		elevator.addPassenger(p);
	} // end for -- passengers loaded onto elevator
} // end loadPassengers

void Floor::updatePassengers()
{
	for(Passenger &p : this->passengerLine)
	{
		p.increaseTimer();
	} // end for -- all passengers' timers updated
} // end updatePassengers

bool Floor::hasPassengersWithLoadTime(int time)
{
	for(Passenger &p : this->passengerLine)
	{
		if(p.getQueueTime() <= time)
		{
			return true;
		}
	}
	return false;
} // end hasPassengersWithLoadTime

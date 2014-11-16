/*
 * Floor.h
 * Author: eric
 * Purpose: 
 */
#ifndef Floor_H
#define Floor_H

#include <queue>
#include "Passenger.h"
#include "Elevator.h"

class Floor
{
	public:
		Floor()
			: Floor(0)
		{}
		Floor(int floorNum)
			: floorNum(floorNum)
	  {}
		virtual ~Floor() {};
		void queuePassenger(const Passenger &passenger);
		void loadPassenger(Elevator &elevator);
		const inline int getFloorNum()
		{
			return this->floorNum;
		}
	private:
		int floorNum;
		std::queue<Passenger> passengerLine;
};

#endif

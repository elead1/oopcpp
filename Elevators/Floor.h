/*
 * Floor.h
 * Author: eric
 * Purpose: 
 */
#ifndef Floor_H
#define Floor_H

#include <deque>
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
		void loadPassengers(Elevator &elevator);
		void updatePassengers();
		bool hasPassengersWithLoadTime(int time) ;
		inline int getFloorNum() const
		{
			return this->floorNum;
		}
		inline int getPassengerCount() const
		{
			return this->passengerLine.size();
		}
	private:
		int floorNum;
		std::deque<Passenger> passengerLine;
};

#endif

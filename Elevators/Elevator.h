/*
 * Elevator.h
 * Author: eric
 * Purpose: 
 */
#ifndef Elevator_H
#define Elevator_H

#include <vector>
#include <array>
#include "Passenger.h"

enum ElevatorState {MOVING_UP, MOVING_DOWN, STOPPING, STOPPED};

class Elevator
{
	public:
		Elevator()
			: Elevator(8, 10, 1)
		{}
		Elevator(int capacity, int speed, int initFloor)
			: capacity(capacity), speed(speed), previousFloor(initFloor),
			  destination(initFloor), timeSinceStateChange(0), state(STOPPED)
		{}
		virtual ~Elevator() {};
		void moveUp();
		void moveDown();
		void addPassenger(const Passenger &p);
		std::vector<Passenger> unloadPassengers();
		void stop();
		void setStopped();
		const inline int getAvailableSpace()
		{
			return this->capacity - this->passengers.size();
		}
		const inline int getPassengerCount()
		{
			return this->passengers.size();
		}
		const int getClosestFloor();
		void update();
		const inline ElevatorState getState()
		{
			return this->state;
		}
	private:
		ElevatorState state;
		int previousFloor;
		int destination;
		int speed;
		int timeSinceStateChange;
		int capacity;
		std::array<Passenger, capacity> passengers;
};

#endif

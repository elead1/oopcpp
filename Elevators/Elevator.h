/*
 * Elevator.h
 * Author: eric
 * Purpose: 
 */
#ifndef Elevator_H
#define Elevator_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Passenger.h"

enum ElevatorState {MOVING_UP, MOVING_DOWN, STOPPING, STOPPED};

class Elevator
{
	public:
		Elevator()
			: Elevator(10, 1)
		{}
		Elevator(int speed, int initFloor)
		{
			this->capacity = 8;
			this->speed = speed;
			this->currentFloor = initFloor;
			this->destination = initFloor;
			this->timeSinceStateChange = 0;
			this->timeStopping = 0;
			this->state = ElevatorState::STOPPED;
			this->lastDirection = ElevatorState::MOVING_UP;
		}
		virtual ~Elevator() {};
		void moveUp();
		void moveDown();
		void addPassenger(const Passenger &p);
		std::vector<Passenger> unloadPassengers();
		void updatePassengers();
		void slow();
		void stop();
		inline int getAvailableSpace() const
		{
			return this->capacity - this->passengers.size();
		}
		inline int getPassengerCount() const
		{
			return this->passengers.size();
		}
		inline bool hasPassengers() const
		{
			return this->passengers.size() > 0;
		}
		inline double getCurrentFloor() const
		{
			return this->currentFloor;
		}
		inline ElevatorState getState() const
		{
			return this->state;
		}
		//If we were just moving upward, we passed the floors reachable by
		//MOVING_DOWN, so we should keep going up.
		inline bool shouldGoUp() const
		{
			return (this->lastDirection == ElevatorState::MOVING_UP ? true
					: false);
		}
		bool havePassengerForCurrentFloor();
	private:
		ElevatorState state;
		ElevatorState lastDirection;
		double currentFloor;
		int destination;
		int speed;
		int timeSinceStateChange;
		int timeStopping;
		static int capacity;
		std::vector<Passenger> passengers;
};

#endif

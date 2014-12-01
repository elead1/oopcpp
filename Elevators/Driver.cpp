/*
 * Driver.cpp
 * Author: eric
 * Purpose: 
 */
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Passenger.h"
#include "Floor.h"
#include "Elevator.h"

void buildElevators(int speed, std::array<Elevator, 4> *elevators)
{
	for(int i = 0; i < 4; i++)
	{
		//Elevators start on floors 25, 50, 75, 100
		elevators->at(i) = Elevator(speed, 25 * (i+1));
	} // end for
} // end buildElevators

int initializeFloors(std::array<Floor, 101> *floors)
{
	int passengerCount = 0;
	std::string filename = "/home/eric/Documents/Elevators.csv";
	std::ifstream file;
	file.open(filename);

	if(!file.is_open())
	{
		std::cerr << "Could not open Elevators.csv" << std::endl;
		return -1;
	} // end if

	//Skip header line of CSV
	std::string line;
	std::getline(file, line);

	//Initialize floors and passengers.
	std::array<Floor, 101> stories;
	for(int i = 1; i <= 100; i++)
	{
		stories[i] = Floor(i);
	} // end for

	char strvals[256]; //Extract values into this.
	int  vals[3]; //Parse values into this
	while(std::getline(file, line))
	{
		std::stringstream lineParser(line);
		int i = 0;
		while(lineParser.good())
		{
			lineParser.getline(strvals, 256, ',');
			vals[i] = atoi(strvals);
			i++;
		} // end inner while
		stories[vals[1]].queuePassenger(Passenger(vals[0], vals[2]));
		passengerCount++;
	} // end outer while
	//Done with the file.
	file.close();
	return passengerCount;
}

void runSimulation(int passengerCount, std::array<Elevator, 4> *elevators,
		std::array<Floor, 101> *floors)
{
	//Keeps track of passengers after getting off elevators, for stats
	std::vector<Passenger> processedPassengers;
	//Run first simulation
	int time = 0;
	while(processedPassengers.size() < passengerCount)
	{
		time++;
		for(Elevator &e : *elevators)
		{
			if(e.havePassengerForCurrentFloor())
			{
				switch(e.getState())
				{
					case ElevatorState::MOVING_UP:
					case ElevatorState::MOVING_DOWN:
					{
						e.slow();
						break;
					} // end case MOVING_DOWN
					case ElevatorState::STOPPING:
					{
						//e.stop();
						break;
					} // end case MOVING_STOPPING
					case ElevatorState::STOPPED:
					{
						std::vector<Passenger> unloaded = e.unloadPassengers();
						processedPassengers.insert(processedPassengers.end(),
								unloaded.begin(), unloaded.end());
						break;
					} // end case STOPPED
				} // end switch(e.getState)
			} // end if passengersForCurrentFloor

			//Is elevator stopped at a floor, or is it between floors.
			int castedCurrentFloor = (int)e.getCurrentFloor();
			bool atFloor = castedCurrentFloor - e.getCurrentFloor() == 0;
			//If so, pick up passengers
			if(atFloor &&
					e.getAvailableSpace() > 0 &&
					floors->at(castedCurrentFloor)
						.hasPassengersWithLoadTime(time))
			{
				floors->at(castedCurrentFloor).loadPassengers(e);
			} // end if

			//Choose how to move
			switch(e.getState())
			{

				//Elevators follow Newton's first law:
				//They only change direction after stopping (or hit floor limit)
				case ElevatorState::MOVING_UP:
				{
					if(e.getCurrentFloor() < 100)
					{
						e.moveUp();
					}
					else
					{
						e.moveDown();
					}
					break;
				} // end case MOVING_UP
				case ElevatorState::MOVING_DOWN:
				{
					if(e.getCurrentFloor() > 1)
					{
						e.moveDown();
					}
					else
					{
						e.moveUp();
					}
					break;
				} // end case MOVING_DOWN
				case ElevatorState::STOPPING:
				{
					//The 'STOPPING' case is handled above. This case block
					//should never get executed.
					break;
				} // end case STOPPING
				case ElevatorState::STOPPED:
				{
					//Deliver current passengers before seeking new ones.
					if(e.hasPassengers())
					{
						if(e.shouldGoUp())
						{
							e.moveUp();
						} // end if
						else
						{
							e.moveDown();
						} // end else
					} // end if hasPassengers
					//Oscillate out from current floor seeking for passengers
					else
					{
						int currentFloor = (int)e.getCurrentFloor();
						int i = 1;
						int onFloor = 0;
						bool passengersFound = false;
						while(!passengersFound &&
								currentFloor + i <= 100 &&
								currentFloor - i >= 1)
						{
							onFloor = currentFloor + i;
							if(floors->at(onFloor)
									.hasPassengersWithLoadTime(time))
							{
								passengersFound = true;
							} // end if hasPassengers for time
							else
							{
								onFloor = currentFloor - i;
								if(floors->at(onFloor)
										.hasPassengersWithLoadTime(time))
								{
									passengersFound = true;
								} // end if--found passengers
							} // end else
							i++;
						}
						if(onFloor > currentFloor)
						{
							try
							{
								e.moveUp();
							}
							catch(std::exception &except)
							{
								e.moveDown();
							}
						} // end if -- closest waiting passenger is above
						else
						{
							try
							{
								e.moveDown();
							}
							catch(std::exception &except)
							{
								e.moveUp();
							}
						} // end if -- closest waiting passenger is below
					} // end else -- found new passenger
					break;
				} // end case STOPPED
			} // end switch -- figured out how to move
		} // end for -- time for next elevator

		//Update passenger's times (only passengers waiting or riding).
		for(Floor &f : *floors)
		{
			f.updatePassengers();
		}
		for(Elevator &e : *elevators)
		{
			e.updatePassengers();
		}
	} // end while -- finished simulation

	//Calculate stats
	int waitSum = 0;
	int rideSum = 0;
	for(Passenger &p : processedPassengers)
	{
		waitSum += p.getWaitingTime();
		rideSum += p.getRidingTime();
	}

	std::cout << "At 10 second travel time between floors:" << std::endl;
	std::cout << "Average waiting time: " <<
			(waitSum / 1.0 * passengerCount) << std::endl;
	std::cout << "Average riding time: " <<
			(rideSum / 1.0 * passengerCount) << std::endl;
}

int main()
{
	int passengerCount = 0;

	//initialize floors/passengers
	std::array<Floor, 101> stories;
	passengerCount = initializeFloors(&stories);

	//Initialize elevators
	std::array<Elevator, 4> elevators;
	buildElevators(10, &elevators);

	runSimulation(passengerCount, &elevators, &stories);

	//Run 5 second speed simulation
	passengerCount = initializeFloors(&stories);
	buildElevators(5, &elevators);

	runSimulation(passengerCount, &elevators, &stories);

	return 0;
} // end main



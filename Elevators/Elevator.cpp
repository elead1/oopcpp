/*
 * Elevator.cpp
 * Author: eric
 * Purpose: 
 */

#include "Elevator.h"


int Elevator::capacity = 8;

void Elevator::moveUp()
{
	if(this->currentFloor == 100)
	{
		throw std::logic_error("Already at top floor.");
	}
	if(this->state == ElevatorState::STOPPED)
	{
		this->timeSinceStateChange = 0;
	}
	this->currentFloor += 1.0 / this->speed;
	this->state = ElevatorState::MOVING_UP;
	std:: cout << "STATE AFTER UP: " << this->state << std::endl;
	std::cout << "UP" << std::endl;
}

void Elevator::moveDown()
{
	if(this->currentFloor == 1)
	{
		throw std::logic_error("Already at bottom floor.");
	}
	if(this->state == ElevatorState::STOPPED)
	{
		this->timeSinceStateChange = 0;
	}
	this->currentFloor -= 1.0 / this->speed;
	this->state = ElevatorState::MOVING_DOWN;
	std::cout << "DOWN" << std::endl;
}

void Elevator::slow()
{
	this->lastDirection = this->state;
	this->timeStopping = 0;
	this->state = ElevatorState::STOPPING;
}

void Elevator::stop()
{
	std::cout << "State set to STOPPED" << std::endl;
	if(this->timeStopping == 2)
	{
		this->state = ElevatorState::STOPPED;
	}
	else
	{
		this->timeStopping++;
	}
}

void Elevator::addPassenger(const Passenger &p)
{
	if(this->passengers.size() < Elevator::capacity)
	{
		this->passengers.push_back(p);
	}
	else
	{
		throw std::length_error("Elevator already full.");
	}
}


bool Elevator::havePassengerForCurrentFloor()
{
	for(Passenger &p : this->passengers)
	{
		if(p.getEndFloor() == this->currentFloor)
		{
			return true;
		}
	}
	return false;
}

std::vector<Passenger> Elevator::unloadPassengers()
{
	std::vector<Passenger> unloading;
	//Sort the passenger vector so all passengers disembarking on this
	//floor are listed first
	std::sort(this->passengers.begin(), this->passengers.end(),
			[this](const Passenger &a, const Passenger &b) -> bool
			{
				if(a.getEndFloor() == this->currentFloor)
				{
					return true;
				}
				else
				{
					return false;
				}
			});
	int disembarkCount = 0;
	for(Passenger &p : this->passengers)
	{
		if(p.getEndFloor() == this->currentFloor)
		{
			disembarkCount++;
		}
		else
		{
			break;
		}
	} // end for -- all disembarking passengers accounted for
	for(int i = 0; i < disembarkCount; i++)
	{
		unloading.push_back(this->passengers.front());
		this->passengers.erase(this->passengers.begin());
	} // end for -- all disembarking passengers are now in temp vector
	return unloading;
}

void Elevator::updatePassengers()
{
	for(Passenger &p : this->passengers)
	{
		p.increaseTimer();
	} // end for -- all passengers' timers increased
} // end updatePassengers

/*
int main()
{
	std::array<Elevator, 2> elevators;
	Elevator e(10, 25);
	Elevator e2(10, 50);
	elevators[0] = e;
	elevators[1] = e2;
	for(int i = 0; i < 2; i++)
	for(Elevator &e: elevators)
	{
		std::cout<<e.getCurrentFloor()<<std::endl;
		std::cout << e.getState() << std::endl;
		e.moveUp();
	}
	/*std::cout << e.getCurrentFloor() << std::endl;
	std::cout << e.getState() << std::endl;
	e.moveUp();
	std::cout << e.getCurrentFloor() << std::endl;
	std::cout << e.getState() << std::endl;
	e.moveDown();
	std::cout << e.getCurrentFloor() << std::endl;
	std::cout << e.getState() << std::endl;

	return 0;
}*/


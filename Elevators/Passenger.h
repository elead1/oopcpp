/*
 * Passenger.h
 * Author: eric
 * Purpose: 
 */
#ifndef Passenger_H
#define Passenger_H

enum PassengerState {WAITING, RIDING};

class Passenger
{
	public:
		Passenger()
			: Passenger(100)
		{}
		Passenger(int endFloor)
		{
			this->endFloor = endFloor;
			this->waitingTime = 0;
			this->ridingTime = 0;
			this->state = WAITING;
		}
		virtual ~Passenger() {}
		void increaseTimer();
		const inline int getWaitingTime()
		{
			return this->waitingTime;
		}
		const inline int getRidingTime()
		{
			return this->ridingTime;
		}
		inline void setRiding()
		{
			this->state = RIDING;
		}
		const inline PassengerState getState()
		{
			return this->state;
		}
	private:
		int endFloor;
		int ridingTime;
		int waitingTime;
		PassengerState state;
};

#endif

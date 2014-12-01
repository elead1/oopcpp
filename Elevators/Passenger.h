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
			: Passenger(1, 100)
		{}
		Passenger(int queueTime, int endFloor)
		{
			this->queueTime = queueTime;
			this->endFloor = endFloor;
			this->waitingTime = 0;
			this->ridingTime = 0;
			this->state = WAITING;
		}
		virtual ~Passenger() {}
		void increaseTimer();
		inline int getWaitingTime() const
		{
			return this->waitingTime;
		}
		inline int getRidingTime() const
		{
			return this->ridingTime;
		}
		inline int getQueueTime() const
		{
			return this->queueTime;
		}
		inline void setRiding()
		{
			this->state = RIDING;
		}
		inline PassengerState getState() const
		{
			return this->state;
		}
		inline int getEndFloor() const
		{
			return this->endFloor;
		}
	private:
		int endFloor;
		int ridingTime;
		int waitingTime;
		int queueTime;
		PassengerState state;
};

#endif

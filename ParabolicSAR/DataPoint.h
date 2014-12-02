/*
 * DataPoint.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulates all data fields for a financial datapoint.
 */
#ifndef DataPoint_H
#define DataPoint_H

#include <sstream>
#include <time.h>

class DataPoint
{
	public:
		DataPoint() { /*dummy constructor*/ };
		DataPoint(std::string timestamp, double openVal, double highVal,
				double lowVal, double closeVal, int volume);
		virtual ~DataPoint() { /*dummy destructor*/ };
		
		inline int getTimeStamp() const
		{
			return this->timestamp;
		}

		inline std::string getTimeStampString() const
		{
			return this->strTimeStamp;
		}

		inline double getCloseVal() const
		{
			return this->closeVal;
		}

		inline double getHighVal() const
		{
			return this->highVal;
		}

		inline double getLowVal() const
		{
			return this->lowVal;
		}

		inline double getOpenVal() const
		{
			return this->openVal;
		}

		inline int getVolume() const
		{
			return this->volume;
		}

		/**
		 * \fn static int timestampToUnixTime(const char*)
		 * Converts a timestamp to UNIX Epoch time.
		 * @param timestamp In format DD-Mon-YY
		 * @return a UNIX timestamp equal to the parameter.
		 */
		static int timestampToUnixTime(const char* timestamp);
		/**
		 * \fn static std::string unixTimeToTimeStamp(int)
		 * Converts a UNIX Epoch timestamp to a human readable string.
		 * @param unixtime UNIX Epoch time.
		 * @return a date string in DD-Mon-YY format.
		 */
		static std::string unixTimeToTimeStamp(int unixtime);
	private:
		std::string strTimeStamp;
		int timestamp, volume;
		double openVal, highVal, lowVal, closeVal;
};
#endif

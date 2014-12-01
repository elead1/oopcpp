/*
 * DataPoint.h
 * Author: eric
 * Purpose: 
 */

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

		static int timestampToUnixTime(const char* timestamp);

		static std::string unixTimeToTimeStamp(int unixtime);
	private:
		std::string strTimeStamp;
		int timestamp, volume;
		double openVal, highVal, lowVal, closeVal;
};

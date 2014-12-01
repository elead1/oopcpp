/*
 * PSAR.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */

#include "PSAR.h"

double PSAR::baseAccel = 0.02;
double PSAR::maxAccel = 0.2;
double PSAR::accelIncr = 0.02;

PSAR::PSAR(const char *filename, bool ascending)
{
	std::ifstream file(filename);
	if(!file.is_open())
	{
		throw std::runtime_error("Failed to open file.");
	}
	//Skip header line of CSV
	std::string line;
	std::vector<std::string> values;
	boost::char_separator<char> sep(",");
	//skip header line
	std::getline(file, line);

	while(std::getline(file, line))
	{
		boost::tokenizer<boost::char_separator<char> > tok(line, sep);
		for(boost::tokenizer<boost::char_separator<char> >::iterator beg =
				tok.begin(); beg != tok.end();
				++beg)
		{
			values.push_back(*beg);
		}
		std::string date = values[0];
		double open = atof(values[1].c_str());
		double high = atof(values[2].c_str());
		double low = atof(values[3].c_str());
		double close = atof(values[4].c_str());
		int volume = atoi(values[5].c_str());

		//We want data ordered with oldest first
		if(!ascending)
		{
			this->data.push_front(DataPoint(date, open, high,
					low, close, volume));
		}
		else
		{
			this->data.push_back(DataPoint(date, open, high,
								low, close, volume));
		}
		values.clear();
	}
	file.close();


	this->accelFactor = PSAR::baseAccel;
	updateTrending(this->data[0], this->data[1]);

	//On uptrend, SAR must be <= lowest of previous two datapoints.
	if(this->uptrending)
	{
		this->lastPSAR =
				std::min(this->data[0].getLowVal(), this->data[1].getLowVal());
		this->extremePoint =
				std::max(this->data[0].getHighVal(),this->data[1].getHighVal());
	}
	//On downtrend, >= highest of previous two datapoints.
	else
	{
		this->lastPSAR =
				std::max(this->data[0].getHighVal(),this->data[1].getHighVal());
		this->extremePoint =
				std::min(this->data[0].getLowVal(), this->data[1].getLowVal());
	}
}

void PSAR::calculatePSARs()
{
	std::deque<DataPoint>::iterator it = this->data.begin();
	//Step passed first two elements that we used for seeding values.
	it++;
	it++;
	for(; it != this->data.end(); ++it)
	{
		//Reset values if trend changed.
		if(updateTrending(*it, *(it - 1)))
		{
			this->accelFactor = PSAR::baseAccel;
			this->lastPSAR = this->extremePoint;
			if(this->uptrending)
			{
				this->extremePoint = std::max(it->getHighVal(),
						(it - 1)->getHighVal());
			}
			else
			{
				this->extremePoint = std::min(it->getLowVal(),
						(it - 1)->getLowVal());
			}
		} // end reset values

		if(this->uptrending)
		{
			//New EP => increase acceleration factor
			if(it->getHighVal() > this->extremePoint)
			{
				//accel factor maxes at 0.2
				this->accelFactor += (this->accelFactor < PSAR::maxAccel ?
						PSAR::accelIncr : 0.0);
				this->extremePoint = it->getHighVal();
			}
			this->lastPSAR = this->lastPSAR +
					this->accelFactor * (this->extremePoint - this->lastPSAR);
			//Maintain value restriction
			double prevMin =
					std::min((it - 1)->getLowVal(),
							(it - 2)->getLowVal());
			this->lastPSAR = (this->lastPSAR <= prevMin ?
					this->lastPSAR : prevMin);
		} // end uptrending calculation
		else
		{
			if(it->getLowVal() < this->extremePoint)
			{
				this->accelFactor += (this->accelFactor < PSAR::maxAccel ?
						PSAR::accelIncr : 0.0);
				this->extremePoint = it->getLowVal();
			}
			this->lastPSAR = this->lastPSAR -
					this->accelFactor * (this->extremePoint - this->lastPSAR);
			//Maintain value restriction
			double prevMax =
					std::max((it - 1)->getHighVal(),
							(it - 2)->getHighVal());
			this->lastPSAR = (this->lastPSAR > prevMax ?
					this->lastPSAR : prevMax);
		} // end downtrending calculation

		//Store PSAR value for current time period
		this->psarMap.insert(
				std::pair<int, double>(it->getTimeStamp(), this->lastPSAR));
	} // end calculation loop
}

double PSAR::getPSARAt(int unixtime)
{
	double psar = this->psarMap[unixtime];
	return psar;
}

std::vector<std::pair<int, double> >PSAR::getPSARSeries() const
{
	std::vector<std::pair<int, double> > psarVals(this->psarMap.size());
	std::pair<int, double> kv_pair;
	int i = 0;
	BOOST_FOREACH(kv_pair, this->psarMap)
	{
		psarVals[i] = kv_pair;
		i++;
	}
	return psarVals;
}

std::vector<std::pair<int, double> >PSAR::getPSARSeriesFrom(int unixtime)
{
	std::vector<std::pair<int, double> > psarVals;
	std::map<int, double>::iterator it = this->psarMap.find(unixtime);

	for(; it != this->psarMap.end(); ++it)
	{
		psarVals.push_back(*it);
	}
	return psarVals;
}

/**
 * \fn bool updateTrending(DataPoint, DataPoint)
 * Determines the current trend and whether the trend changed.
 * @param currentPoint the current DataPoint
 * @param previousPoint the previous DataPoint to compare against
 * @return true if the new trend is different from the old trend
 */
bool PSAR::updateTrending(DataPoint currentPoint, DataPoint previousPoint)
{
	bool trendChanged = false;
	//cut some corners to detect up/downtrend. Generally
	//an uptrend is defined when both highs and lows are  higher in
	//subsequent days (vice versa for downtrends).
	if((currentPoint.getHighVal() <= previousPoint.getHighVal()) &&
			(currentPoint.getLowVal() <= previousPoint.getLowVal()))
	{
		if(!this->uptrending)
		{
			trendChanged = true;
		}
		this->uptrending = true;
	}
	else if((currentPoint.getHighVal() > previousPoint.getHighVal()) &&
			(currentPoint.getLowVal() > previousPoint.getLowVal()))
	{
		if(this->uptrending)
		{
			trendChanged = true;
		}
		this->uptrending = false;
	}
	return trendChanged;
}

int main()
{
	std::string fname("testfile.csv");
	try{
		PSAR testPSAR(fname.c_str(), false);

		testPSAR.calculatePSARs();
		std::vector<std::pair<int, double> >myPSARS = testPSAR.getPSARSeries();
		//std::cout << testPSAR.getPSARAt(DataPoint::timestampToUnixTime("20-Nov-14"));
		for(std::pair<int, double> d : myPSARS)
		{
			std::cout << DataPoint::unixTimeToTimeStamp(d.first) <<
					":" << d.second << std::endl;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}


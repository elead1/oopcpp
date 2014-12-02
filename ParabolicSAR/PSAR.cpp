/*
 * PSAR.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulates financial data and allows for calculation of
 * PSAR values for each datapoint.
 */

#include "PSAR.h"

double PSAR::baseAccel = 0.02;
double PSAR::maxAccel = 0.2;
double PSAR::accelIncr = 0.02;

/**
 * \fn PSAR(const char*, bool)
 * Initializes a PSAR calculator using the data in the file
 * referred to by the given filename. If ascending is false, it is
 * assumed that the data is listed in the file with the newest data
 * first.
 * @param filename
 * @param ascending
 * @throws Exception if the given filename is unable to be opened.
 */
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
/**
 * \fn void calculatePSARs(void)
 * Calculates the PSAR values for the data stored in this. PSARs
 * are keyed using the UNIX timestamp equivalent to the date of the
 * financial datapoint.
 */
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
/**
 * \fn double getPSARAt(int)
 * Returns the PSAR value calculated for the date closest to the given
 * timestamp.
 * @param unixtimestamp
 * @return The PSAR value
 */
double PSAR::getPSARAt(int unixtime)
{
	int closestTime = this->closestKeyTo(unixtime);
	double psar = this->psarMap[closestTime];
	return psar;
}
/**
 * \fn std::vector<std::pair<int, double>>getPSARSeries() const
 * Returns a container of all timestamp-PSAR pairs with the lvalue =
 * timestamp.
 * @return A vector of timestamp-PSAR pairs.
 */
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
/**
 * \fn std::vector<std::pair<int, double>>getPSARSeriesUntil(int unixtimestamp)
 * Returns a container of all timestamp-PSAR pairs up until the given
 * UNIX timestamp.
 * @param unixtimestamp
 * @return A vector of timestamp-PSAR pairs.
 */
std::vector<std::pair<int, double> >PSAR::getPSARSeriesUntil(int unixtime)
{
	std::vector<std::pair<int, double> > psarVals;
	std::map<int, double>::iterator beg_it = this->psarMap.begin();
	std::map<int, double>::iterator end_it = this->psarMap.find(unixtime);

	for(;	beg_it != end_it; ++beg_it)
	{
		psarVals.push_back(*beg_it);
	}
	return psarVals;
}
/**
 * \fn std::vector<std::pair<int, double>>getPSARSeriesUntil(const char* tstamp)
 * Returns a container of all timestamp-PSAR pairs up until the given
 * timestamp.
 * @param tstamp a date given in DD-Mon-YY format.
 * @return A vector of timestamp-PSAR pairs.
 */
std::vector<std::pair<int, double> >PSAR::getPSARSeriesUntil(const char* tstamp)
{
	int t = this->closestKeyTo(DataPoint::timestampToUnixTime(tstamp));
	return this->getPSARSeriesUntil(t);
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

/**
 * \fn int closestKeyTo(int)
 * Determines the key with the value closest to but less than the parameter.
 * @param unixtime the UNIX timestamp to find a key less than
 * @return the existing key value just less than the parameter
 */
int PSAR::closestKeyTo(int unixtime)
{
	int closestTime = -1;
	std::map<int, double>::iterator beg_it = this->psarMap.begin();

	for(; beg_it != this->psarMap.end(); ++beg_it)
	{
		if(beg_it->first <= unixtime)
		{
			closestTime = beg_it->first;
		}
		else
		{
			break;
		}
	}
	return closestTime;
}
/*
int main()
{
	std::string fname("/home/eric/workspace/oopcpp/ParabolicSAR/data/asps.csv");
	try{
		PSAR testPSAR(fname.c_str(), false);

		testPSAR.calculatePSARs();
		std::vector<std::pair<int, double> >myPSARS = testPSAR.getPSARSeriesUntil("1-Jun-13");
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
*/

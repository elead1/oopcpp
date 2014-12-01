/*
 * PSAR.h
 * Author: Eric Leadbetter
 * Purpose: 
 */
#include <fstream>
#include <exception>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include "DataPoint.h"

class PSAR
{
	public:
		PSAR() { /* dummy constructor */ }
		PSAR(const char *filename, bool ascending);
		virtual ~PSAR() { /* dummy destructor */ };
		void calculatePSARs();
		double getPSARAt(int unixtimestamp);
		std::vector<std::pair<int, double> >getPSARSeries() const;
		std::vector<std::pair<int, double> >getPSARSeriesFrom(int unixtimestamp);
	private:
		/**
		 * \fn bool updateTrending(DataPoint, DataPoint)
		 * Determines the current trend and whether the trend changed.
		 * @param currentPoint the current DataPoint
		 * @param previousPoint the previous DataPoint to compare against
		 * @return true if the new trend is different from the old trend
		 */
		bool updateTrending(DataPoint currentPoint,
				DataPoint previousPoint);
		std::deque<DataPoint> data;
		std::map<int, double> psarMap;
		double extremePoint;
		bool uptrending;
		double accelFactor;
		double lastPSAR;
		static double baseAccel;
		static double maxAccel;
		static double accelIncr;
};


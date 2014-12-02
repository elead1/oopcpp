/*
 * PSAR.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulates financial data and allows for calculation of
 * PSAR values for each datapoint.
 */
#ifndef PSAR_H
#define PSAR_H

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
		PSAR(const char *filename, bool ascending);
		virtual ~PSAR() { /* dummy destructor */ };
		/**
		 * \fn void calculatePSARs(void)
		 * Calculates the PSAR values for the data stored in this. PSARs
		 * are keyed using the UNIX timestamp equivalent to the date of the
		 * financial datapoint.
		 */
		void calculatePSARs();
		/**
		 * \fn double getPSARAt(int)
		 * Returns the PSAR value calculated for the date closest to the given
		 * timestamp.
		 * @param unixtimestamp
		 * @return The PSAR value
		 */
		double getPSARAt(int unixtimestamp);
		/**
		 * \fn std::vector<std::pair<int, double>>getPSARSeries() const
		 * Returns a container of all timestamp-PSAR pairs with the lvalue =
		 * timestamp.
		 * @return A vector of timestamp-PSAR pairs.
		 */
		std::vector<std::pair<int, double> >getPSARSeries() const;
		/**
		 * \fn std::vector<std::pair<int, double>>getPSARSeriesUntil(int unixtimestamp)
		 * Returns a container of all timestamp-PSAR pairs up until the given
		 * UNIX timestamp.
		 * @param unixtimestamp
		 * @return A vector of timestamp-PSAR pairs.
		 */
		std::vector<std::pair<int, double> >getPSARSeriesUntil(int unixtimestamp);
		/**
		 * \fn std::vector<std::pair<int, double>>getPSARSeriesUntil(const char* tstamp)
		 * Returns a container of all timestamp-PSAR pairs up until the given
		 * timestamp.
		 * @param tstamp a date given in DD-Mon-YY format.
		 * @return A vector of timestamp-PSAR pairs.
		 */
		std::vector<std::pair<int, double> >getPSARSeriesUntil(const char* tstamp);
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
		/**
		 * \fn int closestKeyTo(int)
		 * Determines the key with the value closest to but less than the parameter.
		 * @param unixtime the UNIX timestamp to find a key less than
		 * @return the existing key value just less than the parameter
		 */
		int closestKeyTo(int unixtime);
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

#endif

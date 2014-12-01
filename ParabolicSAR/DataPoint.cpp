/*
 * DataPoint.cpp
 * Author: eric
 * Purpose: 
 */
#include <iostream>
#include "DataPoint.h"

DataPoint::DataPoint(std::string timestamp, double openVal, double highVal,
		double lowVal, double closeVal, int volume)
{
	this->timestamp = DataPoint::timestampToUnixTime(timestamp.c_str());
	this->strTimeStamp = timestamp;
	this->openVal = openVal;
	this->highVal = highVal;
	this->lowVal = lowVal;
	this->closeVal = closeVal;
	this->volume = volume;
}

/**
 * \fn Parses the provided string timestamp in format DD-Mon-YY into
 * a UNIX Epoch timestamp.
 * @param timestamp the string to be converted
 * @return an integer representing the number of seconds between the UNIX
 * Epoch (Jan 1 1970) and the given date timestamp.
 */
int DataPoint::timestampToUnixTime(const char* timestamp)
{
	// parse time; using C-style because Boost documentation sucks
	struct tm *time_struct = (struct tm*)calloc(1, sizeof(struct tm));
	strptime(timestamp, "%d-%b-%y", time_struct);
	int ptime = (int)mktime(time_struct);
	free(time_struct);

	return ptime;
}

std::string DataPoint::unixTimeToTimeStamp(int unixtime)
{
	time_t t = (time_t)unixtime;
	struct tm* tminfo = localtime(&t);
	std::stringstream ss("");
	ss << tminfo->tm_mday << "-" << (tminfo->tm_mon + 1) << "-" <<
			(tminfo->tm_year + 1900);
	return ss.str();
}

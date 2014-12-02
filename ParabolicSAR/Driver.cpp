/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Class: 605.404 OOP w/ C++
 * Purpose: Calculates and displays the PSAR values for various
 * financial symbols given their histories, calculated up to June 1, 2013.
 */
#include <array>
#include <sstream>
#include "PSAR.h"

int main()
{
	std::string filedir = "/home/eric/workspace/oopcpp/ParabolicSAR/data/";
	std::array<std::string, 10> filenames = {"asps.csv", "azo.csv",
			"cnp.csv", "cost.csv", "cvs.csv", "dbp.csv", "dgl.csv", "jjp.csv",
			"orly.csv",	"phys.csv"};

	for(std::string symbol : filenames)
	{
		std::stringstream ss("");
		ss << filedir << symbol;
		std::cout << "PSAR for " << symbol << ":" << std::endl;

		PSAR psar(ss.str().c_str(), false);
		psar.calculatePSARs();

		/*std::vector<std::pair<int, double> >myPSARS =
				psar.getPSARSeriesUntil("1-Jun-13");
		for(std::pair<int, double> d : myPSARS)
		{
			std::cout << DataPoint::unixTimeToTimeStamp(d.first) <<
					":" << d.second << std::endl;
		}*/
		std::cout <<
				psar.getPSARAt(DataPoint::timestampToUnixTime("1-Jun-13")) <<
				std::endl;
	}
}

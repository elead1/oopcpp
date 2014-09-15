/*
 * Statistical.h
 * Author: Eric Leadbetter
 * Purpose: Tracks student values and provides statistical data on them.
 */

class Statistical
{
	private:
		int valueSum = 0; // Keeps running sum of values entered.
		int squareSum = 0; // Keeps running sum of values squared for stdev.
		int numEntries = 0; // Keeps running count of values entered.

	public:
		double AVG() const;
		double STD() const;
		void addValue(int value);
}; //end class Statistical

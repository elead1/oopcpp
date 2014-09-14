/*
 * Statistical.h
 * Author: Eric Leadbetter
 * Purpose: Tracks student grades and provides statistical data on them.
 */

class Statistical
{
	private:
		int gradeSum = 0; // Keeps running sum of grades entered.
		int numEntries = 0; // Keeps running count of grades entered.

	public:
		double AVG() const;
		double STD() const;
		void addGrade(int grade);
}; //end class Statistical

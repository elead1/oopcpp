/*
 * Statistical.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */
#include <cmath>
#include "Statistical.h"

/*
 * addValue( int value )
 * Purpose: Add a value to the stat book and increment
 * the number of values counted.
 * Input: value is the value to be added to the stat book.
 * Postcondition: the stat book will include the value,
 * subsequent stat requests will use the value.
 */
void Statistical::addValue(int value)
{
	valueSum += value;
	squareSum += value * value;
	numEntries++; // Increment number of grades entered.
} //end addGrade(grade)

/*
 * AVG( void )
 * Purpose: Returns the average of the grades in the stat book.
 */
double Statistical::AVG() const
{
	//Ensure some values have been entered
	if(numEntries <= 0)
	{
		return 0;
	}

	double doubleSum = static_cast<double>(valueSum); // Cast gradeSum to double
	return doubleSum / numEntries;
} //end AVG()

/*
 * STD( void )
 * Purpose: Returns the standard deviation
 * of the grades in the stat book. uses the formula:
 * stdev = sqrt((Sum(value_i^2) - (Sum(value_i) * Sum(value_i) / N)) / (N - 1))
 */
double Statistical::STD() const
{
	//Cast both key values to double for arithmetic.
	double doubleSum = static_cast<double>(valueSum);
	double doubleSquared = static_cast<double>(squareSum);

	//Ensure some sample has been entered/avoid divide by 0
	if(numEntries - 1 <= 0)
	{
		return 0;
	}

	//Calculate the second term of the numerator of the formula
	double innerTerm = doubleSum * doubleSum / numEntries;
	//Calculate the difference that makes up the numerator
	double numerator = doubleSquared - innerTerm;
	//Calculate the sample standard deviation.
	double stdev = std::sqrt(numerator / (numEntries - 1));

	return stdev;
} //end STD()

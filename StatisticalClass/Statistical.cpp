/*
 * Statistical.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */
#include <cmath>
#include "Statistical.h"

/*
 * addGrade( int grade )
 * Purpose: Add a grade to the stat book and increment
 * the number of grades counted.
 * Input: grade is the grade to be added to the stat book.
 * Precondition: grade must be a nonnegative number
 * Postcondition: the stat book will include the grade value,
 * subsequent stat requests will use the grade value.
 */
void Statistical::addGrade(int grade)
{
	//Verify that the input value is nonnegative.
	if(grade >= 0)
	{
		gradeSum += grade;
		squareSum += grade * grade;
		numEntries++; // Increment number of grades entered.
	}
} //end addGrade(grade)

/*
 * AVG( void )
 * Purpose: Returns the average of the grades in the stat book.
 */
double Statistical::AVG() const
{
	double doubleSum = static_cast<double>(gradeSum); // Cast gradeSum to double
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
	double doubleSum = static_cast<double>(gradeSum);
	double doubleSquared = static_cast<double>(squareSum);

	//Calculate the second term of the numerator of the formula
	double innerTerm = doubleSum * doubleSum / numEntries;
	//Calculate the difference that makes up the numerator
	double numerator = doubleSquared - innerTerm;
	//Calculate the sample standard deviation.
	double stdev = std::sqrt(numerator / (numEntries - 1));

	return stdev;
} //end STD()

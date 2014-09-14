/*
 * Statistical.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */

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
 * of the grades in the stat book.
 */
double Statistical::STD() const
{
	return 0.0;
} //end STD()

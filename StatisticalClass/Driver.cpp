/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Purpose: Receives integer grades from the user until
 * a sentinel (-1) is input. Then utilizes the Statistical class
 * to calculate the average and standard deviation; those values
 * are then printed for the user.
 */

#include <iostream>
#include "Statistical.h"

/*
 * main()
 * Input: (from standard input) an arbitrary number of integers
 */
int main()
{
	Statistical data; // Instantiate a Statistical object for calculations.
	int input; // Holder for user input
	do
	{
		std::cout << "Enter test grade: " << std::endl;
		std::cin >> input;
		data.addGrade(input);
	}while(input != -1); // end do-while

	std::cout << "The average is: " << data.AVG() << std::endl;
	std::cout << "The standard deviation is: " << data.STD() << std::endl;
} //end main()





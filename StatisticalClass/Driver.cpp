/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Date: September 13th, 2014
 * Class: 605.401 Programming in C++, Hal Pierson and Doug Ferguson
 * Purpose: Receives integers from the user until
 * a sentinel (-999) is input. Then utilizes the Statistical class
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
	const int SENTINEL = -999; //Define sentinel value for input control.
	Statistical data; // Instantiate a Statistical object for calculations.
	int input; // Holder for user input

	do
	{
		std::cout << "Enter test grade (-999 to quit): " << std::endl;
		std::cin >> input;

		//Avoid adding sentinel value to sample
		if(std::cin && input != SENTINEL)
		{
			data.addValue(input);
		}
		//If the input was invalid, clear the error and the buffer
		else if(!std::cin)
		{
			std::cin.clear();
			std::cin.ignore();
		}
	}while(input != SENTINEL); // end do-while

	std::cout << "The average is: " << data.AVG() << std::endl;
	std::cout << "The standard deviation is: " << data.STD() << std::endl;
} //end main()





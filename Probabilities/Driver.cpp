/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Class: 605.404 OOP with C++, Hal Pierson and Doug Ferguson
 * Module #6: Probability
 * Purpose: Make use of the Probability class to illustrate its
 * functionality.
 */
#include <iostream>
#include "Probability.h"

int main()
{
	// Assignment from double.
	Probability p = 0.2;
	Probability q = 0.1;

	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;

	std::cout << "Not p: " << ~p << std::endl << std::endl;

	std::cout << "p And q: " << (p & q) << std::endl;

	std::cout << "0.5 and p: " << (0.5 & p) << std::endl << std::endl;

	std::cout << "p Or q: " << (p | q) << std::endl;

	std::cout << "0.5 or p: " << (0.5 | p) << std::endl << std::endl;

	std::cout << "p xor q: " << (p ^ q) << std::endl << std::endl;

	std::cout << "p but not q: " <<  (p - q).getValue() << std::endl
			<< std::endl;

	try
	{
		std::cout << "Trying to assign 1.5 to a Probability." << std::endl;
		Probability r = 1.5;
	}
	catch(std::exception& except)
	{
		std::cout << "Exception: " << except.what() << std::endl;
	}
}


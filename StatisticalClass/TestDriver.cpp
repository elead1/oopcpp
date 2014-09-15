/*
 * TestDriver.cpp
 * Author: Eric Leadbetter
 * Date: September 13th, 2014
 * Class: 605.401 Programming in C++, Hal Pierson and Doug Ferguson
 * Purpose: To evaluate the Statistical class to verify that it performs as expected.
 * Input: None, all parameters to the Statistical objects are generated programmatically.
 * Output: Prints to standard out the average and standard deviations for the various data
 * sets, and whether they match the expected output taken from the vetted source WolframAlpha.
 */

#include <iostream>
#include "Statistical.h"

int main()
{
	//Define variables for use in various test cases.
	//1-5 make up the first data set.
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6;
	int num7;

	//Define the various Statistical objects for testing.
	Statistical stat1;
	Statistical stat2;
	Statistical stat3;
	Statistical stat4;
	Statistical stat5;
	Statistical stat6;

	std::cout << "First data set: \n\t" << num1 << "\n\t" << num2 << "\n\t" << num3 << "\n\t"
			<< num4 << "\n\t" << num5 << std::endl;
	std::cout << "Wolfram Average: 3" << std::endl;
	std::cout << "Wolfram Standard Deviation: 1.5811" << std::endl;
	//Add data set #1 to stat1
	stat1.addValue(num1);
	stat1.addValue(num2);
	stat1.addValue(num3);
	stat1.addValue(num4);
	stat1.addValue(num5);
	std::cout << "Statistical class average: " << stat1.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat1.STD() << std::endl;
	std::cout << "=====================" << std::endl;

	//Exercise ability to operate with negative values.
	num1 = -2;
	num2 = -1;
	num3 = 0;
	num4 = 1;
	num5 = 2;
	std::cout << "Second data set (working with negatives): \n\t" << num1 << "\n\t" << num2
			<< "\n\t" << num3 << "\n\t" << num4 << "\n\t" << num5 << std::endl;
	std::cout << "Wolfram Average: 0" << std::endl;
	std::cout << "Wolfram Standard Deviation: 1.5811" << std::endl;
	//Add data set #1 to stat2
	stat2.addValue(num1);
	stat2.addValue(num2);
	stat2.addValue(num3);
	stat2.addValue(num4);
	stat2.addValue(num5);
	std::cout << "Statistical class average: " << stat2.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat2.STD() << std::endl;
	std::cout << "=====================" << std::endl;

	//Exercise ability to use fewer than 5 values.
	num1 = 70;
	num2 = 80;
	num3 = 90;
	std::cout << "Third data set (fewer than 5 values): \n\t" << num1 << "\n\t" << num2
			<< "\n\t" << num3 << std::endl;
	std::cout << "Wolfram Average: 80" << std::endl;
	std::cout << "Wolfram Standard Deviation: 10" << std::endl;
	//Add data set #1 to stat3
	stat3.addValue(num1);
	stat3.addValue(num2);
	stat3.addValue(num3);
	std::cout << "Statistical class average: " << stat3.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat3.STD() << std::endl;
	std::cout << "=====================" << std::endl;

	//Exercise ability to use more than 5 values.
	num1 = 1;
	num2 = 2;
	num3 = 3;
	num4 = 4;
	num5 = 5;
	num6 = 6;
	num7 = 7;
	std::cout << "Fourth data set (greater than 5 values): \n\t" << num1 << "\n\t" << num2
			<< "\n\t" << num3 << "\n\t" << num4 << "\n\t" << num5 << "\n\t" << num6
			<< "\n\t" << num7 << std::endl;
	std::cout << "Wolfram Average: 4" << std::endl;
	std::cout << "Wolfram Standard Deviation: 2.1602" << std::endl;
	//Add data set #1 to stat4
	stat4.addValue(num1);
	stat4.addValue(num2);
	stat4.addValue(num3);
	stat4.addValue(num4);
	stat4.addValue(num5);
	stat4.addValue(num6);
	stat4.addValue(num7);
	std::cout << "Statistical class average: " << stat4.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat4.STD() << std::endl;
	std::cout << "=====================" << std::endl;

	//Illustrate that sentinel value is factor of driver, not class.
	num7 = -999;
	std::cout << "Fifth data set (Driver's sentinel is not tied to Statistical class): \n\t"
			<< num1 << "\n\t" << num2 << "\n\t" << num3 << "\n\t" << num4 << "\n\t"
			<< num5	<< "\n\t" << num6 << "\n\t" << num7 << std::endl;
	std::cout << "Wolfram Average: -139.71" << std::endl;
	std::cout << "Wolfram Standard Deviation: 378.91" << std::endl;
	//Add data set #1 to stat4
	stat5.addValue(num1);
	stat5.addValue(num2);
	stat5.addValue(num3);
	stat5.addValue(num4);
	stat5.addValue(num5);
	stat5.addValue(num6);
	stat5.addValue(num7);
	std::cout << "Statistical class average: " << stat5.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat5.STD() << std::endl;
	std::cout << "=====================" << std::endl;

	//Exhibit behavior with 0 values.
	std::cout << "Sixth data set is empty." << std::endl;
	std::cout << "Statistical class average: " << stat6.AVG() << std::endl;
	std::cout << "Statistical class standard deviation: " << stat6.STD() << std::endl;
} //end main()





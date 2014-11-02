/*
 * Driver.cpp
 * Author: eric
 * Purpose: 
 */

#include <iostream>
#include "Variable.h"
#include "Constant.h"

int main()
{
	Variable x("X");
	Variable::setVariableValue("X", 3.0);
	std::cout << x << "=" << x.getValue() << std::endl;
	Variable y("Y");
	Variable::setVariableValue("Y", 5.0);
	std::cout << y << "=" << y.getValue() << std::endl;
	Constant a(0.5);
	std::cout << "a=" << a << std::endl;
	std::cout << "X*Y: " << x * y << std::endl;
	std::cout << "X+Y: " << x + y << std::endl;
	std::cout << "X-Y: " << x - y << std::endl;
	std::cout << "X/Y: " << x / y << std::endl;
	std::cout << "X%Y: " << x % y << std::endl;
	std::cout << "X^Y: " << (x ^ y) << std::endl;

	std::cout << "X*0.5: " << x * a << std::endl;
	std::cout << "X+0.5: " << x + a << std::endl;
	std::cout << "X-0.5: " << x - a << std::endl;
	try
	{
		std::cout << "X/0.5: " << x / a << std::endl;
		std::cout << "X%0.5: " << x % a << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "X^0.5: " << (x ^ a) << std::endl;
	return 0;
}

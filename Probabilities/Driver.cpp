/*
 * Driver.cpp
 * Author: eric
 * Purpose: 
 */
#include <iostream>
#include "Probability.h"

int main()
{
	Probability p = 0.0;
	Probability q = 1.0;

	std::cout << "p = " << p.getValue() << std::endl;
	std::cout << "q = " << q.getValue() << std::endl;

	std::cout << "Not p: " << (~p).getValue() << std::endl;

	std::cout << "p And q: " << (p & q).getValue() << std::endl;

	std::cout << "p Or q: " << (p | q).getValue() << std::endl;

	std::cout << "p xor q: " << (p ^ q).getValue() << std::endl;
	std::cout << "not p xor q: " << ((~p) ^ q).getValue() << std::endl;
}


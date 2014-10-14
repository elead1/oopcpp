/*
 * Driver.cpp
 * Author: eric
 * Purpose: 
 */
#include <iostream>
#include "Probability.h"

int main()
{
	Probability p = 0.2;
	Probability q = 0.1;

	std::cout << "p = " << p.getValue() << std::endl;
	std::cout << "q = " << q.getValue() << std::endl;

	std::cout << "Not p: " << (~p).getValue() << std::endl;

	std::cout << "p And q: " << (p & q).getValue() << std::endl;

	std::cout << "p Or q: " << (p | q).getValue() << std::endl;

	std::cout << "p xor q: " << (p ^ q).getValue() << std::endl; // should be 0.74
	std::cout << "not p xor q: " << ((~p) ^ q).getValue() << std::endl;

	std::cout << "p and not q: " <<  (p - q).getValue() << std::endl;
}


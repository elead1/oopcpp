/*
 * Driver.cpp
 * Author: eric
 * Purpose: 
 */

#include <iostream>
#include "ExpressionTree.h"

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

	Tree tree = new Mul(new Add(new Sub(new Constant(-5), &x), &a), &y);
	Tree tree2 = new Pow(new Constant(-3.0), new Constant(3.0));
	Tree tree3 = new Mod(new Constant(5.0), new Constant(3.0));
	Tree tree4 = new Neg(new Constant(10.0));
	try
	{
		std::cout << tree->Evaluate() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << *tree << std::endl;
	std::cout << *tree2 << " = " << tree2->Evaluate() << std::endl;
	std::cout << *tree3 << " = " << tree3->Evaluate() << std::endl;
	std::cout << *tree4 << " = " << tree4->Evaluate() << std::endl;
	return 0;
}

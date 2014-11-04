/*
 * Driver.cpp
 * Author: Eric Leadbetter
 * Class: EN 605.404 OOP w/ C++, Profs Pierson and Ferguson
 * Purpose: To exercise the capabilities of the ExpressionTree library
 * of classes.
 */

#include <iostream>
//contains includes for all node types and the Node* to Tree typedef
#include "ExpressionTree.h"

int main()
{
	//Establish some Variable values.
	Variable::setVariableValue("X", 2.0);
	Variable::setVariableValue("Y", 3.0);
	Variable::setVariableValue("Z", 5.0);

	std::cout << "Variable values:" << std::endl;
	std::cout << "X = " << Variable::getVariableValue("X") << std::endl;
	std::cout << "Y = " << Variable::getVariableValue("Y") << std::endl;
	std::cout << "Z = " << Variable::getVariableValue("Z") << std::endl;

	//Establish a Constant node.
	Constant a(0.5);
	std::cout << "a=" << a << std::endl;

	//Construct the tree from the assignment example
	Tree tree = new Add(
			new Mul(new Constant(2.3), new Variable("X")),
			new Mul(new Variable("Y"),
					new Sub(new Variable("Z"), new Variable("X"))));
	//Construct a tree to illustrate exponentiation
	Tree tree2 = new Pow(new Constant(-3.0), new Constant(3.0));
	//Construct a tree to illustrate modulo
	Tree tree3 = new Mod(new Constant(5.0), new Constant(3.0));
	//Construct a tree to illustrate negation
	Tree tree4 = new Neg(new Constant(10.0));
	//Construct a tree to illustrate division
	Tree tree5 = new Div(new Variable("Y"), new Constant(2.0));
	//Construct a tree to illustrate division by 0 protection
	Tree tree6 = new Div(new Variable("X"), new Constant(0.0));

	//Display all trees and their evaluations
	std::cout << *tree << " = " << tree->Evaluate() << std::endl;
	std::cout << *tree2 << " = " << tree2->Evaluate() << std::endl;
	std::cout << *tree3 << " = " << tree3->Evaluate() << std::endl;
	std::cout << *tree4 << " = " << tree4->Evaluate() << std::endl;
	std::cout << *tree5 << " = " << tree5->Evaluate() << std::endl;

	try
	{
		std::cout << *tree6 << " = " << tree6->Evaluate() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

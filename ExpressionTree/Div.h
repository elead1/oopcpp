/*
 * Div.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for a Division
 * operator.
 */

#ifndef Div_H
#define Div_H

#include "OperatorNode.h"

class Div : public OperatorNode
{
	public:
		Div(Node *leftChild, Node *rightChild)
		{
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		/**
		 * virtual double Evaluate() const override final
		 * @return The value of leftChild divided by rightChild.
		 * Throws exception if division by 0 would occur.
		 */
		virtual double Evaluate() const override final
		{	double rvalue = this->rightChild->Evaluate();
			//Avoid division by 0.
			if(rvalue == 0.0)
			{
				throw std::invalid_argument("Error evaluating division: "
						"Divisor cannot be 0.");
			}
			return this->leftChild->Evaluate() / rvalue;
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " / "
						<< *(this->rightChild) << " )";
		}
};

#endif



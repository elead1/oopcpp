/*
 * Mod.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for a Modulo
 * operator.
 */

#ifndef Mod_H
#define Mod_H

#include "OperatorNode.h"

class Mod : public OperatorNode
{
	public:
		Mod(Node *leftChild, Node *rightChild)
		{
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		/**
		 * virtual double Evaluate() const override final
		 * @return the value of leftChild, rounded to nearest
		 * whole number, modulo rightChild rounded. Throws exception
		 * if rightChild rounded is 0.
		 */
		virtual double Evaluate() const override final
		{
			//Modulo requires integer parameters, so round
			//left and right expressions to nearest whole number.
			int lvalue = lround(this->leftChild->Evaluate());
			int rvalue = lround(this->rightChild->Evaluate());
			//Modulo relies on division, so ensure no division by 0.
			if(rvalue == 0)
			{
				throw std::invalid_argument("Error evaluating modulo: "
						"Divisor cannot be 0.");
			}
			return lvalue % rvalue;
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " % "
						<< *(this->rightChild) << " )";
		}

};

#endif




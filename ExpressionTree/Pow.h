/*
 * Pow.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for a Exponentiation
 * operator.
 */

#ifndef Pow_H
#define Pow_H

#include <cmath>
#include "OperatorNode.h"

class Pow : public OperatorNode
{
	public:
		Pow(Node *leftChild, Node *rightChild)
		{
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		virtual double Evaluate() const override final
		{
			return pow(this->leftChild->Evaluate(),
					this->rightChild->Evaluate());
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " ^ "
						<< *(this->rightChild) << " )";
		}

};

#endif




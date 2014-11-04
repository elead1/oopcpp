/*
 * Mul.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for a Multiplication
 * operator.
 */

#ifndef Mul_H
#define Mul_H

#include "OperatorNode.h"

class Mul : public OperatorNode
{
	public:
		Mul(Node *leftChild, Node *rightChild)
		{
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		virtual double Evaluate() const override final
		{
			return this->leftChild->Evaluate() * this->rightChild->Evaluate();
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " * "
						<< *(this->rightChild) << " )";
		}
};

#endif




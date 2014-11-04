/*
 * Add.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for an Add operator.
 */

#ifndef Add_H
#define Add_H

#include "OperatorNode.h"

class Add : public OperatorNode
{
	public:
		Add(Node *leftChild, Node *rightChild)
		{
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		virtual double Evaluate() const override final
		{
			return this->leftChild->Evaluate() + this->rightChild->Evaluate();
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " + "
						<< *(this->rightChild) << " )";
		}
};

#endif


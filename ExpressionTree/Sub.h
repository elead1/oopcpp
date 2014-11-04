/*
 * Sub.h
 * Author: eric
 * Purpose: 
 */

#ifndef Sub_H
#define Sub_H

#include "OperatorNode.h"

class Sub : public OperatorNode
{
	public:
		Sub(Node *leftChild, Node *rightChild)
		{
				this->leftChild = leftChild;
				this->rightChild = rightChild;
		}
		virtual double Evaluate() const override final
		{
			return this->leftChild->Evaluate() - this->rightChild->Evaluate();
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( " << *(this->leftChild) << " - "
									<< *(this->rightChild) << " )";
		}

	private:
		Node *leftChild;
		Node *rightChild;
};

#endif




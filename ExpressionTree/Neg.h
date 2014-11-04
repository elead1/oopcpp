/*
 * Neg.h
 * Author: eric
 * Purpose: 
 */

#ifndef Neg_H
#define Neg_H

#include "OperatorNode.h"
#include "Constant.h"

class Neg : public OperatorNode
{
	public:
		Neg(Node *rightChild)
		{
			this->leftChild = new Constant(-1.0);
			this->rightChild = rightChild;
		}
		virtual double Evaluate() const override final
		{
			return this->leftChild->Evaluate() * this->rightChild->Evaluate();
		}
		virtual void print(std::ostream &out) const override final
		{
			out << "( -" << *(this->rightChild) << " )";
		}

	private:
		Node *leftChild;
		Node *rightChild;
};

#endif




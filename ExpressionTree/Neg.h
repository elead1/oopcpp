/*
 * Neg.h
 * Author: Eric Leadbetter
 * Purpose: Define the Evaluate and print operations for a Negation
 * operator.
 */

#ifndef Neg_H
#define Neg_H

#include "OperatorNode.h"
#include "Constant.h"

class Neg : public OperatorNode
{
	public:
		/**
		 * \fn Neg(Node *rightChild)
		 * Neg is a unary operation that multiplies the parameter by -1.
		 * @param rightChild the expression to negate.
		 */
		Neg(Node *rightChild)
		{
			// For negation, left child is always -1.
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

};

#endif




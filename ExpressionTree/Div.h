/*
 * Div.h
 * Author: eric
 * Purpose: 
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
		virtual double Evaluate() const override final
		{	double rvalue = this->rightChild->Evaluate();
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

	private:
		Node *leftChild;
		Node *rightChild;
};

#endif



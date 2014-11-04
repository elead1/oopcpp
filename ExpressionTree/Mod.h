/*
 * Mod.h
 * Author: eric
 * Purpose: 
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
		virtual double Evaluate() const override final
		{
			int lvalue = lround(this->leftChild->Evaluate());
			int rvalue = lround(this->rightChild->Evaluate());
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

	private:
		Node *leftChild;
		Node *rightChild;
};

#endif




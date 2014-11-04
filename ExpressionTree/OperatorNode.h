/*
 * OperatorNode.h
 * Author: Eric Leadbetter
 * Purpose: Encapsulate the concept of a generic "operator".
 */

#ifndef OperatorNode_H
#define OperatorNode_H

#include "Node.h"

class OperatorNode : public Node
{
	public:
		virtual ~OperatorNode() { } //dummy destructor
		virtual double Evaluate() const = 0;
		virtual void print(std::ostream &out) const = 0;
	protected:
		Node* leftChild;
		Node* rightChild;
};

#endif


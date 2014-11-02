/*
 * OperatorNode.h
 * Author: Eric Leadbetter
 * Purpose: 
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
};

#endif


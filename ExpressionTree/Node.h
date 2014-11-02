/*
 * Node.h
 * Author: Eric Leadbetter
 * 605.404 OOP w/ C++, Profs Pierson & Ferguson
 * Defines an abstract Node class for construction of expression trees.
 */
#ifndef Node_H
#define Node_H

#include <iostream>
/**
 * \class Node
 */
class Node
{
	public:
		virtual ~Node() { };
		virtual void print(std::ostream& out) const = 0;
};

inline std::ostream &operator<<(std::ostream& out, const Node& n)
{
	n.print(out);
	return out;
}

#endif

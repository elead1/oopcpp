/*
 * OperandNode.h
 * Author: Eric Leadbetter
 * Purpose: An abstract ancestor for the value classes to be provided
 * to a mathematical operator.
 */
#ifndef OperandNode_H
#define OperandNode_H

#include <cmath>
#include <stdexcept>
#include "Node.h"

/**
 * \class OperandNode
 * \brief An abstract ancestor for the value classes to be provided
 * to a mathematical operator.
 */
class OperandNode : public Node
{
	public:
		virtual ~OperandNode() { }; // dummy destructor
		/**
		 * \fn virtual double Evaluate() const override;
		 * The evaluation of an operand node is just the value of that node.
		 * @return getValue()
		 */
		virtual double Evaluate() const override;
		/**
		 * \fn virtual double getValue( void ) const = 0;
		 * @return The double value of the node
		 */
		virtual double getValue( void ) const = 0;
		/**
		 * \fn virtual double operator+( const OperandNode &otherNode ) const
		 * Provides for addition between leaf nodes in an expression tree
		 * @param otherNode the node to add to this
		 * @return the result of the addition operation.
		 */
		virtual double operator+( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double operator-( const OperandNode &otherNode ) const
		 * Provides for subtraction between leaf nodes in an expression tree
		 * @param otherNode the node to subtract from this
		 * @return the result of the subtraction operation.
		 */
		virtual double operator-( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double operator*( const OperandNode &otherNode ) const
		 * Provides for multiplication between leaf nodes in an expression
		 * tree
		 * @param otherNode the node to multiply this by
		 * @return the result of the multiplication operation.
		 */
		virtual double operator*( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double operator/( const OperandNode &otherNode ) const
		 * Provides for division between leaf nodes in an expression tree
		 * @param otherNode the node to divide this by
		 * @return the result of the division operation.
		 */
		virtual double operator/( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double operator^( const OperandNode &otherNode ) const
		 * Provides for exponentiation between leaf nodes in an expression
		 * tree
		 * @param otherNode the node to raise this to the power of
		 * @return the result of the exponentiation operation.
		 */
		virtual double operator^( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double operator%( const OperandNode &otherNode ) const
		 * Provides for modulo between leaf nodes in an expression tree
		 * @param otherNode the node to modulo this with
		 * @return the result of the modulo operation.
		 */
		virtual int operator%( const OperandNode &otherNode ) const;
		/**
		 * \fn virtual double print( std::ostream &out ) const = 0;
		 * Helper function to avoid 'friend'ing the << operator.
		 */
		virtual void print(std::ostream &out) const = 0;
};


#endif


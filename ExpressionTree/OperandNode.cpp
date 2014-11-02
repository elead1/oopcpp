/*
 * OperandNode.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */

#include "OperandNode.h"

/**
 * \fn virtual double operator+( const OperandNode &otherNode ) const
 * Provides for addition between leaf nodes in an expression tree
 * @param otherNode the node to add to this
 * @return the result of the addition operation.
 */
double OperandNode::operator+(const OperandNode &otherNode) const
{
	return this->getValue() + otherNode.getValue();
} // end operator+
/**
 * \fn virtual double operator-( const OperandNode &otherNode ) const
 * Provides for subtraction between leaf nodes in an expression tree
 * @param otherNode the node to subtract from this
 * @return the result of the subtraction operation.
 */
double OperandNode::operator-(const OperandNode &otherNode) const
{
	return this->getValue() - otherNode.getValue();
} // end operator-

/**
 * \fn virtual double operator*( const OperandNode &otherNode ) const
 * Provides for multiplication between leaf nodes in an expression
 * tree
 * @param otherNode the node to multiply this by
 * @return the result of the multiplication operation.
 */
double OperandNode::operator*(const OperandNode &otherNode) const
{
	return this->getValue() * otherNode.getValue();
} // end operator*
/**
 * \fn virtual double operator/( const OperandNode &otherNode ) const
 * Provides for division between leaf nodes in an expression tree
 * @param otherNode the node to divide this by
 * @return the result of the division operation. Throws exception if
 * the divisor is 0.
 */
double OperandNode::operator/(const OperandNode &otherNode) const
{
	if(otherNode.getValue() == 0.0)
	{
		throw std::invalid_argument("Divisor cannot be 0.");
	}
	return this->getValue() / otherNode.getValue();
} // end operator/
/**
 * \fn virtual double operator%( const OperandNode &otherNode ) const
 * Provides for modulo between leaf nodes in an expression tree. Rounds
 * values to nearest integer.
 * @param otherNode the node to modulo this with
 * @return the result of the modulo operation. Throws an exception if
 * either operand is 0 after the integer conversion.
 */
int OperandNode::operator%(const OperandNode &otherNode) const
{
	int lvalue = lround(this->getValue());
	int rvalue = lround(otherNode.getValue());
	if(rvalue == 0)
	{
		throw std::invalid_argument("Rounded divisor cannot be 0.");
	}
	return lvalue % rvalue;
} // end operator%
/**
 * \fn virtual double operator^( const OperandNode &otherNode ) const
 * Provides for exponentiation between leaf nodes in an expression
 * tree
 * @param otherNode the node to raise this to the power of
 * @return the result of the exponentiation operation.
 */
double OperandNode::operator^(const OperandNode &otherNode) const
{
	return pow(this->getValue(), otherNode.getValue());
} // end operator^


/*
 * Constant.h
 * Author: Eric Leadbetter
 * Purpose: Represents a constant numeric value in an expression tree.
 */
#ifndef Constant_H
#define Constant_H

#include "OperandNode.h"


/**
 * \class Constant
 * \brief Represents a constant numeric value in an expression tree.
 */
class Constant : public OperandNode
{
	public:
		/**
		 * \fn Constant( double value )
		 * Initializes the value of this Constant to the parameter
		 * @param value the value to assign to this Constant.
		 */
		Constant( double value )
		{
			this->value = value;
		}

		virtual ~Constant() { }; // dummy destructor

		/**
		 * \fn virtual double getValue( void ) const override
		 * @return The value of this constant.
		 */
		virtual double getValue( void ) const override
		{
			return this->value;
		} // end getValue
		/**
		 * \fn virtual double print( std::ostream &out ) const = 0;
		 * Helper function to avoid 'friend'ing the << operator.
		 */
		virtual void print( std::ostream &out ) const override
		{
			out << this->value;
		}

	private:
		double value;
};

#endif

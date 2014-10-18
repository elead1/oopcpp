/*
 * Probability.h
 * Author: Eric Leadbetter
 * Class: 605.404 OOP with C++, Hal Pierson and Doug Ferguson
 * Module #6: Probability
 * Purpose: This class represents a probability and provides the necessary
 * operators to perform probability-related math.
 */
#ifndef Probability_H
#define Probability_H
#include <stdexcept>

/** \file Probability.h
 * \brief Defines the Probability class and overloaded operators
 * for use with it.
 */

/**
 * \brief Probability
 * Specifies operations to perform mathematical operations on probabilities.
 */
class Probability
{
	public:
		/**
		 * \fn Probability( void )
		 * Purpose: Creates a Probability of 0.
		 */
		Probability( void )
		{
			this->val = 0.0;
		} // end Probability()

		/**
		 * \fn Probability( const Probability &probability )
		 * Copy constructor.
		 * @param probability A Probability object to clone.
		 */
		Probability( const Probability &probability )
		{
			*this = probability;
		} // end Probability( Probability )

		/**
		 * \fn Probability( double probability )
		 * Primary/conversion constructor to turn a double into a
		 * Probability. Throws invalid_argument exception if probability < 0
		 * or probability > 1
		 * @param probability A double representing a probability
		 */
		Probability( double probability )
		{
			*this = probability;
		} // end Probability( double )

		/**
		 * \fn Probability &operator=( const Probability &probability )
		 * Allows creation of a new Probability from an existing probability
		 * using assignment.
		 * @param probability The probability to copy.
		 * @return The Probability object created from the parameter object.
		 */
		Probability &operator=( const Probability &probability )
		{
			this->val = probability.getValue();
			return *this;
		}
		/**
		 * \fn Probability &operator=( double probability )
		 * Allows creation of a Probability object using assignment.
		 * @param probability The double value the new Probability will have
		 * @return The Probability object created with the parameter
		 * probability value.
		 */
		Probability &operator=( double probability )
		{
			if((probability < 0.0) || (probability > 1.0))
			{
				throw std::invalid_argument("probability must "
						"be between 0 and 1");
			}
			this->val = probability;
			return *this;
		} // end operator=( double )


		/**
		 * \fn Probability &operator~( void ) const
		 * @return The probability of the event represented by this
		 * probability not occurring (the complement).
		 */
		Probability &operator~( void ) const
		{
			Probability *temp = new Probability;
			*temp = 1.0 - this->val;
			return *temp;
		} // end operator~()

		/**
		 * \fn double getValue( void )
		 * @return The value of this probability.
		 */
		double getValue( void ) const
		{
			return this->val;
		}
	private:
		double val;
};

/**
 * \fn std::ostream &operator<<( std::ostream &out,
 * 		const Probability &probability)
 * Enables Probabilities to be streamed to output.
 * @param out the ostream to stream probability to
 * @param probability the Probability whose value will be streamed to out
 * @return out in order to chain operations.
 */
std::ostream &operator<<( std::ostream &out, const Probability &probability)
{
	out << probability.getValue();
	return out;
}

/**
 * \fn Probability &operator&( const Probability &prob1,
 * 		const Probability &prob2 )
 * @param prob1 The first probability to and
 * @param prob2 The second probability to and with the first one
 * @return The probability of the event represented by prob1 and
 * the event represented by prob2 occurring.
 */
Probability &operator&( const Probability &prob1,
		const Probability &prob2 )
{
	Probability *temp = new Probability;
	*temp = prob1.getValue() * prob2.getValue();
	return *temp;
} // end operator&( Probability, Probability )

/**
 * \fn Probability &operator|( const Probability &prob1,
 * 		const Probability &prob2 )
 * @param prob1 The first probability to or
 * @param prob2 The second probability to or with the first one
 * @return The probability of the event represented by prob1
 * or the event represented by prob2 occurring.
 */
Probability &operator|( const Probability &prob1,
		const Probability &prob2 )
{
	Probability *temp = new Probability;
	*temp = prob1.getValue() + prob2.getValue()
			- (prob1 & prob2).getValue();
	return *temp;
} // end operator|( Probability )

/**
 * \fn Probability &operator^( const Probability &prob1,
 * 		const Probability &prob2 )
 * @param prob1 The first probability to be xor-ed
 * @param prob2 The probability to be xor-ed with the first one
 * @return The probability of the event represented by prob1
 * or the event represented by prob2 occurring, but not both.
 */
Probability &operator^( const Probability &prob1,
		const Probability &prob2 )
{
	Probability *temp = new Probability;
	*temp = (prob1.getValue() + prob2.getValue()
			- (2 * (prob1 & prob2).getValue()));
	return *temp;
} // end operator^( Probability )

/**
 * \fn Probability &operator-( const Probability &prob1,
 * 		const Probability &prob2 )
 * @param prob1 The probability of the event that does occur
 * @param prob2 The probability of the event that does not occur
 * @return The probability of the event represented by prob1 occurring
 *  but not the event represented by prob2.
 */
Probability &operator-( const Probability &prob1,
		const Probability &prob2 )
{
	Probability *temp = new Probability;
	*temp = prob1 & ~prob2;
	return *temp;
} // end operator-( Probability )
#endif

/*
 * Probability.h
 * Author: Eric Leadbetter
 * Purpose: This class represents a probability and provides the necessary
 * operators to perform probability-related math.
 */
#ifndef Probability_H
#define Probability_H
#include <iostream>
#include <stdexcept>

/**
 * \class Probability
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
		 * \fn Probability &operator=( const Probability &probability ) const
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
		 * \fn Probability &operator&( const Probability &probability ) const
		 * @param probability The probability to and with this one
		 * @return The probability of the event represented by this
		 * probability and the event represented by the parameter occurring.
		 */
		Probability &operator&( const Probability &probability ) const
		{
			Probability temp;
			temp = this->val * probability.getValue();
			return temp;
		} // end operator&( Probability)

		/**
		 * \fn Probability &operator~( void ) const
		 * @return The probability of the event represented by this
		 * probability not occurring (the complement).
		 */
		Probability &operator~( void ) const
		{
			Probability temp;
			temp = 1.0 - this->val;
			return temp;
		} // end operator~()

		/**
		 * \fn Probability &operator|( const Probability &probability ) const
		 * @param probability The probability to or with this one
		 * @return The probability of the event represented by this
		 * probability or the event represented by the parameter occurring.
		 */
		Probability &operator|( const Probability &probability ) const
		{
			Probability temp;
			temp = this->val + probability.getValue()
					- (*this & probability).getValue();
			return temp;
		} // end operator|( Probability )

		/**
		 * \fn Probability &operator^( const Probability &probability ) const
		 * @param probability The probability to exclusive-or with this one
		 * @return The probability of the event represented by this
		 * probability or the event represented by the parameter occurring,
		 * but not both.
		 */
		Probability &operator^( const Probability &probability ) const
		{
			Probability temp;
			temp = (this->val + probability.getValue()
					- (2 * (*this & probability).getValue()));
			//temp = Probability((1 - this->val) * probability.getValue()) | Probability(this->val * (1 - probability.getValue()));
			return temp;
		} // end operator^( Probability )

		/**
		 * \fn Probability &operator-( const Probability &probability ) const
		 * @param probability The probability to calculate exclusivity from
		 * @return The probability of the event represented by this
		 * probability occurring but not the event represented by the
		 * parameter.
		 */
		Probability &operator-( const Probability &probability ) const
		{
			Probability temp;
			temp = this->getValue() - (*this & probability).getValue();
			return temp;
		} // end operator-( Probability )

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

#endif


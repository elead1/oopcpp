/*
 * Variable.cpp
 * Author: Eric Leadbetter
 * Purpose: 
 */

#include "Variable.h"

std::map<std::string, double> Variable::symbolTable;

/**
 * \fn virtual double getValue( void ) const
 * @return The value stored in the symbol table for this variable's
 * symbol. Throws an exception if the symbol is not in the table.
 */
double Variable::getValue( void ) const
{
	return Variable::symbolTable.at(this->symbol);
} // end getValue

/**
 * \fn void Variable::setVariableValue(std::string symbol, double value)
 * \brief Sets the provided symbol's entry in the symbol table to value.
 * If the symbol doesn't exist in the table yet, it is inserted.
 * @param symbol the symbol to set
 * @param value the value to set the symbol to
 */
void Variable::setVariableValue(std::string symbol, double value)
{
	Variable::symbolTable[symbol] = value;
} // end setVariableValue

/**
 * \fn double Variable::getVariableValue(std::string symbol)
 * \brief Gets the value of the given symbol
 * @param symbol the symbol whose value is being retrieved
 * @return the value of the given symbol. Throws an exception if the symbol
 * does not exist in the table.
 */
double Variable::getVariableValue(std::string symbol)
{
	return Variable::symbolTable.at(symbol);
} // end getVariableValue

/**
 * \fn void Variable::print( std::ostream &out ) const
 * A utility function to avoid 'friend'ing the overloaded << operator.
 * @param out the ostream to write to.
 */
void Variable::print( std::ostream &out ) const
{
	out << this->symbol;
} // end print

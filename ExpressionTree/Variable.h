/*
 * Variable.h
 * Author: Eric Leadbetter
 * Purpose: Represents a variable value in an expression tree. Contains
 * a static symbol table to store variable values.
 */
#ifndef Variable_H
#define Variable_H

#include <map>
#include "OperandNode.h"

/**
 * \class Variable
 * \brief Represents a variable value in an expression tree. Contains
 * a static symbol table to store variable values.
 */
class Variable : public OperandNode
{
	public:
		/**
		 * \fn Variable( std::string symbol )
		 * Creates a Variable with the given symbol as it's representative
		 * in the symbol table. If the symbol is not yet in the table, it is
		 * inserted with a default value of 0.
		 * @param symbol the representative for the new Variable in the table
		 */
		Variable( std::string symbol )
		{
			this->symbol = symbol;
			//If symbol not yet in table, add it with default value of 0.
			if(Variable::symbolTable.find(this->symbol)
					== Variable::symbolTable.end())
			{
				Variable::symbolTable[this->symbol] = 0.0;
			}
		}
		virtual ~Variable() { }; // dummy destructor
		/**
		 * \fn virtual double getValue( void ) const
		 * @return The value stored in the symbol table for this variable's
		 * symbol. Throws an exception if the symbol is not in the table.
		 */
		virtual double getValue( void ) const override final;
		/**
		 * \fn void Variable::print( std::ostream &out ) const
		 * A utility function to avoid 'friend'ing the overloaded << operator.
		 * @param out the ostream to write to.
		 */
		virtual void print( std::ostream &out ) const override final;

		/**
		 * \fn void Variable::setVariableValue(std::string symbol, double value)
		 * \brief Sets the provided symbol's entry in the symbol table to value.
		 * If the symbol doesn't exist in the table yet, it is inserted.
		 * @param symbol the symbol to set
		 * @param value the value to set the symbol to
		 */
		static void setVariableValue(std::string symbol, double value);
		/**
		 * \fn double Variable::getVariableValue(std::string symbol)
		 * \brief Gets the value of the given symbol
		 * @param symbol the symbol whose value is being retrieved
		 * @return the value of the given symbol. Throws an exception if the symbol
		 * does not exist in the table.
		 */
		static double getVariableValue(std::string symbol);

	private:
		// the representative for this Variable in the symbol table
		std::string symbol;
		//the table holding all variable values.
		static std::map<std::string, double> symbolTable;

};

#endif

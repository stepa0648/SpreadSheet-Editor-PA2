/**
 * \file Math.h
 * \author severste
 *
   \brief This is the file where all mathematical functions are defined.
	 All mathematical functions and all functions related to evaluating mathematical expression in cells
	 Functions are documented in Math.cpp file
	*/

#ifndef MATH_H
#define MATH_H

//Evaluating Mathematical Expression============================================

#include <string>
#include <vector>
#include <exception>
#include <memory>

#include "CToken.h"
#include "CTable.h"

/**
   \class BracketsMissMatch
   \brief Class is used to be throw as an exception when brackets error happens
   the what() method returns error message
 */
class BracketsMissMatch : public std::exception {
public:
virtual const char * what() const noexcept {
								return "Brackets missmatch";
}
};

/**
   \class OperatorError
   \brief Class is used to be throw as an exception when operator error happens.
   Error could be for example operator at the end of expressin or binary operator with only one operand etc.

 */
class OperatorError : public std::exception {
public:
virtual const char * what() const noexcept {
								return "OperatorError";
}
};

/**

   \brief Checks if string is math expression and cut off the = sign from string
   @param val is the string which we want to test
   @return true if the expression starts with =
 */
bool isMathExprTrans(std::string & val);

/**

	\brief Checks if string is math expression. Same as isMathExprTrans but does not cut off the = sign
   @param val is the string which we want to test
   @return true if the expression starts with =
 */
bool isMathExpr(const std::string & val);

/**

	\brief Function findParents finds parents cell in string m_textVal in CCell and saves them to parent set
	@param string str, string where to find parent cells
	@param set<pair<int,int>> set, set where parent cells are saved
	@return bool, true if at least one parent was found
*/
bool findParents(const std::string & str, std::set<std::pair<int,int>> & set);

/**

	\brief Function findAncestors finds all ancestors of the cell and saves them to ancestors set.
	It is a recursive function that finds parents of parents etc.
	@param set<pair<int,int>>  ancestors, set where the ancestors are stored
	@param set<pair<int,int>> parents, set where parent cells are given to our function
	@return bool, true if at least one parent was found
*/
std::set<std::pair<int,int>> findAncestors(std::set<std::pair<int,int>> & ancestors,std::set<std::pair<int,int>> parents, const CTable & table);





/**

   \brief Converts string to double.
   If string is NaN throw an exception invalid_argument
   @param str is the string we want to convert
   @return double value of the string
 */
double stringToDouble( const std::string & str);

/**
   \brief Checks if string is an operator
   @param c is the string you want to check
   @return bool, true if string is an operator
 */
bool isOperator(const std::string& c);

/**
   \brief Checks if string is a funtion
   @param c is the string you want to check
   @return bool, true if string is a function
 */
bool isFunction(const std::string& c);

/**
   \brief Checks if the string is identificator of a cell in format [y;x]
   @param str is the string that we want to test
   @param y is the int where we will store the y value if the string is Cell
   @param x is the int where we will store the x value if the string is Cell
   @return bool, true if the format is right
 */
bool isCell(const std::string& str, int & y, int & x);

/**
   \brief Converts string mathematical expression to vector with separated tokens (still strings).
   This mathematical expression can include some cells from table, and count with values from them
   @param str is a string which you want to convert
   @param table is a table in which you are searching for the cells
   @return vector of strings and each string represents one Token
 */
std::vector<std::string> stringToVec( const std::string & str, const CTable & table );


/**
   \brief Returns the operator precedence, the higer value has higer precedence
   @param c is the operator whose precedence you want
   @return int the value of the operator precedence
 */
int operatorPrecedence(const std::string& c);


/**
   \brief Converts vector of tokens(strings) in infix notation to RPN (reverse polish notation) vector of CTokens using shunting yard algorithm.
   @param vec is the vector of string(tokens)
   @return vector of CToknes in RPN
 */
std::vector<std::shared_ptr<CToken> > infixToRPN(const std::vector<std::string> & vec);

/**
   \brief Evalutes vector of CTOkens in RPN and returns double value of that expression
   @param vec is vector of CTokens in RPN
   @return double value of evaluated vector
 */
double evaluateRPN(const std::vector<std::shared_ptr<CToken> > & vec);
/**
   \brief Evalutes string where is math expression
   @param res, double where the evaluated value will be stored
   @param str is string from cell, that will be evaluated
   @param table, where cell is stored
   @return bool, true if string was evaluated
 */
bool evaluateString(double & res, std::string & str, const CTable & table);
/**

   \brief Evalutes string from cell
   @param res, double where the evaluated value will be stored
   @param val is string from cell, that will be evaluated
   @param table, where cell is stored
   @return bool, true if string was evaluated
 */
bool evaluateCell(double & res, const std::string & val,const CTable & table);


#endif

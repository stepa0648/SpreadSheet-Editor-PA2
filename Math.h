//Evaluating Mathematical Expression============================================

#include <string>
#include <vector>
#include <exception>
#include <memory>

#include "CToken.h"
#include "CTable.h"

/**
  checks if string is math expression and cut off the = sign from string
  @param val is the string which we want to test
  @return true if the expression starts with =
*/
bool isMathExpr(std::string & val);

/**
  \class BracketsMissMatch
  \brief class for throwing exception when brackets error happens
  the what() method returns error message
*/
class BracketsMissMatch : public std::exception {
	public:
	virtual const char * what() const noexcept{
		return "Brackets missmatch";
	}
};

/**
  \class OperatorError
  \brief class for throwing exception when operator error happens
  error could be for example operator at the end of expressin or binary operator with only one operand etc.

*/
class OperatorError : public std::exception{
	public:
	virtual const char * what() const noexcept{
		return "OperatorError";
	}
};

/**
  converts string to double,
  if string is NaN throw an exception invalid_argument
	@param str is the string we want to convert
	@return double value of the string
*/
double stringToDouble( const std::string & str);

/**
  checks if string is an operator
	@param c is the string you want to check
  @return bool, true if string is an operator
*/
bool isOperator(const std::string& c);

/**
  checks if string is a funtion
	@param c is the string you want to check
  @return bool, true if string is a function
*/
bool isFunction(const std::string& c);

/**
  Checks if the string is identificator of a cell in format [y;x]
  @param str is the string that we want to test
  @param y is the double where we will store the y value if the string is Cell
  @param x is the double where we will store the x value if the string is Cell
  @return bool, true if the format is right
*/
bool isCell(const std::string& str, double & y, double & x);

/**
  converts string mathematical expression to vector with separated tokens (still strings)
	This mathematical expression can include some cells from table, and count with values from them
	@param str is a string which you want to convert
	@param table is a table in which you are searching for the cells
	@return vector of strings and each string represents one Token
*/
std::vector<std::string> stringToVec( const std::string & str, const CTable & table );


/**
	return the operator precedence, the higer value has higer precedence
	@param c is the operator whose precedence you want
	@return int the value of the operator precedence
*/
int operatorPrecedence(const std::string& c);


/**
  converts vector of tokens(strings) in infix notation to RPN (reverse polish notation) vector of CTokens using shunting yard algorithm
	@param vec is the vector of string(tokens)
	@return vector of CToknes in RPN
*/
std::vector<std::shared_ptr<CToken>> infixToRPN(const std::vector<std::string> & vec);

/**
  evalutes vector of CTOkens in RPN and returns double value of that expression
	@param vec is vector of CTokens in RPN
	@return double value of evaluated vector
*/
double evaluateRPN(const std::vector<std::shared_ptr<CToken>> & vec);

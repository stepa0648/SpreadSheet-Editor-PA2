/**
 * \file CToken.h
 * \author severste
* \brief This is the file where CToken, CNumber, COperator and CFunction classes are defined
 */

#ifndef CTOKEN_H
#define CTOKEN_H

#include <string>
#include <stack>





/**
  \class CToken
  \brief Derived classes are used as tokens in RPN(reverse polish notation)
  It is used also during transformation vector<string> infix notation intto RPN and evaluate the RPN
  It is an abstract class
*/
class CToken{
public:
  /**
    Constructor of class CToken
  */
  CToken(){}
  /**
    Destructor of class CToken
  */
  virtual ~CToken() {};
  /**
    This method returns true if token is a number
    @return bool, true if token is a number
  */
  virtual bool isNumber() const = 0;
  /**
  This method performs the operation according to what type the token is.
  */
  virtual void performOperation( std::stack<double> & stack ) = 0;
  /**
  This method returs double value of token if a token is a number
  @return double, if token is a CNumber returns its value, if token is not a number returns 0
  */
  virtual double getVal() const = 0;

};
//==============================================================================
/**
  \class CNumber
  \brief Class is used as a number in evaluating RPN (reverse polish notation)
*/
class CNumber: public CToken{
public:
  /**
    Constructor of class CNumber
    @param double val - represents the value of the number
  */
  CNumber( double val );
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;

private:
  double m_Val; /** double represantiton of CNumber*/
};
//==============================================================================
/**
\class CFunction
\brief Class is used as a function in evaluating RPN (reverse polish notation)
*/
class CFunction: public CToken{
  /**
  Constructor of class CFunction
  @param string function - represents the string representation of function for example: sin
  */
public:
  CFunction( std::string function );
  virtual bool isNumber() const;
  /**
		Method performOperation pops value out of a stack and performs operation according to the function used
		and result push back to a stack
		@param stack<double> stack - is a stack where are double values of CNumber from evaluating RPN
	*/
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;

private:
  std::string m_func; /** string represantiton of CFunction*/
};
//==============================================================================
/**
\class COperator
\brief Class is used as an operator in evaluating RPN (reverse polish notation)
*/
class COperator: public CToken{
public:
  /**
  Constructor of class COperator
  @param string o - represents the string representation of operator for example: +
  */
  COperator( std::string o);
  virtual bool isNumber() const;
  /**
    Method performOperation pops 2 values out of a stack and performs operation between them according to the operator used
    and result push back to a stack
    @param stack<double> stack - is a stack where are double values of CNumber from evaluating RPN
  */
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;
private:
  std::string m_op; /** string represantiton of COperator*/
};

#endif

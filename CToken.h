#ifndef CTOKEN_H
#define CTOKEN_H

#include <string>
#include <stack>


/**
  \class CToken
  This class is used to transform vector<string> in infix notation to RPN and evaluate the RPN
  It is abstract class
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
  @return double, if token is a number returns its value, if token is not a number returns 0
  */
  virtual double getVal() const = 0;

};
//==============================================================================
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
  double m_Val;
};
//==============================================================================
class CFunction: public CToken{
  /**
  Constructor of class CFunction
  @param string function - represents the string representation of function for example: sin
  */
public:
  CFunction( std::string function );
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;

private:
  std::string m_func;
};
//==============================================================================
class COperator: public CToken{
public:
  /**
  Constructor of class COperator
  @param string o - represents the string representation of operator for example: +
  */
  COperator( std::string o);
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;
private:
  std::string m_op;
};

#endif

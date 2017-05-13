#ifndef CTOKEN_H
#define CTOKEN_H

#include <string>
#include <stack>

class CToken{
public:
  CToken(){}
  virtual ~CToken() {};
  virtual bool isNumber() const = 0;
  virtual void performOperation( std::stack<double> & stack ) = 0;
  virtual double getVal() const = 0;
  virtual void print() const = 0;
};
//==============================================================================
class CNumber: public CToken{
public:
  CNumber( double val );
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;
  virtual void print() const;

private:
  double m_Val;
};
//==============================================================================
class CFunction: public CToken{
public:
  CFunction( std::string function );
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;
  virtual void print() const;
private:
  std::string m_func;
};
//==============================================================================
class COperator: public CToken{
public:
  COperator( std::string o);
  virtual bool isNumber() const;
  virtual void performOperation(std::stack<double> & stack);
  virtual double getVal() const;
  virtual void print() const;
private:
  std::string m_op;
};

#endif

#ifndef CTOKEN_H
#define CTOKEN_H

#include <string>
#include <memory>

class CToken{
public:
  CToken(){}
  virtual ~CToken() {};
  virtual bool isFunction() const = 0;
  virtual bool isOperator() const = 0;
  virtual bool isNumber() const = 0;
  virtual double performOperation(double left, double right) const  = 0;
  virtual double getVal() const = 0;
};
//==============================================================================
class CNumber: public CToken{
public:
  CNumber( double val );
  virtual bool isFunction() const;
  virtual bool isOperator() const;
  virtual bool isNumber() const;
  virtual double performOperation(double left, double right) const;
  virtual double getVal() const;

private:
  double m_Val;
};
//==============================================================================
class CFunction: public CToken{
public:
  CFunction( std::string function );
  virtual bool isFunction() const;
  virtual bool isOperator() const;
  virtual bool isNumber() const;
  virtual double performOperation(double val, double dummy) const;
  virtual double getVal() const;
private:
  std::string m_func;
};
//==============================================================================
class COperator: public CToken{
public:
  COperator( std::string o);

  virtual bool isFunction() const;
  virtual bool isOperator() const;
  virtual bool isNumber() const;
  virtual double performOperation(double left, double right) const;
  virtual double getVal() const;
private:
  std::string m_op;
};

#endif

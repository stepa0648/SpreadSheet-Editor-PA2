#ifndef CTOKEN_H
#define CTOKEN_H

class CToken{
public:
  CToken();
  virtual bool isFunction() const = 0;
  virtual bool isOperator() const = 0;
  virtual bool isNumber() const = 0;
  virtual double performOperation(double left, double right)  = 0;
  virtual double getVal() const = 0;
};
//==============================================================================
class CNumber: CToken{
public:
  CNumber( double val );
  virtual bool isFunction() const;
  virtual bool isOperator() const;
  virtual bool isNumber() const;
  virtual double performOperation(double left, double right);
  virtual double getVal() const;

private:
  double m_Val;
};



#endif

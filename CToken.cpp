

#include <string>
#include <stack>
#include <cmath>

#include "CToken.h"

//==============================================================================
CNumber::CNumber( double val = 0 ):m_Val(val){}

bool CNumber::isFunction() const{
    return false;
  }
bool CNumber::isOperator() const {
    return false;
  }
bool CNumber::isNumber() const {
    return true;
  }

double CNumber::performOperation(double left, double right){
    return 0;
  }
double CNumber::getVal() const {
    return m_Val;
  }
//==============================================================================
class CFunction: CToken{
public:
  CFunction( std::string function): m_func(function){}

  virtual bool isFunction() const{
    return true;
  }
  virtual bool isOperator() const {
    return false;
  }
  virtual bool isNumber() const {
    return false;
  }
  virtual double performOperation(double val, double dummy){
      double res;

      if(m_func == "sin"){
        res = sin(val);
      }else if(m_func == "cos"){
        res = cos(val);
      }else if(m_func == "tan"){
        res = tan(val);
      }else if(m_func == "cotg"){
        res = pow(tan(val), -1);
      }else if(m_func == "abs"){
        res = fabs(val);
      }else if(m_func == "sqrt"){
        res = sqrt(val);
      }else if(m_func == "exp"){
        res = exp(val);
      }else if(m_func == "log"){
        res = log10(val);
      }else if(m_func == "ln"){
        res = log(val);
      }

      return res;
  }

  virtual double getVal() const {
    return 0;
  }
protected:
  std::string m_func;
};
//==============================================================================
class COperator: CToken{
public:
  COperator( std::string o): m_op(o) {}

  virtual bool isFunction() const{
    return false;
  }
  virtual bool isOperator() const {
    return true;
  }
  virtual bool isNumber() const {
    return false;
  }
  virtual double performOperation(double left, double right){
    double res;
    if( m_op == "+"){
      res = left + right;
    }else if( m_op == "-"){
      res = left - right;
    }else if( m_op == "*"){
      res = left * right;
    }else if( m_op == "/"){
      if( right != 0){
        res = left - right;
      }
      // dodelat vyjimku
    }else if( m_op == "^"){
      res = pow(left, right);
    }

    return res;
  }
  virtual double getVal() const {
    return 0;
  }
protected:
  std::string m_op;
};
//==============================================================================

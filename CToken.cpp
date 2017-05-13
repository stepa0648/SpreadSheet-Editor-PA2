
#include "CToken.h"

#include <string>
#include <stack>
#include <cmath>

#include <exception>

#include <iostream>


using namespace std;


class DivisionByZero: public exception{
	public:
	virtual const char * what() const noexcept{
		return "DivisionByZero";
	}
};

class NotAFunction : public exception{
	public:
	virtual const char * what() const noexcept{
		return "Not A Function";
	}
};


//==============================================================================
CNumber::CNumber( double val = 0 ):m_Val(val){}

bool CNumber::isNumber() const {
    return true;
  }

void CNumber::performOperation(stack<double> & stack){
  }
double CNumber::getVal() const {
    return m_Val;
  }
void CNumber::print() const{
  cout << m_Val;
}
//==============================================================================

  CFunction::CFunction( string function): m_func(function){}

   bool CFunction::isNumber() const {
    return false;
  }
   void CFunction::performOperation(stack<double> & stack){
      double res;
      double val = stack.top();
      stack.pop();

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
      }else{
        /** throws an exception NotAFunction, if its not known function*/
        throw NotAFunction();
      }
      stack.push(res);
  }

   double CFunction::getVal() const {
    return 0;
  }

  void CFunction::print() const{
    cout << m_func;
  }

//==============================================================================
  COperator::COperator( string o): m_op(o) {}

   bool COperator::isNumber() const {
    return false;
  }
   void COperator::performOperation(stack<double> & stack){
    double res;
    double right = stack.top();
    stack.pop();
    double left = stack.top();
    stack.pop();

    if( m_op == "+"){
      res = left + right;
    }else if( m_op == "-"){
      res = left - right;
    }else if( m_op == "*"){
      res = left * right;
    }else if( m_op == "/"){
      if( right != 0){
        res = left / right;
      }else{
        /** throws an exception DivisionByZero, if you divide by 0*/
        throw DivisionByZero();
      }
    }else if( m_op == "^"){
      res = pow(left, right);
    }
    stack.push(res);
  }
   double COperator::getVal() const {
    return 0;
  }
  void COperator::print() const{
    cout << m_op;
  }
//==============================================================================

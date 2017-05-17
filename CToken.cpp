
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

class InvalidDomain : public exception{
	public:
	virtual const char * what() const noexcept{
		return "InvalidDomain";
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

			//SIN=====================================================================
      if(m_func == "sin"){
        res = sin(val);
			//COS=====================================================================
      }else if(m_func == "cos"){
        res = cos(val);
			//TAN=====================================================================
      }else if(m_func == "tan"){
        res = tan(val);
			//COTG====================================================================
      }else if(m_func == "cotg"){
        res = pow(tan(val), -1);
			//ABS=====================================================================
      }else if(m_func == "abs"){
        res = fabs(val);
			//SQRT====================================================================
      }else if(m_func == "sqrt"){
				if(val < 0){
					throw InvalidDomain();
				}
        res = sqrt(val);
			//EXP=====================================================================
      }else if(m_func == "exp"){
        res = exp(val);
			//LOG=====================================================================
      }else if(m_func == "log"){
				if(val <= 0){
					throw InvalidDomain();
				}
        res = log10(val);
			//LN======================================================================
			}else if(m_func == "ln"){
				if(val <= 0){
					throw InvalidDomain();
				}
        res = log(val);
			//ELSE====================================================================
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

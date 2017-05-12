
#include "CToken.h"

#include <string>
#include <stack>
#include <cmath>


#include <iostream>


using namespace std;


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

   bool CFunction::isFunction() const{
    return true;
  }
   bool CFunction::isOperator() const {
    return false;
  }
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
        // neni funkce
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

   bool COperator::isFunction() const{
    return false;
  }
   bool COperator::isOperator() const {
    return true;
  }
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
      }
      // dodelat vyjimku
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

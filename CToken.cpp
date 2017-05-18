
#include "CToken.h"

#include <string>
#include <stack>
#include <cmath>

#include <exception>

#include <iostream>


using namespace std;

/**
	\DivisionByZero
	This class is used to be throw as an exception when you divide by 0
*/
class DivisionByZero: public exception{
	public:
	virtual const char * what() const noexcept{
		return "DivisionByZero";
	}
};

/**
	\NotAFunction
	This class is used to be throw as an exception when string is not a funcion
*/
class NotAFunction : public exception{
	public:
	virtual const char * what() const noexcept{
		return "Not A Function";
	}
};

/**
	\InvalidDomain
	This class is used to be throw as an exception when domain of a function is invalid for example sqrt(-2)
*/
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

//==============================================================================

  CFunction::CFunction( string function): m_func(function){}

   bool CFunction::isNumber() const {
    return false;
  }
	/**
		Method performOperation pops value out of a stack and performs operation according to the function used
		and result push back to a stack
		@param stack<double> stack - is a stack where are double values of CNumber from evaluating RPN
	*/
   void CFunction::performOperation(stack<double> & stack){
      double res;
      double val = stack.top();
      stack.pop();

			//SIN=====================================================================
			/**
			if function is sin evaluates the sinus value of the double and push it back to the stack
			*/
			if(m_func == "sin"){
        res = sin(val);
			//COS=====================================================================
			/**
			if function is cos evaluates the cosinus value of the double and push it back to the stack
			*/
      }else if(m_func == "cos"){
        res = cos(val);
			//TAN=====================================================================
			/**
			if function is tan evaluates the tangens value of the double and push it back to the stack
			*/
      }else if(m_func == "tan"){
        res = tan(val);
			//COTG====================================================================
			/**
			if function is cotg evaluates the cotangens value of the double and push it back to the stack
			*/
      }else if(m_func == "cotg"){
        res = pow(tan(val), -1);
			//ABS=====================================================================
			/**
			if function is abs evaluates the absulute value of the double and push it back to the stack
			*/
      }else if(m_func == "abs"){
        res = fabs(val);
			//SQRT====================================================================
			/**
			if function is sqrt evaluates the square root of the double and push it back to the stack
			*/
      }else if(m_func == "sqrt"){
				if(val < 0){
					throw InvalidDomain();
				}
        res = sqrt(val);
			//EXP=====================================================================
			/**
			if function is exp evaluates the exponencial value of the double and push it back to the stack
			*/
      }else if(m_func == "exp"){
        res = exp(val);
			//LOG=====================================================================
			/**
			if function is log evaluates the decimal logarith of the double and push it back to the stack
			*/
      }else if(m_func == "log"){
				if(val <= 0){
					throw InvalidDomain();
				}
        res = log10(val);
			//LN======================================================================
			/**
			if function is ln evaluates the natural logarithm of the double and push it back to the stack
			*/
			}else if(m_func == "ln"){
				if(val <= 0){
					throw InvalidDomain();
				}
        res = log(val);
			//ELSE====================================================================
			/**
			if function is unknown throws and NotAFunction exception
			*/
      }else{
        /** throws an exception NotAFunction, if its not known function*/
        throw NotAFunction();
      }
      stack.push(res);
  }

   double CFunction::getVal() const {
    return 0;
  }



//==============================================================================
  COperator::COperator( string o): m_op(o) {}

   bool COperator::isNumber() const {
    return false;
  }

	/**
		Method performOperation pops 2 values out of a stack and performs operation between them according to the operator used
		and result push back to a stack
		@param stack<double> stack - is a stack where are double values of CNumber from evaluating RPN
	*/
   void COperator::performOperation(stack<double> & stack){
    double res;
    double right = stack.top();
    stack.pop();
    double left = stack.top();
    stack.pop();
		/*
		Operator + adds two doubles
		*/
    if( m_op == "+"){
      res = left + right;
		/*
			Operator - substracts right double from the left one
		*/
    }else if( m_op == "-"){
      res = left - right;
		/*
			Operator * multiplies two doubles
		*/
    }else if( m_op == "*"){
      res = left * right;
		/*
			Operator / devides two doubles
		*/
    }else if( m_op == "/"){
      if( right != 0){
        res = left / right;
      }else{
        /** throws an exception DivisionByZero, if you divide by 0*/
        throw DivisionByZero();
      }
		/*
			Operator ^ makes the left operand powered by the right one por exaplme 2^3 = 2 * 2 * 2 = 8
		*/
    }else if( m_op == "^"){
      res = pow(left, right);
    }
    stack.push(res);
  }
   double COperator::getVal() const {
    return 0;
  }

//==============================================================================

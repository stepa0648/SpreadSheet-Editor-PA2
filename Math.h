/**
 * \file Math.h
 * \author severste
 *
   \brief This is the file where all mathematical functions are defined.
	 All mathematical functions and all functions related to evaluating mathematical expression in cells
	 Functions are documented in Math.cpp file
	*/

#ifndef MATH_H
#define MATH_H

//Evaluating Mathematical Expression============================================

#include <string>
#include <vector>
#include <exception>
#include <memory>

#include "CToken.h"
#include "CTable.h"

/**
   \class BracketsMissMatch
   \brief Class is used to be throw as an exception when brackets error happens
   the what() method returns error message
 */
class BracketsMissMatch : public std::exception {
public:
virtual const char * what() const noexcept {
								return "Brackets missmatch";
}
};

/**
   \class OperatorError
   \brief Class is used to be throw as an exception when operator error happens.
   Error could be for example operator at the end of expressin or binary operator with only one operand etc.

 */
class OperatorError : public std::exception {
public:
virtual const char * what() const noexcept {
								return "OperatorError";
}
};

bool isMathExprTrans(std::string & val);

bool isMathExpr(const std::string & val);

bool findParents(const std::string & str, std::set<std::pair<int,int>> & set);

std::set<std::pair<int,int>> findAncestors(std::set<std::pair<int,int>> & ancestors,std::set<std::pair<int,int>> parents, const CTable & table);

double stringToDouble( const std::string & str);

bool isOperator(const std::string& c);

bool isFunction(const std::string& c);

bool isCell(const std::string& str, int & y, int & x);

std::vector<std::string> stringToVec( const std::string & str, const CTable & table );

int operatorPrecedence(const std::string& c);

std::vector<std::shared_ptr<CToken> > infixToRPN(const std::vector<std::string> & vec);

double evaluateRPN(const std::vector<std::shared_ptr<CToken> > & vec);

bool evaluateString(double & res, std::string & str, const CTable & table);

bool evaluateCell(double & res, const std::string & val,const CTable & table);


#endif

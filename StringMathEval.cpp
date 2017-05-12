/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 10, 2017, 3:49 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <exception>
#include <memory>

#include "CToken.h"

using namespace std;

/*
vector<string> stringToVec( const string & str ){
  char c = 0;
  char prev = 0;
  vector<string> vec;
  int i = 0;
  string substr;

  while( 1 ){
    if(i != 0){ // if its not the firt char insert into prev the last one
      prev = c;
    }

    c = str[i]; // insert next char from str in c

    if( c == 0 ){ // if its end of string break
      break;
    }
    if( c == ' ' || c == '\t' ){ // ignore whitespaces
      i++;
      continue;
    }

    if( prev == 0 && (c == '*' || c == '/' || c == ')') ){ // if the first char is binary operator error
      cout << "Chybny operator na zacatku" << endl;
    }
    if( prev == '(' && (c == '*' || c == '/' || c == ')') ){ // if the next char after opening bracket is binary operator error
      cout << "Chybny operator po oteviraci zavorce" << endl;
    }

    if( isOperator(c) && ( (prev != 0 && prev != '(' ) || c == '(' )){ // if char is operator and is not first or after
                                                                          bracket insert it into a vector
      if(substr.size() != 0){
        vec.push_back(substr);
      }
      substr = c;
      vec.push_back(substr);
      substr.erase();
      i++;
      continue;
    }

    substr += c;
    i++;
  }

  return vec;
}*/

class BracketsMissMatch : public exception{
	public:
	virtual const char * what() const noexcept{
		return "Brackets missmatch";
	}
};

/** checks if string is an operator, returns bool*/
bool isOperator(const string & c){
  return c == "+" || c == "-" || c == "*" || c == "/" || c=="^";
}
/** checks if string is a funtion, returns bool*/
bool isFunction(const string & c){
  return c == "sin" || c == "cos" || c == "tan" || c == "cotg"
        || c == "abs" || c == "sqrt" || c == "exp" || c == "log"
        || c == "ln";
}

/** converts string to double, if string is NaN throw an exception invalid_argument*/
double stringToDouble( const string & str){
  double res = 0;
  size_t resLen = 0;

  res = stod( str, &resLen);

  if( resLen != str.size() ){
    throw invalid_argument("Neni cislo");
  }

  return res;
}

/** return the operator precedence, the higer value has higer precedence*/
int operatorPrecedence(const string & c){
  if( c == "+" || c == "-"){
    return 1;
  }
  if( c == "*" || c == "/"){
    return 2;
  }
  if( c == "^"){
    return 3;
  }
  return 0;
}

vector<shared_ptr<CToken>> infixToRPN(const vector<string> & vec){
  double res=0;
  bool isNumber;
  vector<shared_ptr<CToken>> out;
  stack<string> stack;

  for(size_t i = 0; i < vec.size(); i++){
    isNumber = true;
    /** tries to parse string to double to know if it is number or not */
    try{
      res = stringToDouble ( vec[i] );
    }catch( invalid_argument a){
      isNumber = false;
    }

    if( isNumber ){
      /** if token is a number, just push it on the output*/
      out.push_back(shared_ptr<CToken> (new CNumber(res)) );

    }else if( isFunction( vec[i] ) ){
      /** if token is function push it on the stack*/
      stack.push( vec[i] );

    }else if( isOperator( vec[i]) ){
      if( !stack.empty() ){
        /** while a operator with higer or equal precedence is on the stack, pop it to the output and then push operator on a stack */
        while( operatorPrecedence(stack.top()) >= operatorPrecedence( vec[i] )){
          /** if a left bracket is on the top of the stack dont pop operators, just push this one on the stack*/
          if( stack.top() == "(" ){
            break;
          }
          /** push operator in the output */
          out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
          stack.pop();
          if( stack.empty() ){
            break;
          }
        }
      }
      /** push operator on a stack */
      stack.push(vec[i]);
    }else if( vec[i] == "("){
      /** if token is left bracket push it on the stack no matter what*/
      stack.push(vec[i]);
    }else if( vec[i] == ")"){
      /** if token is right bracket empty stack until left bracket is found
          if you empty whole stack brackets were wrong
      */
      while( stack.top() != "(" ){
        if( stack.empty() ){
          break;
        }
        if( isFunction( stack.top() ) ){
          out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
          stack.pop();
        }else{
          out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
          stack.pop();
        }
      }
      /** pop the operators between brackets*/
      if(! stack.empty() ){
        stack.pop();
        if( isFunction( stack.top() ) ){
          out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
          stack.pop();
        }
      }else{
        /** if a left bracket wasnt in the stack the brackets were wrong*/
        throw BracketsMissMatch();
      }
    }
  }

  /** if you have run out of the tokens you need to empty the stack*/
  while (! stack.empty() ){
    /** if there is a left bracket in stack, brackets were wrong*/
    if( stack.top() == "("){
      throw BracketsMissMatch();
      break;
    }
    if( isFunction( stack.top() ) ){
      out.push_back(shared_ptr<CToken> (new CFunction( stack.top() ) ) );
      stack.pop();
    }else{ /** if is an operator*/
      out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
      stack.pop();
    }
  }
  return out;
}


/**
  evalutes vector where is RPN and returns double value
*/
double evaluateRPN(const vector<shared_ptr<CToken>> & vec){
  stack<double> stack;

  for( auto it : vec){
    if( it->isNumber() ){
      stack.push( it->getVal() );
    }else{
      it->performOperation(stack);
    }
  }

  return stack.top();
}


int main(int argc, char** argv) {

  double res;

  vector<string> infix;
  vector< shared_ptr<CToken> > rpn;

//789×38−(2^4)÷sin(38)+cos(29)

  infix.push_back("sin");
  infix.push_back("(");
  infix.push_back("62.4");
  infix.push_back(")");
  infix.push_back("*");
  infix.push_back("0.345");
  infix.push_back("-");
  infix.push_back("(");
  infix.push_back("(");
  infix.push_back("6");
  infix.push_back("+");
  infix.push_back("0.7");
  infix.push_back(")");
  infix.push_back("/");
  infix.push_back("9");
  infix.push_back(")");
  infix.push_back("*");
  infix.push_back("102");


  try{
    rpn = infixToRPN(infix);
  }catch(const exception & excp){
    cerr << excp.what() << endl;
    return 1;
  }catch(...){
    cerr << "Neocekavana chyba" << endl;
    return 2;
  }

  res = evaluateRPN( rpn );

  cout << res << endl;


  return 0;
}

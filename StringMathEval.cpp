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

class BracketsMissMatch : public exception{
	public:
	virtual const char * what() const noexcept{
		return "Brackets missmatch";
	}
};

class OperatorError : public exception{
	public:
	virtual const char * what() const noexcept{
		return "OperatorError";
	}
};
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

bool isCell(const string & str, double & y, double & x){
	/** checks if the cell start with [ and ends with ]*/
	if( str[0] == '[' && str.back() == ']' ){
		char c = 0;
		string substr = "";
		int i = 1;
		/** while ; is not found put char in substr*/
		c = str[i];
		while(c != ';'){
			/** ; wasnt found*/
			if((unsigned) i >= str.size() ){
				cout << "nenalezeno \";\"" << endl;
				return false;
			}
			substr += c;

			i++;
			c = str[i];
		}
		/** checks if substr is a number*/
		try{
			cout << "y = " << substr << endl;
			y = stringToDouble(substr);
		}catch(const invalid_argument & a){
			cout << "Y neni cislo" << endl;
			return false;
		}

		substr = "";
		i++;
		c = str[i];
		/** while ] is not found put char in substr*/
		while(c != ']'){
			substr += c;
			i++;
			c = str[i];
		}
		/** checks if substr is a number*/
		try{
			cout << "x = " << substr << endl;
			x = stringToDouble(substr);
		}catch(const invalid_argument & a){
			cout << "X neni cislo" << endl;
			return false;
		}

		/** checks if coords are positive or 0*/
		if( y >= 0 && x >= 0){
			return true;
		}

	}

	return false;
}

vector<string> stringToVec( const string & str ){
  char c = 0;
  char prev = 0;
  vector<string> vec;
  int i = 0;
  string substr;

  while( 1 ){

    if(i != 0 && c != ' ' && c != '\t' ){ // if its not the first char insert into prev the last one
      prev = c;
    }

    c = str[i]; // insert next char from str in c

		/** temporary strings - typecast from char to int for functions isOperator and isFunction*/
		string c1, prev1;
		c1 = c;
		prev1 = prev;

    if( c == 0 ){ // if its end of string break
			// if you have reached the end of a string push last token into the vector
			if(substr.size() != 0){
        vec.push_back(substr);
      }
			if( isOperator( vec.back() ) || isFunction(vec[vec.size() - 1]) || vec[vec.size() - 1] == "(" ){
				cout << "Chybny operator na konci" << endl;
				throw OperatorError();
			}
      break;
    }
    if( c == ' ' || c == '\t' ){ // ignore whitespaces
      i++;
      continue;
    }
		
    if( prev == 0 && ( c == '*' || c == '/' || c == ')' || c == '^' || c == '+' ) ){ // if the first char is binary operator -> error
      cout << "Chybny operator na zacatku" << endl;
			throw OperatorError();
    }
    if( prev == '(' && (c == '*' || c == '/' || c == ')' || c=='^') ){ // if the next char after opening bracket is binary operator error
      cout << "Chybny operator po oteviraci zavorce" << endl;
			throw OperatorError();
    }

		if( c==')' && ( isOperator(prev1) || isFunction(prev1) ) ){
			cout << "Chybny operator pred zaviraci zavorkou" << endl;
			throw OperatorError();
		}

		if( isOperator(c1) && ( !(prev >= 48 && prev <=57) && prev != ')' && prev != ']') ){
			cout << "Chybny operator pred operatorem" << endl;
			throw OperatorError();
		}

		if( isOperator(prev1) ){
			if( isOperator(c1) ){
				cout << "Vice operatoru za sebou - CHYBA" << endl;
				throw OperatorError();
			}
			if(vec.size() == 0 && !(c >= 48 && c <= 57 ) ){
				cout<< "Chybny operator na zacatku, a po nem neni cislo" << endl;
				throw OperatorError();
			}
		}

		/** if char is an operator or brackets and isn not first or is left bracket insert it into a vector and prev substr as well*/
    if(  ( isOperator(c1) || c1 == "(" || c1 == ")" )
			&& ( prev != 0 && prev != '(' ) || c == '(' ) {

      if(substr.size() != 0){
				//kontrola jestli je to bunka
				double x=0, y=0;
				if( isCell( substr, y, x ) ){
					//opravit
					vec.push_back( to_string(y) );
				}else{
					vec.push_back(substr);
				}
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

	double x=0, y=0;
	if( isCell( vec.back(), y, x ) ){
		vec.pop_back();
		//opravit
		vec.push_back( to_string(y) );
	}


  return vec;
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
          if you empty whole stack and didnt find a left bracket, brackets were wrong
      */
      while( stack.top() != "(" ){
        if( stack.empty() ){
          break;
        }
				/** pop the operators between brackets*/
        if( isFunction( stack.top() ) ){
          out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
          stack.pop();
        }else{
          out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
          stack.pop();
        }
      }
			/** if stack isnt empty, there is a left bracket - pop it out*/
      if(! stack.empty() ){
        stack.pop();

				/** if there was a function before bracket push it in the output*/
				if(! stack.empty() ){
					if( isFunction( stack.top() ) ){
						out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
						stack.pop();
					}
				}
      }else{
        /** if a left bracket wasnt in the stack the brackets were wrong*/
        throw BracketsMissMatch();
      }
    }else{
			cout << "Unknown symbol" << endl;
			throw OperatorError();
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

  double res, y=0, x=0;
	string str = "[15;8]";
  vector<string> infix;
  vector< shared_ptr<CToken> > rpn;
	bool error = false;


try{
	infix = stringToVec(str);
}catch( const exception & excp){
	cerr << excp.what() << endl;
	error = true;
}

	cout << "String: =================================" << endl;
	cout << str << endl;
	cout << "Infix: ==================================" << endl;
	for(auto it : infix){
		cout << it << endl;
	}
	cout << endl;



if( !error ){
	try{
		rpn = infixToRPN(infix);
	}catch(const exception & excp){
		cerr << excp.what() << endl;
		error = true;
		return 1;
	}
}
if( !error ){
	try{
		res = evaluateRPN( rpn );
	}catch( const exception & excp){
		cerr << excp.what() << endl;
		error = true;
		return 1;
	}
}

if( !error ){
	cout << res << endl;
}



  return 0;
}

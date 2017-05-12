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

using namespace std;
/*

void vectorToPostfixNot( vector<string> & vec ){
    pair<string, int> operatorPrecedence;
    vector<string> tmp;
    stack<string> stack;
    for(auto it = vec.begin(); it <= vec.end(); it++){
        if( (*it != "+") && (*it != "-") && (*it != "*") && (*it != "/") && (*it != "(") && (*it != ")") && (*it != "^") ){
            tmp.push_back(*it);
        }else{
            if(stack.empty() || *it == "("){
                stack.push(*it);
            }else if(*it == ")"){
                while( stack.top() != "(" ){
                    vec.push_back(stack.top());
                    stack.pop();
                }
            }else{
                if(*it < stack.top()){
                    stack.push(*it);
                }
            }
        }
    }
    vec.erase(vec.begin(), vec.end());
    vec = tmp;
}*/

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

bool isOperator(const string & c){
  return c == "+" || c == "-" || c == "*" || c == "/";
}
bool isFunction(const string & c){
  return c == "sin" || c == "cos" || c == "tan" || c == "cotg"
        || c == "abs" || c == "sqrt";
}

double stringToDouble( const string & str){
  double res = 0;
  size_t resLen = 0;

  res = stod( str, &resLen);

  if( resLen != str.size() ){
    throw invalid_argument("Neni cislo");
  }

  return res;
}

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

vector<string> infixToRPN(const vector<string> & vec){
  //double res=0;
  bool isNumber;
  vector<string> out;
  stack<string> stack;

  for(size_t i = 0; i < vec.size(); i++){
    isNumber = true;
    try{
      //res = stringToDouble (vec[i]);
      stringToDouble (vec[i]);
    }catch( invalid_argument a){
      //cout << vec[i] << " neni cislo" << endl;
      isNumber = false;
    }

    if( isNumber ){

      // push on out
      out.push_back(vec[i]);

    }else if( isFunction( vec[i] ) ){

      stack.push(vec[i]);

    }else if( isOperator( vec[i]) ){
      if( !stack.empty() ){
        while( operatorPrecedence(stack.top()) >= operatorPrecedence( vec[i] )){
          if( stack.top() == "(" ){
            break;
          }
          out.push_back( stack.top() );
          stack.pop();
          if( stack.empty() ){
            break;
          }
        }
      }
      stack.push(vec[i]);
    }else if( vec[i] == "("){
      stack.push(vec[i]);
    }else if( vec[i] == ")"){
      while( stack.top() != "(" ){
        if( stack.empty() ){
          break;
        }
        out.push_back( stack.top() );
        stack.pop();
      }
      if(! stack.empty() ){
        stack.pop();
        if( isFunction( stack.top() ) ){
          out.push_back( stack.top() );
          stack.pop();
        }
      }else{
        throw BracketsMissMatch();
      }
    }
  }

  while (! stack.empty() ){

    if( stack.top() == "("){
      throw BracketsMissMatch();
      break;
    }

    out.push_back( stack.top() );
    stack.pop();
  }
  return out;
}






int main(int argc, char** argv) {

    string str1 = "a+b*(c-d)";
    string str = "-10+2*sin(-4-1)";
    string str2 = "(42-1)";
    vector<string> vec;
    vector<string> infix;
    vector<string> rpn;

  /*  infix.push_back("-10");
    infix.push_back("+");
    infix.push_back("2");
    infix.push_back("*");
    infix.push_back("sin");
    infix.push_back("(");
    infix.push_back("-4");
    infix.push_back("-");
    infix.push_back("1");
    infix.push_back(")");*/

  infix.push_back("10");
    infix.push_back("+");
    infix.push_back("sin");
    infix.push_back("(");
    infix.push_back("30");
    infix.push_back("+");
    infix.push_back("5");
    infix.push_back(")");
    infix.push_back("*");
    infix.push_back("25");
    infix.push_back("+");
    infix.push_back("10");




try{
  rpn = infixToRPN(infix);
}catch(const exception & excp){
  cerr << excp.what() << endl;
  return 1;
}catch(...){
  cerr << "Neocekavana chyba" << endl;
  return 2;
}




    cout << "INFIX:" << endl;
    for(auto it : infix){
      cout << it << endl;
    }
    cout << "RPN:" << endl;
    for(auto it : rpn){
      cout << it << endl;
    }




    /*vec = stringToVector(str2);

    for(auto it = vec.begin(); it <= vec.end(); it++){
       cout << *it << "|";
    }
    cout << "\n===================" << endl;
    //vectorToPostfixNot(vec);
   // for(auto it = vec.begin(); it <= vec.end(); it++){
      //  cout << *it << ";";
    //}
    cout << endl;*/

    return 0;
}

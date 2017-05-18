
#include "CToken.h"
#include "CTable.h"
#include "Math.h"

#include <vector>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

bool findParents(const string & str, set<pair<int,int>> & set){
  char c;
  bool found = false;

  //cout << str << endl;

  if( str.size() != 0 ){
    c = str[0];
  }else{
    return false;
  }

  int begin = 0, end = 0;
  for(size_t i=0; i<str.size(); i++){
			c = str[i];

			if( c == '[' ){
        begin = i;
      }
      if( c == ']'){
        end = i;
        if( begin < end ){
          int y = 0, x = 0;
          if( isCell( str.substr(begin, end-begin+1), y, x )){
            found = true;
            set.insert(make_pair(y,x));
          }
        }
        begin = 0;
        end = 0;
      }
  }

  return found;
}

set<pair<int,int>> findAncestors(set<pair<int,int>> & ancestors,set<pair<int,int>> parents, const CTable & table){

  ancestors.insert(parents.begin(), parents.end());

  if( parents.empty() ){
    return set<pair<int,int>>();
  }
  for(auto it: parents){
    findAncestors(ancestors, table.getCellParents(it.first, it.second), table);
  }

  return ancestors;
}



//Evaluating Mathematical Expression============================================

bool evaluateCell(double & res, const string & val, const CTable & table);

/** if expression starts with = returns true and cut off the = sign from string*/
bool isMathExprTrans(string & val){
        size_t i=0;
        char c = 0;
        c = val[i];

        while( c == ' ' || c == '\t') {
                if( i >= val.size() ) {
                        break;
                }
                c = val[i];
                i++;
        }

        if(c == '=') {
          // if there is not only = in the expression return true
          i++;
          while( i < val.size() ){
            c = val[i];
            if(c != ' ' && c != '\t' ){
              return true;
            }
            i++;
          }
                return false;
        }

        return false;
}

bool isMathExpr(const std::string & val){
  size_t i=0;
  char c = 0;
  c = val[i];
  while( c == ' ' || c == '\t') {
          if( i >= val.size() ) {
                  break;
          }
          c = val[i];
          i++;
  }
  if(c == '=') {
    // if there is not only = in the expression return true
    i++;
    while( i < val.size() ){
      c = val[i];
      if(c != ' ' && c != '\t' ){
        return true;
      }
      i++;
    }
          return false;
  }

  return false;
}

/** converts string to double, if string is NaN throw an exception invalid_argument*/
double stringToDouble( const string & str){
        double res = 0;
        size_t resLen = 0;

        res = stod( str, &resLen);

        if( resLen != str.size() ) {
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

bool isCell(const string & str, int & y, int & x){
        /** checks if the string starts with [ and ends with ]*/
        if( str[0] == '[' && str.back() == ']' ) {
                char c = 0;
                string substr = "";
                int i = 1;
                /** while ; is not found put char in substr*/
                c = str[i];
                while(c != ';') {
                        /** ; wasnt found*/
                        if((unsigned) i >= str.size() ) {
                                //cout << "nenalezeno \";\"" << endl;
                                return false;
                        }
                        substr += c;

                        i++;
                        c = str[i];
                }
                /** checks if substr is a number*/
                try{
                        y = stringToDouble(substr);
                }catch(const invalid_argument & a) {
                        //cout << "Y neni cislo" << endl;
                        return false;
                }

                substr = "";
                i++;
                c = str[i];
                /** while ] is not found put char in substr*/
                while(c != ']') {
                        substr += c;
                        i++;
                        c = str[i];
                }
                /** checks if substr is a number*/
                try{
                        x = stringToDouble(substr);
                }catch(const invalid_argument & a) {
                        //cout << "X neni cislo" << endl;
                        return false;
                }

                /** checks if coords are positive or 0*/
                if( y >= 0 && x >= 0) {
                        return true;
                }

        }

        return false;
}

vector<string> stringToVec( const string & str, const CTable & table ){
        char c = 0;
        char prev = 0;
        vector<string> vec;
        int i = 0;
        string substr;

        while( 1 ) {

                if(i != 0 && c != ' ' && c != '\t' ) { // if its not the first char insert into prev the last one
                        prev = c;
                }

                c = str[i]; // insert next char from str in c

                /** temporary strings - typecast from char to int for functions isOperator and isFunction*/
                string c1, prev1;
                c1 = c;
                prev1 = prev;

                if( c == 0 ) { // if its end of string break
                        // if you have reached the end of a string push last token into the vector
                        if(substr.size() != 0) {
                                vec.push_back(substr);
                        }
                        if( isOperator( vec.back() ) || isFunction(vec[vec.size() - 1]) || vec[vec.size() - 1] == "(" ) {
                                throw OperatorError();
                        }
                        break;
                }
                if( c == ' ' || c == '\t' ) { // ignore whitespaces
                        i++;
                        continue;
                }

                // if the first char is binary operator -> error
                //Wrong operator at the beginning
                if( prev == 0 && ( c == '*' || c == '/' || c == ')' || c == '^' || c == '+' ) ) {
                        throw OperatorError();
                }

                //Wrong operator after left bracket
                if( prev == '(' && (c == '*' || c == '/' || c == ')' || c=='^' ) ) { // if the next char after opening bracket is binary operator error
                        throw OperatorError();
                }

                //Wrong operator before right bracket
                if( c==')' && ( isOperator(prev1) || isFunction(prev1) || prev != ']') ) {
                        throw OperatorError();
                }

                //Wrong token (number or function or bracket) before operator
                if( isOperator(c1) && ( !(prev >= 48 && prev <=57) && prev != ')' && prev != ']') ) {
                  if(c1!= "-"){
                    throw OperatorError();
                  }
                }

                if( isOperator(prev1) ) {
                        //more operators in a row - error
                        if( isOperator(c1) ) {
                                throw OperatorError();
                        }

                        //After operator at the beginning is not a number
                        if(vec.size() == 0 && !(c >= 48 && c <= 57 ) ) {
                                throw OperatorError();
                        }
                }

                /** if char is an operator or brackets and is not first or is left bracket insert it into a vector and prev substr as well*/
                if( ( ( isOperator(c1) || c1 == "(" || c1 == ")" )
                      && ( prev != 0 && prev != '(' ) ) || c == '(' ) {

                        if(substr.size() != 0) {
                                //checks if the substr is a cell
                                int x=0, y=0;
                                if( isCell( substr, y, x ) ) {
                                        vec.push_back( to_string( table.getResCell(y,x) ) );
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

        int x=0, y=0;
        if( isCell( vec.back(), y, x ) ) {
                vec.pop_back();

                vec.push_back( to_string( table.getResCell(y,x) ) );
        }


        return vec;
}


/** return the operator precedence, the higer value has higer precedence*/
int operatorPrecedence(const string & c){
        if( c == "+" || c == "-") {
                return 1;
        }
        if( c == "*" || c == "/") {
                return 2;
        }
        if( c == "^") {
                return 3;
        }
        return 0;
}

vector<shared_ptr<CToken> > infixToRPN(const vector<string> & vec){
        double res=0;
        bool isNumber;
        vector<shared_ptr<CToken> > out;
        stack<string> stack;

        for(size_t i = 0; i < vec.size(); i++) {
                isNumber = true;
                /** tries to parse string to double to know if it is number or not */
                try{
                        res = stringToDouble ( vec[i] );
                }catch( invalid_argument a) {
                        isNumber = false;
                }

                if( isNumber ) {
                        /** if token is a number, just push it on the output*/
                        out.push_back(shared_ptr<CToken> (new CNumber(res)) );

                }else if( isFunction( vec[i] ) ) {
                        /** if token is function push it on the stack*/
                        stack.push( vec[i] );

                }else if( isOperator( vec[i]) ) {
                        if( !stack.empty() ) {
                                /** while a operator with higer or equal precedence is on the stack, pop it to the output and then push operator on a stack */
                                while( operatorPrecedence(stack.top()) >= operatorPrecedence( vec[i] )) {
                                        /** if a left bracket is on the top of the stack dont pop operators, just push this one on the stack*/
                                        if( stack.top() == "(" ) {
                                                break;
                                        }
                                        /** push operator in the output */
                                        out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
                                        stack.pop();
                                        if( stack.empty() ) {
                                                break;
                                        }
                                }
                        }
                        /** push operator on a stack */
                        stack.push(vec[i]);
                }else if( vec[i] == "(") {
                        /** if token is left bracket push it on the stack no matter what*/
                        stack.push(vec[i]);
                }else if( vec[i] == ")") {
                        /** if token is right bracket empty stack until left bracket is found
                            if you empty whole stack and didnt find a left bracket, brackets were wrong
                         */
                        while( stack.top() != "(" ) {
                                if( stack.empty() ) {
                                        break;
                                }
                                /** pop the operators between brackets*/
                                if( isFunction( stack.top() ) ) {
                                        out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
                                        stack.pop();
                                }else{
                                        out.push_back( shared_ptr<CToken> (new COperator( stack.top() ) ) );
                                        stack.pop();
                                }
                        }
                        /** if stack isnt empty, there is a left bracket - pop it out*/
                        if(!stack.empty() ) {
                                stack.pop();

                                /** if there was a function before bracket push it in the output*/
                                if(!stack.empty() ) {
                                        if( isFunction( stack.top() ) ) {
                                                out.push_back( shared_ptr<CToken> (new CFunction( stack.top() ) ) );
                                                stack.pop();
                                        }
                                }
                        }else{
                                /** if a left bracket wasnt in the stack the brackets were wrong*/
                                throw BracketsMissMatch();
                        }
                }else{
                        //cout << "Unknown symbol" << endl;
                        throw OperatorError();
                }
        }

        /** if you have run out of the tokens you need to empty the stack*/
        while (!stack.empty() ) {
                /** if there is a left bracket in stack, brackets were wrong*/
                if( stack.top() == "(") {
                        throw BracketsMissMatch();
                        break;
                }
                if( isFunction( stack.top() ) ) {
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
double evaluateRPN(const vector<shared_ptr<CToken> > & vec){
        stack<double> stack;

        for( auto it : vec) {
                if( it->isNumber() ) {
                        stack.push( it->getVal() );
                }else{
                    it->performOperation(stack);
                }
        }

        return stack.top();
}

bool evaluateString(double & res, string & str, const CTable & table){
        vector<string> infix;
        vector< shared_ptr<CToken> > rpn;
        bool error = false;

        try{
                infix = stringToVec(str, table);
        }catch( const exception & excp) {
                error = true;
        }

        if( !error ) {
                try{
                        rpn = infixToRPN(infix);
                }catch(const exception & excp) {
                        error = true;
                }
        }
        if( !error ) {
                try{
                        res = evaluateRPN( rpn );
                }catch( const exception & excp) {
                        error = true;
                }
        }

        return error;
}

bool evaluateCell(double & res, const string & val, const CTable & table){
        bool NaN = false; //not a number boolean

        // if string is a number just save it in the m_result in the cell
        try{
                res = stringToDouble(val);
        }catch(invalid_argument a) {
                NaN = true;
        }
        if( !NaN ) {
                return true;
        }

        string str = val;
        //if string is Mathematical expression evaluate it value and save it to m_result in the cell
        if( isMathExprTrans(str) ) {
                bool error = evaluateString(res, str, table);

                if(!error) {
                        return true;
                }else{
                        return false;
                }

        }else{
                return false;
        }
}

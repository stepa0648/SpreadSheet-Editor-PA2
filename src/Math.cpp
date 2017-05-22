
/**
 * \file Math.cpp
 * \author severste
 *
   \brief This is the file where all functions from Math.h are inicialised

 */
#include "CTable.h"
#include "CToken.h"
#include "Math.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/**
        \brief Function findParents finds parents cell in string m_textVal in
   CCell and saves them to parent set
        @param string str, string where to find parent cells
        @param set<pair<int,int>> set, set where parent cells are saved
        @return bool, true if at least one parent was found
 */
bool findParents(const string &str, set<pair<int, int>> &set) {
  char c;
  bool found = false;

  if (str.size() != 0) {
    c = str[0];
  } else {
    return false;
  }

  int begin = 0, end = 0;
  for (size_t i = 0; i < str.size(); i++) {
    c = str[i];

    if (c == '[') {
      begin = i;
    }
    if (c == ']') {
      end = i;
      if (begin < end) {
        int y = 0, x = 0;
        if (isCell(str.substr(begin, end - begin + 1), y, x)) {
          found = true;
          set.insert(make_pair(y, x));
        }
      }
      begin = 0;
      end = 0;
    }
  }

  return found;
}

/**

        \brief Function findAncestors finds all ancestors of the cell and saves
   them to ancestors set.
        It is a recursive function that finds parents of parents etc.
        @param set<pair<int,int>>  ancestors, set where the ancestors are stored
        @param set<pair<int,int>> parents, set where parent cells are given to
   our function
        @return bool, true if at least one parent was found
 */
set<pair<int, int>> findAncestors(set<pair<int, int>> &ancestors,
                                  set<pair<int, int>> parents,
                                  const CTable &table) {

  ancestors.insert(parents.begin(), parents.end());

  if (parents.empty()) {
    return set<pair<int, int>>();
  }
  for (auto it : parents) {
    findAncestors(ancestors, table.getCellParents(it.first, it.second), table);
  }

  return ancestors;
}

/**
   \brief Checks if string is math expression and cut off the = sign from string
   @param val is the string which we want to test
   @return true if the expression starts with =
 */
bool isMathExprTrans(string &val) {
  size_t i = 0;
  char c = 0;
  c = val[i];

  while (c == ' ' || c == '\t') {
    if (i >= val.size()) {
      break;
    }
    c = val[i];
    i++;
  }

  if (c == '=') {
    // cut the = off
    string sub1;
    if (i == 0) {
      sub1 = val.substr(i + 1);
    } else {
      sub1 = val.substr(i);
    }
    val = sub1;

    // if there is not only = in the expression return true
    i++;
    while (i < val.size()) {
      c = val[i];
      if (c != ' ' && c != '\t') {
        return true;
      }
      i++;
    }
    // return false;
    return true;
  }

  return false;
}

/**
        \brief Checks if string is math expression. Same as isMathExprTrans but
   does not cut off the = sign
   @param val is the string which we want to test
   @return true if the expression starts with =
 */
bool isMathExpr(const std::string &val) {
  size_t i = 0;
  char c = 0;
  c = val[i];
  while (c == ' ' || c == '\t') {
    if (i >= val.size()) {
      break;
    }
    c = val[i];
    i++;
  }
  if (c == '=') {
    // if there is not only = in the expression return true
    i++;
    while (i < val.size()) {
      c = val[i];
      if (c != ' ' && c != '\t') {
        return true;
      }
      i++;
    }
    return false;
  }

  return false;
}

/**
   \brief Converts string to double.
   If string is NaN throw an exception invalid_argument
   @param str is the string we want to convert
   @return double value of the string
 */
double stringToDouble(const string &str) {
  double res = 0;
  size_t resLen = 0;

  res = stod(str, &resLen);

  if (resLen != str.size()) {
    throw invalid_argument("Neni cislo");
  }

  return res;
}

/**
   \brief Checks if string is an operator
   @param c is the string you want to check
   @return bool, true if string is an operator
 */
bool isOperator(const string &c) {
  return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

/**
   \brief Checks if string is a funtion
   @param c is the string you want to check
   @return bool, true if string is a function
 */
bool isFunction(const string &c) {
  return c == "sin" || c == "cos" || c == "tan" || c == "cotg" || c == "abs" ||
         c == "sqrt" || c == "exp" || c == "log" || c == "ln";
}

/**
   \brief Checks if the string is identificator of a cell in format [y;x]
   @param str is the string that we want to test
   @param y is the int where we will store the y value if the string is Cell
   @param x is the int where we will store the x value if the string is Cell
   @return bool, true if the format is right
 */
bool isCell(const string &str, int &y, int &x) {
  /* checks if the string starts with [ and ends with ]*/
  if (str[0] == '[' && str.back() == ']') {
    char c = 0;
    string substr = "";
    int i = 1;
    /* while ; is not found put char in substr*/
    c = str[i];
    while (c != ';') {
      /* ; wasnt found*/
      if ((unsigned)i >= str.size()) {
        return false;
      }
      substr += c;

      i++;
      c = str[i];
    }
    /*checks if substr is a number*/
    try {
      y = stringToDouble(substr);
    } catch (const invalid_argument &a) {
      return false;
    }

    substr = "";
    i++;
    c = str[i];
    /* while ] is not found put char in substr*/
    while (c != ']') {
      substr += c;
      i++;
      c = str[i];
    }
    /* checks if substr is a number*/
    try {
      x = stringToDouble(substr);
    } catch (const invalid_argument &a) {
      return false;
    }

    /* checks if coords are positive or 0*/
    if (y >= 0 && x >= 0) {
      return true;
    }
  }

  return false;
}

/**
  \brief If end of the string is reached push the last token to the vector and
  check if there is not any error
  @param vec is a vector where would be tokens saved
  @param substr is substring of string that we are evaluating
 */
void endOfString(vector<string> &vec, const string &substr) {
  // if you have reached the end of a string push last token into the vector
  if (substr.size() != 0) {
    vec.push_back(substr);
  }
  // if last token in string is opearator or function or left bracket throw
  // operator Error
  if (isOperator(vec.back()) || isFunction(vec[vec.size() - 1]) ||
      vec[vec.size() - 1] == "(") {
    throw OperatorError();
  }
}

/**
  \brief If char is an operator or brackets and is not first or operator is left
  bracket, insert it into a vector and previous substr as well
  @param vec is a vector where would be tokens saved
  @param substr is substring of string that we are evaluating
  @param table is table where parent cells are stored
  @param c is character on actual position
 */
void pushOperatorAndSubstr(vector<string> &vec, string &substr,
                           const CTable &table, char c) {
  if (substr.size() != 0) {
    // checks if the substr is a cell
    int x = 0, y = 0;
    if (isCell(substr, y, x)) {
      vec.push_back(to_string(table.getResCell(y, x)));
    } else {
      vec.push_back(substr);
    }
  }

  substr = c;
  vec.push_back(substr);
  substr.erase();
}

/**
  \brief Function to find errors if previous token is operators
  @param vec is a vector that is tested to be empty to find out if token is
  first
  @param c is a character on actual position in string
  @param c1 is a string that represents char c
 */
void prevIsOperator(const vector<string> &vec, char c, const string &c1) {
  // more operators in a row - error
  if (isOperator(c1)) {
    throw OperatorError();
  }

  // After operator at the beginning is not a number
  if (vec.size() == 0 && !(c >= 48 && c <= 57)) {
    throw OperatorError();
  }
}

/**
   \brief Converts string mathematical expression to vector with separated
   tokens (still strings).
   This mathematical expression can include some cells from table, and count
   with values from them
   @param str is a string which you want to convert
   @param table is a table in which you are searching for the cells
   @return vector of strings and each string represents one Token
 */
vector<string> stringToVec(const string &str, const CTable &table) {
  char c = 0;
  char prev = 0;
  vector<string> vec;
  int i = 0;
  string substr;

  while (1) {

    if (i != 0 && c != ' ' &&
        c != '\t') { // if its not the first char insert into prev the last one
      prev = c;
    }

    c = str[i]; // insert next char from str in c

    /* temporary strings - typecast from char to int for functions isOperator
     * and isFunction*/
    string c1, prev1;
    c1 = c;
    prev1 = prev;

    if (c == 0) { // if its end of string break
      endOfString(vec, substr);
      break;
    }
    if (c == ' ' || c == '\t') { // ignore whitespaces
      i++;
      continue;
    }

    // if the first char is binary operator -> error
    // Wrong operator at the beginning
    if (prev == 0 &&
        (c == '*' || c == '/' || c == ')' || c == '^' || c == '+')) {
      throw OperatorError();
    }

    // Wrong operator after left bracket
    if (prev == '(' && (c == '*' || c == '/' || c == ')' ||
                        c == '^')) { // if the next char after opening bracket
                                     // is binary operator error
      throw OperatorError();
    }

    // Wrong operator before right bracket
    if (c == ')' && (isOperator(prev1) || isFunction(prev1))) {
      throw OperatorError();
    }

    // Wrong token (number or function or bracket) before operator
    if (isOperator(c1) &&
        (!(prev >= 48 && prev <= 57) && prev != ')' && prev != ']' )) {
          //if token is - and prev char is ( for example (-10+2) - not error
      if ( !(c1 == "-" && prev == '(')) {
        throw OperatorError();
      }
    }

    if (isOperator(prev1)) {
      prevIsOperator(vec, c, c1);
    }

    /* if char is an operator or brackets and is not first or is left bracket
     * insert it into a vector and prev substr as well*/
    if (((isOperator(c1) || c1 == "(" || c1 == ")") &&
         (prev != 0 && prev != '(')) ||
        c == '(') {
      pushOperatorAndSubstr(vec, substr, table, c);
      i++;
      continue;
    }

    substr += c;
    i++;
  }

  int x = 0, y = 0;
  // if the last token in vec is cell, insert to vector its value instead
  if (isCell(vec.back(), y, x)) {
    vec.pop_back();
    vec.push_back(to_string(table.getResCell(y, x)));
  }

  return vec;
}

/**
   \brief Returns the operator precedence, the higer value has higer precedence
   @param c is the operator whose precedence you want
   @return int the value of the operator precedence
 */
int operatorPrecedence(const string &c) {
  if (c == "+" || c == "-") {
    return 1;
  }
  if (c == "*" || c == "/") {
    return 2;
  }
  if (c == "^") {
    return 3;
  }
  return 0;
}

/**
   \brief If token is operator do:
   While a operator with higer or equal precedence is on the stack, pop it to
   the output and then push operator on a stack.
   If a left bracket is on the top of the stack dont pop operators, just push
   this one on the stack
   @param out is the vector of shared pointer to CTokens
   @param stack of strings of tokens
   @param vec is a string that we are evaluating
   @param i is a position of token in vec we are evaluating
 */
void tokenIsOperator(vector<shared_ptr<CToken>> &out, stack<string> &stack,
                     const vector<string> &vec, size_t &i) {
  if (!stack.empty()) {
    /* while a operator with higer or equal precedence is on the stack, pop it
     * to the output and then push operator on a stack */
    while (operatorPrecedence(stack.top()) >= operatorPrecedence(vec[i])) {
      /* if a left bracket is on the top of the stack dont pop operators, just
       * push this one on the stack*/
      if (stack.top() == "(") {
        break;
      }
      /* push operator in the output */
      out.push_back(shared_ptr<CToken>(new COperator(stack.top())));
      stack.pop();
      if (stack.empty()) {
        break;
      }
    }
  }
  /* push operator on a stack */
  stack.push(vec[i]);
}

/**
   \brief If token is right bracket empty the stack until ( is found
   If left bracket is not found BracketsMissMatch
   @param out is the vector of shared pointer to CTokens
   @param stack of strings of tokens
 */
void tokenIsRightBr(vector<shared_ptr<CToken>> &out, stack<string> &stack) {
  while (stack.top() != "(") {
    if (stack.empty()) {
      break;
    }
    // pop the operators between brackets
    if (isFunction(stack.top())) {
      out.push_back(shared_ptr<CToken>(new CFunction(stack.top())));
      stack.pop();
    } else {
      out.push_back(shared_ptr<CToken>(new COperator(stack.top())));
      stack.pop();
    }
  }
  // if stack isnt empty, there is a left bracket - pop it out
  if (!stack.empty()) {
    stack.pop();

    // if there was a function before bracket push it in the output
    if (!stack.empty()) {
      if (isFunction(stack.top())) {
        out.push_back(shared_ptr<CToken>(new CFunction(stack.top())));
        stack.pop();
      }
    }
  } else {
    // if a left bracket wasnt in the stack the brackets were wrong
    throw BracketsMissMatch();
  }
}

/**
   \brief If you have run out of the tokens to read you need to empty the stack
   @param out is the vector of shared pointer to CTokens
   @param stack of strings of tokens
 */
void emptyTheStack(vector<shared_ptr<CToken>> &out, stack<string> &stack) {
  while (!stack.empty()) {
    // if there is a left bracket in stack, brackets were wrong
    if (stack.top() == "(") {
      throw BracketsMissMatch();
      break;
    }
    // if is an operator
    if (isFunction(stack.top())) {
      out.push_back(shared_ptr<CToken>(new CFunction(stack.top())));
      stack.pop();
      // if is an operator
    } else {
      out.push_back(shared_ptr<CToken>(new COperator(stack.top())));
      stack.pop();
    }
  }
}

/**
   \brief Converts vector of tokens(strings) in infix notation to RPN (reverse
   polish notation) vector of CTokens using shunting yard algorithm.
   @param vec is the vector of string(tokens)
   @return vector of CToknes in RPN
 */
vector<shared_ptr<CToken>> infixToRPN(const vector<string> &vec) {
  double res = 0;
  bool isNumber;
  vector<shared_ptr<CToken>> out;
  stack<string> stack;

  for (size_t i = 0; i < vec.size(); i++) {
    isNumber = true;
    /* tries to parse string to double to know if it is number or not */
    try {
      res = stringToDouble(vec[i]);
    } catch (invalid_argument a) {
      isNumber = false;
    }
    if (isNumber) {
      /* if token is a number, just push it on the output*/
      out.push_back(shared_ptr<CToken>(new CNumber(res)));
    } else if (isFunction(vec[i])) {
      /* if token is function push it on the stack*/
      stack.push(vec[i]);
    } else if (isOperator(vec[i])) {
      tokenIsOperator(out, stack, vec, i);
    } else if (vec[i] == "(") {
      /* if token is left bracket push it on the stack no matter what*/
      stack.push(vec[i]);
    } else if (vec[i] == ")") {
      /* if token is right bracket empty stack until left bracket is found
          if you empty whole stack and didnt find a left bracket, brackets were
         wrong
       */
      tokenIsRightBr(out, stack);
    } else {
      // Unknown symbol found
      throw OperatorError();
    }
  }
  /* if you have run out of the tokens you need to empty the stack*/
  emptyTheStack(out, stack);

  return out;
}

/**
   \brief Evalutes vector of CTOkens in RPN and returns double value of that
   expression
   @param vec is vector of CTokens in RPN
   @return double value of evaluated vector
 */
double evaluateRPN(const vector<shared_ptr<CToken>> &vec) {
  stack<double> stack;

  for (auto it : vec) {
    if (it->isNumber()) {
      stack.push(it->getVal());
    } else {
      it->performOperation(stack);
    }
  }

  return stack.top();
}

/**
   \brief Evalutes string where is math expression
   @param res, double where the evaluated value will be stored
   @param str is string from cell, that will be evaluated
   @param table, where cell is stored
   @return bool, true if string was evaluated
 */
bool evaluateString(double &res, string &str, const CTable &table) {
  vector<string> infix;
  vector<shared_ptr<CToken>> rpn;
  bool error = false;

  try {
    infix = stringToVec(str, table);
  } catch (const exception &excp) {
    error = true;
  }

  if (!error) {
    try {
      rpn = infixToRPN(infix);
    } catch (const exception &excp) {
      error = true;
    }
  }
  if (!error) {
    try {
      res = evaluateRPN(rpn);
    } catch (const exception &excp) {
      error = true;
    }
  }

  return error;
}

/**
   \brief Evalutes string from cell
   @param res, double where the evaluated value will be stored
   @param val is string from cell, that will be evaluated
   @param table, where cell is stored
   @return bool, true if string was evaluated
 */
bool evaluateCell(double &res, const string &val, const CTable &table) {
  bool NaN = false; // not a number boolean

  // if string is a number just save it in the m_result in the cell
  try {
    res = stringToDouble(val);
  } catch (invalid_argument a) {
    NaN = true;
  }
  if (!NaN) {
    return true;
  }

  string str = val;
  // if string is Mathematical expression evaluate it value and save it to
  // m_result in the cell
  if (isMathExprTrans(str)) {
    bool error = evaluateString(res, str, table);
    if (!error) {
      return true;
    } else {
      return false;
    }

  } else {
    return false;
  }
}

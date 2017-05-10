
#include <iostream>
#include <stack>
#include <string>
#include "CCell.h"

using namespace std;

CCell::CCell( string text = "" ) : m_textVal( text ), m_textLen( text.size( ) ), m_result( 0 ), isNumber( false ) {
  if(m_textLen > 0){
    //testovani vyznamu;
  }
}

/**
* prints the string from Cell no matter how long it is
*/
void CCell::printContent(){
  cout << m_textVal << endl;
}

/** parameter is a string in which we want to test if the brackets are right.
*  it returns false if not.
*/
bool CCell::testBrackets() const {
    string x = m_textVal;
    stack<char> s;
    char c;
    for ( size_t i = 0; i < x.size(); i++ ) {
        c = x[i];
        if ( c == '(' ) {
            s.push(c);
        } else if ( c == ')' ) {
            if ( s.empty() ) {
                return false;
            }
            if ( s.top() != '(' ) {
                return false;
            } else {
                s.pop();
            }
        }
    }
    if ( !s.empty() ) {
        return false;
    }
    return true;
}


/**
*prints the string from Cell.
*if its longer than 10 chars, it prints only 8 chars and 2x "."
*/
ostream & operator<<(ostream & out, const CCell & a){
  if ( a.isNumber ) {
      out << a.m_result;
  } else {
      if ( a.m_textLen > 10 ) {
          out << a.m_textVal.substr(0, 8).append("..");
      } else {
          out << a.m_textVal;
      }
  }
  return out;
}

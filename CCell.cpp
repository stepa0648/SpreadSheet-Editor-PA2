
#include <iostream>
#include <stack>
#include <string>
#include "CCell.h"

using namespace std;

CCell::CCell( string text = "" ) : m_textVal( text ), m_result( 0 ), isNumber( false ) {}

/**
* prints the string from Cell no matter how long it is
*/
void CCell::printContent(){
  cout << m_textVal << endl;
  cout << "Vysledek: " << m_result << endl;
}
void CCell::setRes( double res){
  m_result = res;
}
double CCell::getRes() const{
  return m_result;
}
void CCell::Number(){
  isNumber = true;
}

/**
*prints the string from Cell.
*if its longer than 10 chars, it prints only 8 chars and 2x "."
*/
ostream & operator<<(ostream & out, const CCell & a){
  if ( a.isNumber ) {
      out << a.m_result;
  } else {
      if ( a.m_textVal.size() > 10 ) {
          out << a.m_textVal.substr(0, 8).append("..");
      } else {
          out << a.m_textVal;
      }
  }
  return out;
}

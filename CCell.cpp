
#include <iostream>
#include "CCell.h"

using namespace std;


/**
* prints the string from Cell no matter how long it is
*/
void CCell::printContent(){
  cout << m_textVal << endl;
}

/**
*prints the string from Cell.
*if its longer than 10 chars, it prints only 8 chars a 2x "."
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

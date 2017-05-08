#include <iostream>
#include <cstdlib>
#include "CCell.h"

using namespace std;
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

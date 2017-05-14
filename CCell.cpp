
#include <iostream>
#include <stack>
#include <string>
#include "CCell.h"
#include "Math.h"
#include "CTable.h"

using namespace std;

CCell::CCell( string text = "" ) : m_textVal( text ){}

/**
* prints the string from Cell no matter how long it is
*/
void CCell::printContent(const CTable & table){
  cout << m_textVal << endl;
  double res = 0;
  evaluateCell(res, m_textVal, table);
  cout << "Vysledek: " << res << endl;
}


double CCell::getRes(const CTable & table) const{
  double res = 0;
  evaluateCell(res, m_textVal, table);
  return res;
}

string CCell::getText() const{
  return m_textVal;
}


/**
*prints the string from Cell.
*if its longer than 10 chars, it prints only 8 chars and 2x "."
*/
ostream & operator<<(ostream & out, const CCell & a){

      if ( a.m_textVal.size() > 10 ) {
          out << a.m_textVal.substr(0, 8).append("..");
      } else {
          out << a.m_textVal;
      }

  return out;
}

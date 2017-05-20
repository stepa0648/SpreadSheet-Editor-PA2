/**
 * \file CCell.cpp
 * \author severste
   \brief This is the file where CCell class is inicialised

 */

#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <set>

#include "CCell.h"
#include "Math.h"
#include "CTable.h"

using namespace std;

CCell::CCell( string text = "", set<pair<int,int>> parents = set<pair<int,int>>() ) : m_textVal( text ), m_parentCells(parents){
}

void CCell::printContent(const CTable & table){
        // prints the string representation of CCell
        cout << m_textVal << endl;
        double res = 0;
        // evaluates cell
        evaluateCell(res, m_textVal, table);
        cout << "Vysledek: " << res << endl;
}

void CCell::addParentCell(int y, int x){
  m_parentCells.insert( make_pair(y,x) );
}

set< pair< int, int > > CCell::retParentCells(){
  return m_parentCells;
}
// returns evaluated value of cell
double CCell::getRes(const CTable & table) const {
      double res = 0;
      // evaluates cell
        evaluateCell(res, m_textVal, table);
      return res;
}

string CCell::getText() const {
        return m_textVal;
}

ostream & operator<<(ostream & out, const CCell & a){
        // if string is longer than 10 chars it prints only 8 and two dots
        if ( a.m_textVal.size() > 10 ) {
                out << a.m_textVal.substr(0, 8).append("..");
        } else {
                out << a.m_textVal;
        }

        return out;
}

/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on 23. dubna 2017, 16:20
 */

 #include "CTable.h"
 #include "CCell.h"
 #include "CToken.h"
 #include "Math.h"

 #include <vector>
 #include <iostream>
 #include <iomanip>
 #include <string>
 #include <memory>

using namespace std;

class CCell;

//CRow==========================================================================

CRow::CRow() : width(10) {
    m_row.resize( width+1, CCell("", set<pair<int,int>>() ));
}

CCell & CRow::operator[](size_t pos){

    if ( m_row.size() <= pos ) {
        m_row.resize(2 * pos, CCell("", set<pair<int,int>>()));
    }
    return m_row[pos];
}

CCell CRow::getCell(size_t pos) const{
    return m_row.at(pos);
}

void CRow::print(size_t cnt, size_t x, const CTable & table) {
    if( x+11 >= m_row.size() ){
      m_row.resize(2 * (x+11), CCell("", set<pair<int,int>>()));
    }
    cout << setw(10) << cnt << "|"; //print number of the row in front of the row
    double res = 0;
    for (size_t i = x; i <= x+10; i++) {//prints one row of cells

        res = m_row[i].getRes(table);
        if(  res == 0 ){
            if( m_row[i].getText().size() == 0 ){
              cout << setw(10) << "" << "|";
            }else{
              cout << setw(10) << m_row[i] << "|";
            }
        }else{
          string str = to_string(res);
          if ( str.size() > 10 ) {
              cout << str.substr(0, 8).append("..") << "|";
          } else {
              cout << setw(10) << res << "|"; //print each cell 10 chars wide
          }
        }
    }
    cout << endl;
}

//CTable========================================================================

CTable::CTable() : width(10), height(10) {
    m_table.resize( 11, CRow() );
}

CCell & CTable::getCell(size_t y, size_t x) {
    //if table height is lower than y resize the table height;
    if (m_table.size() <= y) {
        m_table.resize(2 * y, CRow() );
    }

    return (m_table[y])[x];
}

set<pair<int,int>> CTable::getCellParents(size_t y, size_t x)const {
    return (m_table[y]).getCell(x).retParentCells();
}

/** returns double Value of the cell*/
double CTable::getResCell(size_t y, size_t x)const{
  return  (m_table[y]).getCell(x).getRes(*this);
}

bool findParents(const string & str, set<pair<int,int>> & set){
  char c;
  bool found = false;
	cout << str << endl;
  if( str.size() != 0 ){
    c = str[0];
  }else{
    return false;
  }
  int begin = 0, end = 0;
  for(size_t i=0; i<str.size(); i++){
			c= str[i];

			if( c == '[' ){
        begin = i;
      }
      if( c == ']'){
        end = i;
        if( begin < end ){
          int y = 0, x = 0;
          if( isCell( str.substr(begin, end), y, x )){
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
    cout << "findAncestors empty" << endl;
    return set<pair<int,int>>();
  }
  for(auto it: parents){
    findAncestors(ancestors, table.getCellParents(it.first, it.second), table);
  }

  cout << "findAncestors end" << endl;
  return ancestors;
}



/**
  inserts string val in Cell in y'th row and in x'th column
  or if it starts with = inserts number in m_result in CCell
*/
void CTable::insert(size_t y, size_t x, const string & val) {

  bool cycle = false;
  //zkontrolovat cykly
  set<pair<int,int>> parents;

  //checks the cycles only on math expressions
  if(isMathExpr(val)){

    if( findParents(val, parents) ){

      if( parents.find(make_pair(y,x)) != parents.end() ){
        cout << "Cyklus, nelze vlozit" << endl;
        cycle = true;
      }

    }

    if(!cycle){

      set<pair<int,int>> ancestors;
      ancestors = findAncestors(ancestors, parents, *this);

      cout << "Ancestors" << endl;
      for(auto it: ancestors){
        cout << it.first << ";" << it.second << endl;

      }
      //checks for cycles
      cout << "Kontroluji cykly" << endl;
      if( ancestors.find(make_pair(y,x)) != ancestors.end() ){
        cout << "Cyklus, nelze vlozit" << endl;
        cycle = true;
      }

    }
  }

  if(!cycle){
    getCell(y,x) = CCell(val, parents);

    double res = 0;
    if( evaluateCell(res, val, *this) ){
      cout << "Uspesne vlozeno jako matematicky vyraz" << endl;
    }else{
      cout << "Neni matematicky vyraz" << endl;
      cout << "Uspesne vlozeno jako text" << endl;
    }
  }
}


void CTable::print(size_t y, size_t x) {
  //if the area that we want to print is bigger than our tabel, we must resize it
  if (m_table.size() <= y+10) {
      m_table.resize(2 * (y+10), CRow() );
  }

  cout << "===============================================================================" << endl;
  cout << endl;
  cout << setw(10) << " " << "|"; //prints empty cell in left top corner

  for (size_t i = x; i <= x+10; i++) { //prints number of columns
      cout << setw(10) << i << "|";
  }
  cout << endl;

  for (size_t i = 0; i <= 11; i++) { //prints separator of number of columns
      for (int j = 0; j < 10; j++) {
          cout << "_";
      }
      cout << "|";
  }
  cout << endl;

  for (size_t i = y; i <= y+10; i++) { //prints rows
      m_table[i].print(i, x, *this);
  }
}

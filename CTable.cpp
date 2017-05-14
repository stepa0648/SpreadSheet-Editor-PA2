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


bool evaluateString(double & res , string & str, CTable & table){
      vector<string> infix;
      vector< shared_ptr<CToken> > rpn;
    	bool error = false;

      try{
      	infix = stringToVec(str, table);
      }catch( const exception & excp){
      	cerr << excp.what() << endl;
      	error = true;
      }

      if( !error ){
      	try{
      		rpn = infixToRPN(infix);
      	}catch(const exception & excp){
      		cerr << excp.what() << endl;
      		error = true;
      	}
      }
      if( !error ){
      	try{
      		res = evaluateRPN( rpn );
      	}catch( const exception & excp){
      		cerr << excp.what() << endl;
      		error = true;
      	}
      }

      return error;
}

bool evaluateCell(double & res, const string & val, CTable & table){
  bool NaN = false; //not a number boolean

  // if string is a number just save it in the m_result in the cell
  try{
    res = stringToDouble(val);
  }catch(invalid_argument a){
    NaN = true;
  }
  if( !NaN ){
    return true;
  }


  string str = val;
  //if string is Mathematical expression evaluate it value and save it to m_result in the cell
  if( isMathExpr(str) ){
    bool error = evaluateString(res, str, table);

    if(!error){
      return true;
    }else{
      return false;
    }

  }else{
    return false;
  }
}

//CRow==========================================================================

CRow::CRow() : width(10) {
    m_row.resize( width+1, CCell(""));
}

CCell & CRow::operator[](size_t pos){

    if ( m_row.size() <= pos ) {
        m_row.resize(2 * pos, CCell(""));
    }
    return m_row[pos];
}

CCell CRow::getCell(size_t pos) const{
    return m_row.at(pos);
}

void CRow::print(size_t cnt, size_t x) {
    if( x+11 >= m_row.size() ){
      m_row.resize(2 * (x+11), CCell(""));
    }
    cout << setw(10) << cnt << "|"; //print number of the row in front of the row
    for (size_t i = x; i <= x+10; i++) {
        cout << setw(10) << m_row[i] << "|";
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

/** returns double Value of the cell*/
double CTable::getResCell(size_t y, size_t x)const{
  return  (m_table[y]).getCell(x).getRes();
}

/**
  inserts string val in Cell in y'th row and in x'th column
  or if it starts with = inserts number in m_result in CCell
*/
void CTable::insert(size_t y, size_t x, const string & val) {
  getCell(y,x) = CCell(val);

  double res = 0;

  if( evaluateCell(res, val, *this) ){
    getCell(y,x).setRes(res);
    getCell(y,x).Number();
    cout << "Uspesne vlozeno jako matematicky vyraz" << endl;
  }else{
    cout << "Uspesne vlozeno jako text" << endl;
  }

  /*
  bool NaN = false; //not a number boolean
  double res = 0;

  // if string is a number just save it in the m_result in the cell
  try{
    res = stringToDouble(val);
  }catch(invalid_argument a){
    NaN = true;
  }
  if( !NaN ){
    getCell(y,x).setRes(res);
  }


  string str = val;
  //if string is Mathematical expression evaluate it value and save it to m_result in the cell
  if( isMathExpr(str) ){
    bool error = evaluateString(res, str, *this);

    if(!error){
      getCell(y,x).setRes(res);
      getCell(y,x).Number();
      cout << "Uspesne vlozeno jako matematicky vyraz" << endl;
    }else{
      cout << "Neni matematicky vyraz" << endl;
      cout << "Vlozeno jako text" << endl;
    }

  }else{
    cout << "Uspesne vlozeno" << endl;
  }

  */
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
      m_table[i].print(i, x);
  }
}

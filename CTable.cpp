/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on 23. dubna 2017, 16:20
 */
 #include <vector>
 #include <iostream>
 #include <iomanip>

 #include "CTable.h"
 #include "CCell.h"

using namespace std;

//CRow==========================================================================

CRow::CRow() : width(10) {
    m_row.resize( width+1, CCell(""));
}

CCell & CRow::operator[](size_t pos){

    if ( m_row.size() <= pos ) {
        m_row.resize(2 * pos, CCell(""));
        //cout << "m_row resized " << m_row.size() << " " << pos << endl;
    }
    return m_row[pos];
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

void CTable::insert(size_t y, size_t x, const CCell & val) {
    //if table height is lower than y resize the tabl height;
    if (m_table.size() <= y) {
        m_table.resize(2 * y, CRow() );
    }

    (m_table[y])[x] = val;
}

void CTable::print(size_t y, size_t x) {

  cout << "m_table size:  " << m_table.size() << " y+10= " << y+10 << endl;
  if (m_table.size() <= y+10) {
      m_table.resize(2 * (y+10), CRow() );
      cout << "m_table resized " << m_table.size() << " " << y << endl;
  }



    cout << setw(10) << " " << "|"; //prints empty cell in left top corner
    for (size_t i = x; i <= x+10; i++) {
        cout << setw(10) << i << "|";
    }
    cout << endl;
    for (size_t i = 0; i <= 11; i++) {
        for (int j = 0; j < 10; j++) {
            cout << "_";
        }
        cout << "|";
    }
    cout << endl;

    for (size_t i = y; i <= y+10; i++) {
        m_table[i].print(i, x);
    }
    cout << "Width: " << width << " Height: " << height << endl;
}

#ifndef CTABLE_H
#define CTABLE_H

#include <vector>
//#include <iostream>
//#include <iomanip>

#include "CCell.h"

class CRow {
public:
    CRow();
    CCell & operator[](size_t pos);
    void print(size_t cnt);
  private:
      std::vector<CCell> m_row;
      size_t width;

};

class CTable {
public:

    CTable();
    void insert(size_t y, size_t x, CCell val);
    void print();

private:
    std::vector<CRow> m_table;
    size_t width, height;
};

#endif

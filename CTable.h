#ifndef CTABLE_H
#define CTABLE_H

#include <vector>
#include <string>

#include "CCell.h"

class CTable;

class CRow {
public:
    CRow();
    CCell & operator[](size_t pos);
    CCell getCell(size_t pos) const;
    void print(size_t cnt, size_t x, const CTable & table);
  private:
      std::vector<CCell> m_row;
      size_t width;

};

class CTable {
public:

    CTable();
    CCell & getCell(size_t y, size_t x);
    void insert(size_t y, size_t x, const std::string & val);
    void print(size_t y, size_t x);
    double getResCell(size_t y, size_t x)const;

private:
    std::vector<CRow> m_table;
    size_t width, height;
};

#endif

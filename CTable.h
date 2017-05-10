#ifndef CTABLE_H
#define CTABLE_H

#include <vector>
#include <string>

#include "CCell.h"

class CRow {
public:
    CRow();
    CCell & operator[](size_t pos);
    void print(size_t cnt, size_t x);
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

private:
    std::vector<CRow> m_table;
    size_t width, height;
};

#endif

#ifndef CROW_H
#define CROW_H

#include <vector>
#include <iostream>

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

#endif

#ifndef CTABLE_H
#define CTABLE_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

#include "CRow.h"
#include "CCell.h"

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

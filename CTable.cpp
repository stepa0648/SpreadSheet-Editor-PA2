/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on 23. dubna 2017, 16:20
 */
#include "CTable.h"
#include "CRow.h"
#include "CCell.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

//CRow=================================================================

CRow::CRow() : width(0) {
    m_row.resize(2);
}

CCell & CRow::operator[](size_t pos){
    if (pos > width) {
        width = pos;
    }
    if (m_row.size() <= pos) {
        m_row.resize(2 * pos);
    }
    return m_row[pos];
}

void CRow::print(size_t cnt) {
    std::cout << std::setw(10) << cnt << "|";
    for (size_t i = 0; i <= width; i++) {
        std::cout << std::setw(10) << m_row[i] << "|";
    }
    std::cout << std::endl;
}

//CTable===============================================================

CTable::CTable() : width(0), height(0) {
    m_table.resize(2);
}

void CTable::insert(size_t y, size_t x, CCell val) {
    if (y + 1 > height) {
        height = y + 1;
    }
    if (x + 1 > width) {
        width = x + 1;
    }
    if (m_table.size() <= y) {
        m_table.resize(2 * y);
    }
    (m_table[y])[x] = val;
}

void CTable::print() {
    cout << setw(10) << " " << "|";
    for (size_t i = 0; i < width; i++) {
        cout << setw(10) << i << "|";
    }
    std::cout << std::endl;
    for (size_t i = 0; i <= width; i++) {
        for (int j = 0; j < 10; j++) {
            cout << "_";
        }
        cout << "|";
    }
    cout << endl;
    for (size_t i = 0; i < height; i++) {
        m_table[i].print(i);
    }
    cout << width << "x" << height << endl;
}

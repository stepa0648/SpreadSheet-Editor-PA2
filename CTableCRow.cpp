/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: severste
 *
 * Created on 23. dubna 2017, 16:20
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class CRow {
public:

    CRow() : width(0) {
        m_row.resize(2);
    };

    T & operator[](size_t pos) {
        if (pos > width) {
            width = pos;
        }
        if (m_row.size() <= pos) {
            m_row.resize(2 * pos);
        }
        return m_row[pos];
    }

    void print(size_t cnt) {
        cout << setw(10) << cnt << "|";
        for (size_t i = 0; i <= width; i++) {
            cout << setw(10) << m_row[i] << "|";
        }
        cout << endl;
    }
private:
    vector<T> m_row;
    size_t width;

};

template <class T>
class CTable {
public:

    CTable() : width(0), height(0) {
        m_table.resize(2);
    };

    void insert(size_t y, size_t x, T val) {
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

    void print() {
        cout << setw(10) << " " << "|";
        for (size_t i = 0; i < width; i++) {
            cout << setw(10) << i << "|";
        }
        cout << endl;
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
private:
    vector<CRow<T>> m_table;
    size_t width, height;
};

/*
 *
 */
int main(int argc, char** argv) {

    CTable<string> table;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            table.insert(i, j, "ahoj");
        }
    }
    table.insert(10, 2, "Nazdarek");
    table.insert(11, 2, "Nazdar");
    table.insert(1, 11, "2*(4+1)-sin(29");

    table.print();


    return 0;
}

/**
 * \file CTable.h
 * \author severste
   \brief This is the file where CTable and CRow classes are defined

 */

#ifndef CTABLE_H
#define CTABLE_H

#include <string>
#include <vector>

#include "CCell.h"

class CTable;

/**
  \class CRow
  \brief CRow represents one row in CTable
*/
class CRow {
public:
  /**
    Constructor of CRow, sets width to 10
  */
  CRow();
  /**
    operator [] is used to acces CCell on specific position.
    It is used to edit CCells. If cell is out of range it resizes the row
    @param size_t pos is position of CCell
    @return CCell &, reference to CCell
  */
  CCell &operator[](size_t pos);
  /**
  Method getCell is used to acces CCell on specific position.
  It is used to view CCells. It is const method
  @param size_t pos is position of CCell
  @return CCell at specific position
  */
  CCell getCell(size_t pos) const;

  /**
  Method print is used to print cells
  @param size_t rowNum represents the number of the row
  @param size_t x is the position of cell in the row
  @param CTable & table is the table where rows and cell are.
  */
  void print(size_t rowNum, size_t x, const CTable &table);

private:
  std::vector<CCell> m_row;
  size_t width;
};
/**
  \class CTable
  \brief CTable represents whole table, it contains CRows
*/
class CTable {
public:
  /**
  Constructor of CTable, width = 10, height = 10
  */
  CTable();
  /**
  Method getCell is used to acces CCell on specific position.
  @param size_t y, number of row
  @param size_t x, number of column
  @return CCell &, reference to a CCell
  */
  CCell &getCell(size_t y, size_t x);
  /**
    inserts string val in Cell in y'th row and in x'th column
    or if it starts with = checks is the string is valid math value and checks
    if there wouldn't be any cycles after insertion
  */
  void insert(size_t y, size_t x, const std::string &val);
  /**
    Method print is used to print area 10x10 from table. It is defined by top
    left corner.
    It evaluates math expressions in cells
    @param size_t y is number of column of top left corner
    @param size_t x is number of row of top left corner
  */
  void print(size_t y, size_t x);
  /**
  Method getResCell return double evaluated from CCell on specific position.
  @param size_t y, number of row
  @param size_t x, number of column
  @return double value of the cell
  */
  double getResCell(size_t y, size_t x) const;
  /**
  Method getCellParents returns set<pair<int,int>> of parents of cell
  @param size_t y, number of row of the cell
  @param size_t x, number of column of column of the cell
  @return set<pair<int,int>> of parents of cell
  */
  std::set<std::pair<int, int>> getCellParents(size_t y, size_t x) const;

private:
  std::vector<CRow> m_table;
  size_t width, height;
};

#endif

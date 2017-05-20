/**
 * \file CCell.h
 * \author severste
   \brief This is the file where CCell class is defined

 */
#ifndef CCELL_H
#define CCELL_H

#include <iostream>
#include <string>
#include <set>
#include <utility>

class CTable;

/**
  \class CCell
  \brief Class that represents one cell int the spreadsheet
  Every cell has string value m_textVal that represents its content
  and every cell knows its own parents. Parents are stored in set of pairs of ints.
  The pair represents parent coordinates in CTable
*/
class CCell {
public:
  /**
    Constructor of CCell
    @param string text,
  */
  CCell( std::string text, std::set<std::pair<int,int>> parents);

  /**
    Prints the string from Cell no matter how long it is and print double
    value if there was mathematical expression stored in that cell
    @param CTable table is table where cell is stored
   */
  void printContent(const CTable & table);
  /**
    Counts the double value of cell and returns it
    @param CTable table is table where cell is stored
    @return double val stored in cell
  */
  double getRes(const CTable & table) const;
  /**
  Returns the string representation (m_textVal) from cell
  @param CTable table is table where cell is stored
  @return string representation of the cell
  */
  std::string getText() const;

/**
  Adds pair of int to parents of this cell
  @param int y is the row number where parent is
  @param int x is the column number where parent is
*/
  void addParentCell(int y, int x);

  /**
    Return set of parent cell represented by pair of int coords
    @return set<pair<int,int>> of parents coords
  */
  std::set< std::pair< int, int > > retParentCells();

  /**
     prints the string from Cell.
     if its longer than 10 chars, it prints only 8 chars and 2x "."
   */
  friend std::ostream & operator << (std::ostream & out, const CCell & a);

private:
  std::string m_textVal; /** string m_textVal represantation of cell*/
  std::set< std::pair< int, int > > m_parentCells; /** set<pair<int,int>> of parents coords*/
};

#endif

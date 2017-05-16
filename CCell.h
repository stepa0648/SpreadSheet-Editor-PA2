#ifndef CCELL_H
#define CCELL_H

#include <iostream>
#include <string>
#include <set>
#include <utility>

class CTable;

class CCell {
public:

  CCell( std::string text, std::set<std::pair<int,int>> parents);

  void printContent(const CTable & table);
  double getRes(const CTable & table) const;
  std::string getText() const;

  void addParentCell(int y, int x);

  std::set< std::pair< int, int > > retParentCells();

  friend std::ostream & operator << (std::ostream & out, const CCell & a);

private:
  std::string m_textVal;
  std::set< std::pair< int, int > > m_parentCells;
};

#endif

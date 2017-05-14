#ifndef CCELL_H
#define CCELL_H

#include <iostream>
#include <string>

class CTable;

class CCell {
public:

    CCell( std::string text);

    void printContent(const CTable & table);
    double getRes(const CTable & table) const;
    std::string getText() const;

    friend std::ostream & operator << (std::ostream & out, const CCell & a);

private:
    std::string m_textVal;
};

#endif

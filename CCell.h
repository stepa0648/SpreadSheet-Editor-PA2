#ifndef CCELL_H
#define CCELL_H

#include <iostream>
#include <string>


class CCell {
public:

    CCell( std::string text = "" ) : m_textVal( text ), m_textLen( text.size( ) ), m_result( 0 ), isNumber( false ) {
    }

    void printContent();

    friend std::ostream & operator << (std::ostream & out, const CCell & a);

private:
    std::string m_textVal;
    size_t m_textLen;
    double m_result;
    bool isNumber;
};

#endif

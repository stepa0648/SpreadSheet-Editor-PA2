#ifndef CCELL_H
#define CCELL_H

#include <iostream>
#include <string>


class CCell {
public:

    CCell( std::string text);

    void printContent();
    void setRes(double res);
    double getRes() const;
    void Number();

    friend std::ostream & operator << (std::ostream & out, const CCell & a);

private:
    std::string m_textVal;
    double m_result;
    bool isNumber;
};

#endif

/*
 * File:   CMenu.h
 * Author: severste
 *
 * Created on April 12, 2017, 7:46 PM
 */

#ifndef CMENU_H
#define CMENU_H

class CMenu {
public:
    CMenu();
    CMenu(const CMenu& orig);
    virtual ~CMenu();
    void print();
    int run();
private:


};

#endif /* CMENU_H */

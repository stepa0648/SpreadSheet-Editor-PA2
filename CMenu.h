/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    void run();
private:
    

};

#endif /* CMENU_H */


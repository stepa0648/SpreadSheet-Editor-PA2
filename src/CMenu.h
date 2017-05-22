/**
 * \file CMenu.h
 * \author severste
   \brief This is the file where CMenu class is inicialised

 */

#ifndef CMENU_H
#define CMENU_H

/**
  \Class CMenu
  \brief is used to print header and to handle user input in menu
  it also prints help whenever user inputs 'h' key
*/
class CMenu {
public:
  /**
    Constructor of class CMenu
  */
  CMenu();

  /**
    Method printHelp is used to print help whenever user inputs 'h'
  */
  void printHelp() const;

  /**
    Method printHeader is used to print header when the program starts
  */
  void printHeader() const;

  /**
    Method printMenu is used to print menu options when the program starts
  */
  void printMenu() const;

  /**
    Method getInput is used to get input from user in menu
  */
  int getInput() const;
};

#endif /* CMENU_H */

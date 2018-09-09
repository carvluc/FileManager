#ifndef SO_FINAL_VIRTUALHD_H
#define SO_FINAL_VIRTUALHD_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include "Manager.h"

using namespace std;

class VirtualHD : public Manager {
public:
    string HDname;
    int qtdB;
    int sizeB;

    void initialize();
    void openHD();
    void actions(fstream &);
    void createHD();
    const string& getHDname();
    const int getQtdB();
    const int getSizeB();
    void setHDname(const string&) ;
    void setQtdB(int) ;
    void setSizeB(int);
    void format();
    void createFile(fstream &);
};

#endif //SO_FINAL_VIRTUALHD_H



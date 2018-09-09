#ifndef SO_FINAL_MANAGER_H
#define SO_FINAL_MANAGER_H

#include <map>

using namespace std;

class VirtualHD;

class Manager {
public:
    map <string, VirtualHD> HDS;
    map <string, VirtualHD>::iterator it;
    string path = "# ";
    int qtdHDS;

    void mLoadHD();
    void printHDS();
    void mWriteHD();
    bool validateHD(VirtualHD);
    bool searchHD(string);
    void setPath(string);
    string getPath();
    void changePath(string, bool);
    void changeHD(string);
    void format(string);
};

#endif //SO_FINAL_MANAGER_H




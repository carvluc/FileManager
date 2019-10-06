#ifndef SO_FINAL_MANAGER_H
#define SO_FINAL_MANAGER_H

#include <map>

using namespace std;

class VirtualHD;

class Manager {
public:
    map <string, VirtualHD> HDS;
    map <string, VirtualHD>::iterator it;
    string path = "#",
            replace = {17};
    int qtdHDS;

    void loadHD();
    void unloadHD();
    void writeHD();
    void formatHD(string);
    void removeHD();
    bool validateHD(VirtualHD);
    bool searchHD(string);
    void statusHD();
    void printHDS();
    void setPath(string);
    string getPath();
    void resetPath();
    void changeHD(string);
    void addPath(string);
    void removePath();
    void help();
    string regexFunction(string target, string replacement, string value);
};

#endif //SO_FINAL_MANAGER_H




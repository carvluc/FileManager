#ifndef SO_FINAL_VIRTUALHD_H
#define SO_FINAL_VIRTUALHD_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>

#include "Manager.h"
#include "Block.h"
#define ULONG unsigned long

using namespace std;

class VirtualHD : public Manager {
public:
    map <string, Block> blocks;
    map <string, Block>::iterator it;
    string HDname,
            currentPathAdr,
            replace = {17};
    int qtdB,
        sizeB;

    void actions(fstream &);
    void openHD();
    void loadBlocks(fstream&);
    void saveHD(fstream& fs);
    void createHD();
    void viewHD();
    void sizeHD();
    void printTypeHDHex(int, map <string, Block>::iterator);
    void setParameters();
    void initialize(fstream &);
    const string& getHDname();
    const int getQtdB();
    const int getSizeB();
    void setHDname(const string&) ;
    void setQtdB(int) ;
    void setSizeB(int);
    string binaryConvertITS(int);
    int binaryConvertSTI(string);
    string stringToHex(string& input);
    void goBackToRoot();
    const vector<string> split(const string&, const char&);
    void openFolder();
    void viewFolder();
    void createFolder();
    void exitFolder();
    void renameFolder();
    void viewFile();
    void createFile();
    void createFileComplete(string, string, string);
    void renameFile();
    void moveFile();
    void copyFile();
    void createContent(string, string);
    void resetBlock();
    void copyFolder();
    void copyFolderComplete(string, string);
    void resetFolder();
    void resetFolderComplete(string posFolder);
    string findEmptyBlock();
    string findFileContent(string name);
    string findFile(string name);
    string findFolder(string name);
    void intToHex(int);
    void help();
};

#endif //SO_FINAL_VIRTUALHD_H



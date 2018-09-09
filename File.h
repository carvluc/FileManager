//
// Created by Lucas Henrique on 09/09/2018.
//

#ifndef SO_FINAL_FILE_H
#define SO_FINAL_FILE_H
#include <bitset>
#include <iostream>

using namespace std;

class File {
public:
    unsigned char flag;
    string folderDadAdr;
    string fileAdr;
    string fileName;


    std::string binary = std::bitset<16>(128).to_string(); //to binary
    std::cout<<binary<<"\n";

    unsigned long decimal = std::bitset<16>(binary).to_ulong();
    std::cout<<decimal<<"\n";

};


#endif //SO_FINAL_FILE_H


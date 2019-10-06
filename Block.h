#ifndef SO_FINAL_BLOCK_H
#define SO_FINAL_BLOCK_H

#include <stdio.h>
#include <string>

using namespace std;

class Block{
public:
    unsigned char flag;
    string blockAdrActual,
            blockAdrDad,
            blockAdrContent,
            blockName;
    Block();
    Block(unsigned char, string, string, string); //pasta + conteudo
    Block(unsigned char, string, string, string, string); //arquivo
};

#endif //SO_FINAL_BLOCK_H

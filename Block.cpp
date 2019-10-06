#include <stdio.h>
#include <string>

#include "Block.h"

using namespace std;

//padrão
Block::Block(){}

//pasta + conteudo
Block::Block(unsigned char flag, string blockAdrActual, string blockAdrDad, string blockinfo):
    flag(flag),
    blockAdrActual(blockAdrActual),
    blockAdrDad(blockAdrDad),
    blockName(blockinfo){}

//arquivo
Block::Block(unsigned char flag, string blockAdrActual, string blockAdrDad,string blockName, string blockAdrContent):
    flag(flag),
    blockAdrActual(blockAdrActual),
    blockAdrDad(blockAdrDad),
    blockName(blockName),
    blockAdrContent(blockAdrContent){}


#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <string>

#include "Manager.h"
#include "VirtualHD.h"

using namespace std;

void Manager::loadHD(){
    fstream fs;
    VirtualHD temp;
    fs.open("HardDriveManager.txt", fstream::in);
    while(fs >> temp.HDname >> temp.sizeB >> temp.qtdB)
        HDS[temp.HDname] = temp;

    fs.close();

    qtdHDS = HDS.size();
}

void Manager::help(){
    fstream fs;
    string f, ds;
    fs.open("HelpHD.txt", fstream::in);
    fs.seekg (0, fs.end);
    int length = fs.tellg();
    fs.seekg (0, fs.beg);
    char* buffer = new char [length];
    fs.read(buffer, length);
    cout << buffer << endl;
    fs.close();
    delete[] buffer;
}

void Manager::unloadHD() {
    fstream fs;
    VirtualHD temp;
    fs.open("HardDriveManager.txt", fstream::out);

    for (it = HDS.begin(); it != HDS.end(); ++it)
        fs << it->second.HDname << " " << it->second.sizeB << " " << it->second.qtdB << endl;

    fs.close();
}

void Manager::removeHD() {
    string name;
    cin >> name;
    if(searchHD(name)){
        remove((name + ".txt").c_str());
        HDS.erase(HDS.find(name));
        unloadHD();
    } else  {
        cout << "HD nao localizado!" << endl;
    }
}

void Manager::formatHD(string name) {
    if(searchHD(name)){
        fstream fs;
        fs.open(name+".txt", fstream::out| fstream::trunc);
        HDS[name].initialize(fs);
        fs.close();
    }else
        cout << "Nao foi possivel formatar o HD, pois ele nao existe" << endl;
}

void Manager::printHDS(){
    cout << setw(20) << "HD_NAME" << setw(20) << "TAM_BLOCK" << setw(20) << "QTD_BLOCK" << endl;
    for (it = HDS.begin(); it != HDS.end(); ++it)
        cout << setw(20) << it->second.HDname <<
             setw(20) << it->second.sizeB <<
             setw(20) << it->second.qtdB << endl;
}

void Manager::writeHD(){
    fstream fs;
    VirtualHD newhd;
    newhd.setParameters();
    if(validateHD(newhd)){
        HDS[newhd.getHDname()] = newhd;
        newhd.createHD();

        fs.open("HardDriveManager.txt", fstream::out);

        for (it = HDS.begin(); it != HDS.end(); ++it)
            fs << it->second.HDname << " " << it->second.sizeB << " " << it->second.qtdB << endl;

        fs.close();

        qtdHDS = HDS.size();
        cout << qtdHDS << " HDs writed with success" << endl;
    }
}

bool Manager::validateHD(VirtualHD temp){
    if(temp.getHDname().find(":") != string::npos){
        cout << "Nome invalido, tente outro nome" << endl;
        return false;
    }

    if(searchHD(temp.getHDname())){
        cout << "Ja existe um HD com este nome, tente outro" << endl;
        return false;
    }

    if(temp.getSizeB() > 128 || temp.getQtdB() > 10000 ){
        cout << "HD muito grande, diminua os parametros" << endl;
        return false;
    }

    if(temp.getSizeB() < 16 || temp.getQtdB() < 10){
        cout << "HD muito pequeno, aumente os parametros" << endl;
        return false;
    }

    return true;
}

bool Manager::searchHD(string hdSearch){
    auto exist = HDS.find(hdSearch);
    if(exist == HDS.end())
        return false;

    return true;
}

void Manager::statusHD(){
    string name;
    cin >> name;
    if(searchHD(name)){
        fstream in;
        in.open(name + ".txt", fstream::in);
        HDS[name].loadBlocks(in);
        HDS[name].sizeHD();
        in.close();
    } else  {
        cout << "HD nao localizado!" << endl;
    }
}

void Manager::setPath(string path){
    this->path = path;
}

string Manager::getPath(){
    return this->path;
}

void Manager::addPath(string path){
    this->path += path + ">";
}

void Manager::resetPath(){
    setPath("#");
}

void Manager::removePath(){
    int countChr = count(path.begin(), path.end(), '>');
    if (countChr < 2)
        cout << "Voce ja esta na raiz do hd, para sair digite exit" << endl;
    else{
        int pos = path.size()-2;
        while(path[pos] != '>'){
            pos--;
        }
        setPath(path.substr(0, pos + 1));
    }
}

string Manager::regexFunction(string target, string replacement, string value){
    auto target_ = regex(target);
    return regex_replace(value, target_, replacement);
}
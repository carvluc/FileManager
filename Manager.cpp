#include "Manager.h"
#include "VirtualHD.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void Manager::mLoadHD(){
    ifstream fs;
    VirtualHD temp;
    cout << "reading HDS ..." << endl << endl;
    fs.open("HardDriveManager.txt", ios::in);
    while(fs >> temp.HDname >> temp.sizeB >> temp.qtdB)
        HDS[temp.HDname] = temp;

    fs.close();

    qtdHDS = HDS.size();
    cout << qtdHDS << " HDs read with success" << endl;
}

void Manager::printHDS(){
    for (it = HDS.begin(); it != HDS.end(); ++it)
        cout << setw(20) << it->second.HDname <<
             setw(20) << it->second.sizeB <<
             setw(20) << it->second.qtdB << endl;
}

void Manager::mWriteHD(){
    ofstream fs;
    VirtualHD newhd;
    newhd.initialize();
    if(validateHD(newhd)){
        HDS[newhd.getHDname()] = newhd;
        newhd.createHD();
        //HDS.push_back(newhd);

        fs.open("HardDriveManager.txt", ios::out);
        cout << "------------writing HDS----------" << endl << endl;

        for (it = HDS.begin(); it != HDS.end(); ++it) {
            cout << "name: " << it->second.HDname << endl;
            cout << "size_b: " << it->second.sizeB << endl;
            cout << "qtd_b: " << it->second.qtdB << endl << endl;

            fs << it->second.HDname + " " << it->second.sizeB << " " << it->second.qtdB << "\n";
        }

        fs.close();

        qtdHDS = HDS.size();
        cout << qtdHDS << " HDs writed with success" << endl;
    }
}

bool Manager::validateHD(VirtualHD temp){

    cout<<"nome do hd : "<<temp.getHDname()<<endl;

    if(temp.getHDname().find(":") != string::npos){
        cout<<"Nome invalido, tente outro nome\n";
        return false;
    }

    if(searchHD(temp.getHDname())){
        cout<<"Ja existe um HD com este nome, tente outro\n";
        return false;
    }

    if(temp.getSizeB() > 128 || temp.getQtdB() > 10000 ){
        cout<<"HD muito grande, diminua os parametros\n";
        return false;
    }

    if(temp.getSizeB() < 8 || temp.getQtdB() < 10){
        cout<<"HD muito pequeno, aumente os parametros\n";
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

void Manager::setPath(string path){
    this->path = path;
}

string Manager::getPath(){
    return this->path;
}

void Manager::changePath(string path, bool reset){
    if(reset)
        setPath("# ");
    else
        this->path += path + "> ";
}

void Manager::changeHD(string path){
    setPath("# "+path+">");
}

void Manager::format(string name) {
    if(searchHD(name)){
        fstream fs;
        fs.open(name+".txt", fstream::out| fstream::trunc);
        fs.close();
    }else
        cout<< "Nao foi possivel formatar o HD, pois nao existe"<<endl;
}
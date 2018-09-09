#include "VirtualHD.h"
#include "Manager.h"

void VirtualHD::initialize(){
    cout << "Creating HD, please insert the infos: " << endl;
    cin >> HDname;
    cin >> sizeB;
    cin >> qtdB;
}

void VirtualHD::openHD(){
    fstream fs;
    fs.open(HDname+".txt", fstream::in | fstream::out | fstream::app);
    Manager::changeHD(HDname);
    actions(fs);
    fs.close();
}





void VirtualHD::actions(fstream & fs) {
    string option,arqName,dirName;

    do{
        cout<<Manager::getPath();
        cin>>option;
        if(option == "create"){
            cin >> arqName;
            fs << arqName << endl;
            //createFile(fs);
        }
    }while(option != "exit");

}

void createFile(fstream &fs){
    /*while(cin>>input){

    }*/
}
void VirtualHD::createHD(){
    ofstream fs;
    fs.open(HDname+".txt", fstream::in | fstream::out | fstream::app);
    fs << HDname << sizeB << endl;
    fs.close();
}

const string& VirtualHD::getHDname(){
    return HDname;
}

const int VirtualHD::getQtdB(){
    return qtdB;
}

const int VirtualHD::getSizeB(){
    return sizeB;
}

void VirtualHD::setHDname(const string &HDname) {
    VirtualHD::HDname = HDname;
}

void VirtualHD::setQtdB(int qtdB) {
    VirtualHD::qtdB = qtdB;
}

void VirtualHD::setSizeB(int sizeB) {
    VirtualHD::sizeB = sizeB;
}

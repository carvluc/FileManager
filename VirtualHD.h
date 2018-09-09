#include "Manager.h"
#ifndef SISTEMAS_OPERACIONAIS_VIRTUALHD_H
#define SISTEMAS_OPERACIONAIS_VIRTUALHD_H

#endif //SISTEMAS_OPERACIONAIS_VIRTUALHD_H

class VirtualHD : public Manager{
public:
    string HDname;
    int qtdB;
    int sizeB;

    void initialize(){
        cout << "Creating HD, please insert the infos: " << endl;
        cin >> HDname;
        cin >> sizeB;
        cin >> qtdB;
    }

    void openHD(){
        fstream fs;
        fs.open(HDname+".txt", fstream::in | fstream::out | fstream::app);
        actions(fs);
        fs.close();
    }

    void actions(fstream & a) {
        string opcao;

        do{
            cout<<Manager::getPath();
            cin>>opcao;
            if(opcao == "create"){
                a << "teste";
            }
        }while(opcao != "exit");

    }

    void createHD(){
        ofstream fs;
        fs.open(HDname+".txt", fstream::in | fstream::out | fstream::app);
        fs << HDname << sizeB << endl;
        fs.close();
    }

    const string &getHDname() const {
        return HDname;
    }

    int getQtdB() const {
        return qtdB;
    }

    int getSizeB() const {
        return sizeB;
    }

    void setHDname(const string &HDname) {
        VirtualHD::HDname = HDname;
    }

    void setQtdB(int qtdB) {
        VirtualHD::qtdB = qtdB;
    }

    void setSizeB(int sizeB) {
        VirtualHD::sizeB = sizeB;
    }
    bool validateHDName(){
    }
};

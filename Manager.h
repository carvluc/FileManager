#include "VirtualHD.h"
#include <fstream>
#ifndef SISTEMAS_OPERACIONAIS_MANAGER_H
#define SISTEMAS_OPERACIONAIS_MANAGER_H

#endif //SISTEMAS_OPERACIONAIS_MANAGER_H

usinfjfhsjhdjkhfs
#include <fstream>
class Manager {
public:
    map <string,VirtualHD> HDS;
    map<string,VirtualHD>::iterator it;
    string path = "# ";
    int qtdHDS;

    void mLoadHD(){
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

    void printHDS(){
        for (it = HDS.begin(); it != HDS.end(); ++it)
            cout << setw(20) << it->second.HDname <<
                 setw(20) << it->second.sizeB <<
                 setw(20) << it->second.qtdB << endl;
    }

    void mWriteHD(){
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

    bool validateHD(VirtualHD temp){

        cout<<"nome do hd : "<<temp.getHDname()<<endl;

        if(temp.getHDname().find(":") != string::npos){
            cout<<"Nome invalido, tente outro nome\n";
            return false;
        }

        if(searchHd(temp.getHDname())){
            cout<<"Ja existe um HD com este nome, tente outro\n";
            return false;
        }

        return true;
    }

    bool searchHd(string hdSearch){
        auto exist = HDS.find(hdSearch);
        if(exist == HDS.end())
            return false;

        return true;
    }

    void setPath(string path){
        this->path = path;
    }

    string getPath(){
        return this->path;
    }

    void changePath(string path, bool reset){
        if(reset)
            setPath("# ");
        else
            this->path += path + "> ";
    }
    void changeHD(string path){
        setPath("# "+path+">");
    }

};



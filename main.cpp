#include <stdlib.h>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string.h>
#include <regex>
using namespace std;

//region Comments
/*1 bloco - 32 bytes
1 carac = 1byte, então cada bloco vai ter 32 zeros.
arquivo de 1MB = 1024/32 = 32blocos*/
//endregion

//region Types

typedef void(*PointerFunction);

//endregion

//region Classes

class VirtualHD {
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
        ofstream fs;
        fs.open(HDname+".txt", ios::in | ios::out);
        actions(fs);
        //fs >> HDname;

        fs.close();
    }

    void closeHD(){

    }

    void actions(ofstream & a) {
        string opcao;
        do{
            cin>>opcao;

           if(opcao == "create"){
                a << "teste";
           }


        }while(opcao != "exit");

    }

    void createHD(){
        ofstream fs;
        fs.open(HDname+".txt", ios::out);
        fs << HDname << sizeB;
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
//endregion

class Manager{
public:
    //vector <VirtualHD> HDS;
    //vector<VirtualHD>::iterator it;
    map <string,VirtualHD> HDS;
    map<string,VirtualHD>::iterator it;


    string path = "# ";
    int qtdHDS;
    void mLoadHD(){
        ifstream fs;
        VirtualHD temp;
        cout << "reading HDS ..." << endl << endl;
        fs.open("HardDriveManager.txt", ios::in);
        while(fs >> temp.HDname >> temp.sizeB >> temp.qtdB){
            HDS[temp.HDname] = temp;
            //HDS.push_back(temp);
        }

        //fs.read((char*)&temp, sizeof(temp));
        //HDS.push_back(temp);
        fs.close();

        qtdHDS = HDS.size();
        cout << qtdHDS << " HDs read with success" << endl;
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
        /*
        for(it = HDS.begin(); it != HDS.end(); ++it) {
            if(it->HDname == hdSearch)
                return true;
        }*/
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


//region Static Methods

// endregion

//region Main



int main() {


    Manager manageHDS;
    manageHDS.mLoadHD();

    VirtualHD newhd;

    cout << "qtd de hds: " << manageHDS.HDS.size() << endl;
    string opcao;


    do {

        //smatch strMatch;
        //regex regexVar(":");

        cout << manageHDS.getPath();
        cin >> opcao;
        //regex_search(opcao, strMatch, regexVar);
        //opcoes digitados pelo usuario
        if (opcao == "createhd") {
            manageHDS.mWriteHD();
        } else if (opcao.find(":") != string::npos) {
            string hdSearch = "";
            hdSearch = opcao.replace(opcao.size()-1,1,"");
            if (manageHDS.searchHd(hdSearch)) {
                manageHDS.changeHD(hdSearch);
                newhd.openHD();
            }else
                cout<<"HD não existente\n";
        }

        }while(opcao != "exit");

    }

// endregion
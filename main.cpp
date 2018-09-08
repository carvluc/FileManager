#include <stdlib.h>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>

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
        cin >> qtdB;
        cin >> sizeB;
    }
};
//endregion

class Manager{
public:
    vector <VirtualHD> HDS;
    int qtdHDS;
    void loadHD(){
        ifstream fs;
        VirtualHD temp;
        cout << "reading HDS ..." << endl << endl;
        fs.open("HardDriveManager.txt", ios::in);
        while(fs >> temp.HDname >> temp.qtdB >> temp.sizeB){
            HDS.push_back(temp);
        }

        //fs.read((char*)&temp, sizeof(temp));
        //HDS.push_back(temp);
        fs.close();

        qtdHDS = HDS.size();
        cout << qtdHDS << " HDs read with success" << endl;
    }
    void writeHD(VirtualHD newhd){
        ofstream fs;
        HDS.push_back(newhd);
        fs.open("HardDriveManager.txt", ios::out);
        cout << "------------writing HDS----------" << endl << endl;
        for(vector<VirtualHD>::iterator it = HDS.begin(); it != HDS.end(); ++it) {
            cout << "name: " << it->HDname << endl;
            cout << "size_b: " << it->sizeB << endl;
            cout << "qtd_b: " << it->qtdB << endl << endl;

            fs << it->HDname + " " << it->sizeB << " " << it->qtdB << "\n";
        }

        fs.close();
        qtdHDS = HDS.size();
        cout << qtdHDS << " HDs writed with success" << endl;
    }
};


//region Static Methods

// endregion

//region Main



int main() {
    Manager manageHDS;
    manageHDS.loadHD();
    VirtualHD newhd;
    newhd.initialize();
    manageHDS.writeHD(newhd);
    cout << "qtd de hds: " << manageHDS.HDS.size() << endl;
    for(vector<VirtualHD>::iterator it = manageHDS.HDS.begin(); it != manageHDS.HDS.end(); ++it) {
        cout << "name: " << it->HDname << endl;
        cout << "size_b: " << it->sizeB << endl;
        cout << "qtd_b: " << it->qtdB << endl << endl;
    }

    /*
    cin >> input;
    if(input == "createhd"){
        VirtualHD* newhd = new VirtualHD();
        HDS.push_back(newhd);
    }
     */

    //alo teste de commit
    /*
    while (cin >> selecthd) {
        if (selecthd == "createhd") {

        } else {
            if (encontrou) {
                while (cin >> input) {


                    if (input == "createhd") {

                    } else {
                        options.find(input)->second();
                    }
                }
            } else {
                printf("Comando não é válido");
            }

        }
        //openFile();
        system("pause");

        return 0;
    }
     */
}
// endregion
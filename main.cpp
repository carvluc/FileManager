#include <stdlib.h>
#include <iostream>

#include "Manager.h"
#include "VirtualHD.h"

using namespace std;

int main() {
    Manager manageHDS;
    string option,
            name;

    manageHDS.loadHD();

    do {
        cout << manageHDS.getPath();
        cin >> option;
        if (option == "createhd") {
            manageHDS.writeHD();
        } else if (option.find(":") != string::npos) {
            string hdSearch;
            hdSearch = option.replace(option.size()-1,1,"");
            if (manageHDS.searchHD(hdSearch)) {
                manageHDS.HDS[hdSearch].openHD();
            }else
                cout << "HD nao existente" << endl;
        }else if(option == "formathd"){
            cin >> name;
            cin.get();
            manageHDS.formatHD(name);
        }else if(option == "dirhd"){
            manageHDS.printHDS();
        }else if(option == "removehd") {
            manageHDS.removeHD();
        }else if(option == "statushd"){
            manageHDS.statusHD();
        }else if(option == "?" || option == "help"){
            manageHDS.help();
        }else if(option != "exit"){
            cout << "Comando nao existente!" << endl;
        }
    }while(option != "exit");
}
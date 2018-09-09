#include <stdlib.h>
#include <iostream>
#include <map>
#include <iomanip>
#include "Manager.h"
#include "VirtualHD.h"

using namespace std;

int main() {
    Manager manageHDS;
    string option, name;

    manageHDS.mLoadHD();

    cout << "qtd de hds: " << manageHDS.HDS.size() << endl;

    do {
        cout << manageHDS.getPath();
        cin >> option;
        if (option == "createhd") {
            manageHDS.mWriteHD();
        } else if (option.find(":") != string::npos) {
            string hdSearch;
            hdSearch = option.replace(option.size()-1,1,"");
            if (manageHDS.searchHD(hdSearch)) {
                manageHDS.HDS[hdSearch].openHD();
            }else
                cout<<"HD não existente\n";
        }else if(option == "formathd"){
            cin>>name;
            manageHDS.format(name);

        }else if(option == "dirhd"){
            manageHDS.printHDS();
        }
    }while(option != "exit");
}

// endregion
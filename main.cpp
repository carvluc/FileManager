#include <stdlib.h>
#include <iostream>
#include <map>

#include <regex>
#include <iomanip>

using namespace std;

//region Classe


//endregion



//region Static Methods

// endregion

//region Main

int main() {
    Manager manageHDS;
    string option, name;

    manageHDS.mLoadHD();

    cout << "qtd de hds: " << manageHDS.HDS.size() << endl;

    do {
        cout << manageHDS.getPath();
        cin >> option;
        //regex_search(opcao, strMatch, regexVar);
        //opcoes digitados pelo usuario
        if (option == "createhd") {
            manageHDS.mWriteHD();
        } else if (option.find(":") != string::npos) {
            string hdSearch;
            hdSearch = option.replace(option.size()-1,1,"");
            if (manageHDS.searchHd(hdSearch)) {
                manageHDS.changeHD(hdSearch);
                manageHDS.HDS[hdSearch].openHD();
            }else
                cout<<"HD não existente\n";
        }else if(option == "formathd"){
            cin>>name;

        }else if(option == "dirhd"){
            manageHDS.printHDS();
        }
    }while(option != "exit");
}

// endregion
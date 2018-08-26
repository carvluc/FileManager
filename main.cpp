#include <stdlib.h>
#include <iostream>
#include <map>
#include <fstream>

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
    string nameHD;
    int num;
    double tam;

    void openFile() {
        try {
            ofstream fs;
            fs.open("HardDrive.txt", fstream::out);
            string formathd = "";
            fs.write("Lucas", sizeof("Lucas"));
            fs.close();
        }
        catch (exception ex) {

        }
    }

    VirtualHD() {
        VirtualHD hd;
        cin >> hd.nameHD;
        cin >> hd.tam;
        cin >> hd.num;
        openFile();
    }
};
//endregion

//region Static Methods

void teste() {
    cout << "funciona\n";
}


void inserirAcaoMenu(map<string, PointerFunction>& options) {
    //options["createhd"] = &createVirtualHD;

}
// endregion

//region Main

int main() {
    map<string, PointerFunction> options;
    inserirAcaoMenu(options);

    string selecthd, input;
    //alterando para efetivar na master
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

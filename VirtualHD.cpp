#include <bitset>
#include <map>
#include <cmath>
#include <string>
#include <vector>

#include "VirtualHD.h"

#define BLOCKSIZE_A 7
#define BLOCKSIZE_C 5
#define BLOCKSIZE_P 5
#define END_OF_CONTENT 65535
#define ULONG unsigned long

using namespace std;

void VirtualHD::actions(fstream& fs) {
    string option;
    loadBlocks(fs);
    do{
        cout << Manager::getPath();
        cin >> option;
        cin.get();
        if(option == "create"){
            createFile();
        }else if(option == "createdir") {
            createFolder();
        }else if(option == "cd"){
            openFolder();
        }else if(option == "cd.."){
            exitFolder();
        }else if(option == "cd\\") {
            goBackToRoot();
        }else if(option == "type"){
            viewFile();
        }else if(option == "typehd") {
            viewHD();
        }else if(option == "dir"){
            viewFolder();
        }else if(option == "remove"){
            resetBlock();
        }else if(option == "removedir"){
            resetFolder();
        }else if(option == "rename"){
            renameFile();
        }else if(option == "renamedir"){
            renameFolder();
        }else if(option == "?" || option == "help"){
            help();
        }else if(option == "move"){
            moveFile();
        }else if(option == "copy") {
            copyFile();
        }else if(option == "copydir"){
            copyFolder();
        }else if(option == "exit"){
            cout << "Saindo do HD!" << endl;
        }else
            cout << "Comando nao existente" << endl;

    }while(option != "exit");

    Manager::resetPath();
}

//region HDFunctions

void VirtualHD::sizeHD(){
    int totalSize = qtdB * sizeB;
    int totalEmpty = 0;
    int countEmpty = 0;
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'V')
            countEmpty++;
    totalEmpty = countEmpty * sizeB;
    cout << "Quantidade de Blocos: " << qtdB << " und." << endl;
    cout << "Tamanho do Bloco: " << sizeB << " bytes." << endl;
    cout << totalEmpty << " bytes livres de " << totalSize << " bytes totais" << endl;
}

void VirtualHD::openHD(){
    fstream in,
            out;
    Manager::addPath(HDname);
    currentPathAdr = binaryConvertITS(0);
    in.open(HDname + ".txt", fstream::in);
    actions(in);
    in.close();
    out.open(HDname + ".txt", fstream::out);
    saveHD(out);
    out.close();
}

void VirtualHD::loadBlocks(fstream& fs){
    unsigned char flag;
    string blockAdrActual,
            blockAdrDad,
            blockAdrContent,
            blockInfo;

    while (fs >> flag){
        switch(flag){
            case 'V': {
                fs >> blockAdrActual >> blockAdrDad >> blockInfo >> blockAdrContent;
                Block block(flag, blockAdrActual, blockAdrDad, blockInfo, blockAdrContent);
                blocks[blockAdrActual] = block;
                break;
            }
            case 'P':{
                fs >> blockAdrActual >> blockAdrDad >> blockInfo;
                blockInfo = Manager::regexFunction(replace, " ", blockInfo);
                Block block(flag, blockAdrActual, blockAdrDad, blockInfo);
                blocks[blockAdrActual] = block;
                break;
            }
            case 'A':{
                fs >> blockAdrActual >> blockAdrDad >> blockInfo >> blockAdrContent;
                blockInfo = Manager::regexFunction(replace, " ", blockInfo);
                Block block(flag, blockAdrActual, blockAdrDad, blockInfo, blockAdrContent);
                blocks[blockAdrActual] = block;
                break;
            }
            case 'C':{
                fs >> blockAdrActual >> blockAdrDad >> blockInfo;
                blockInfo = Manager::regexFunction(replace, " ", blockInfo);
                Block block(flag, blockAdrActual, blockAdrDad, blockInfo);
                blocks[blockAdrActual] = block;
            }
        }
    }
}

void VirtualHD::intToHex(int a) {
    string A = to_string(a);

    for (int i = 0; i < A.size(); i++) {
        string temp = A.substr(i, 1);
        string hexa = stringToHex(temp);
        cout << hexa << " ";
    }
}

void VirtualHD::printTypeHDHex(int flag, map <string, Block>::iterator a){
    intToHex(binaryConvertSTI(a->second.blockAdrActual));
    printf("%x ", flag);
    intToHex(binaryConvertSTI(a->second.blockAdrDad));
    cout << stringToHex(a->second.blockName) << " ";

    if(flag == 'A')
        intToHex(binaryConvertSTI(it->second.blockAdrContent));

    cout << endl << endl;
}

void VirtualHD::viewHD() {
    for(it = blocks.begin(); it != blocks.end(); ++it){
        if(it->second.flag != 'V'){
            if(it->second.flag == 'P'){
                cout << binaryConvertSTI(it->second.blockAdrActual) << " " << (char)it->second.flag << " " <<  binaryConvertSTI(it->second.blockAdrDad) << " " << it->second.blockName << endl;
                printTypeHDHex(80, it);
            }
            else if(it->second.flag == 'C'){

                cout <<  binaryConvertSTI(it->second.blockAdrActual) << " " << (char)it->second.flag << " " <<  it->second.blockAdrDad << " " << it->second.blockName << endl;
                printTypeHDHex(67, it);
            }
            else if(it->second.flag == 'A'){

                cout <<  binaryConvertSTI(it->second.blockAdrActual) << " " << (char)it->second.flag  << " " <<  binaryConvertSTI(it->second.blockAdrDad) << " " << it->second.blockName << " " <<  binaryConvertSTI(it->second.blockAdrContent) << endl;
                printTypeHDHex(65, it);
            }
        }
    }
}

void VirtualHD::saveHD(fstream& fs){
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'P' || it->second.flag == 'C')
            fs << it->second.flag << " " << it->second.blockAdrActual << " " << it->second.blockAdrDad << " " << Manager::regexFunction(" ", replace, it->second.blockName) << endl;
        else if(it->second.flag == 'V' || it->second.flag == 'A')
            fs << it->second.flag << " " << it->second.blockAdrActual << " " << it->second.blockAdrDad << " " << Manager::regexFunction(" ", replace, it->second.blockName) << " " << Manager::regexFunction(" ", replace, it->second.blockAdrContent) << endl;
}

void VirtualHD::createHD(){
    fstream fs;
    fs.open(HDname + ".txt", fstream::out);
    initialize(fs);
    fs.close();
}

void VirtualHD::setParameters(){
    cin >> HDname >> sizeB >> qtdB;
}

void VirtualHD::initialize(fstream& fs) {
    int i;
    string addressIni = binaryConvertITS(0);
    currentPathAdr = addressIni;
    fs << "P" << " " << addressIni << " " << addressIni << " " << "ROOT" << "\n";
    for(i = 1; i < qtdB; i++){
        string address = binaryConvertITS(i);
        fs << "V" << " " << address << " " << addressIni << " " << "#" << " " << addressIni << "\n";
    }
}

void VirtualHD::goBackToRoot() {
    currentPathAdr = binaryConvertITS(0);
    Manager::resetPath();
    Manager::addPath(HDname);
}

const vector<string> VirtualHD::split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for (auto n:s)
        if (n != c)
            buff += n;
        else if (n == c && !buff.empty()){
            v.push_back(buff);
            buff = "";
        }

    if (!buff.empty())
        v.push_back(buff);

    return v;
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
    this->HDname = HDname;
}

void VirtualHD::setQtdB(int qtdB) {
    this->qtdB = qtdB;
}

void VirtualHD::setSizeB(int sizeB) {
    this->sizeB = sizeB;
}

void VirtualHD::help(){
    fstream fs;
    string f, ds;
    fs.open("HelpFile.txt", fstream::in);
    fs.seekg (0, fs.end);
    int length = fs.tellg();
    fs.seekg (0, fs.beg);
    char* buffer = new char [length];
    fs.read(buffer, length);
    cout << buffer << endl;
    fs.close();
    delete[] buffer;
}

//endregion

//region BinaryFunctions

string VirtualHD::binaryConvertITS(int number){
    return bitset<16>(number).to_string();
}

int VirtualHD::binaryConvertSTI(string str){
    int res = bitset<16>(str).to_ulong();
    return res;
}

string VirtualHD::stringToHex(string& input)
{
    char lut[] = "0123456789ABCDEF";
    size_t len = input.length();
    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

//endregion

//region FolderFunctions

void VirtualHD::openFolder() {
    string folderName,
            pos;
    getline(cin, folderName);
    pos = findFolder(folderName);
    if(pos.empty())
        cout << "Pasta nao existe!" << endl;
    else{
        currentPathAdr = pos;
        Manager::addPath(folderName);
    }
}

void VirtualHD::viewFolder() {
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag != 'V' && it->second.blockAdrDad == currentPathAdr)
            cout << it->second.flag << " " << it->second.blockName << endl;
}

void VirtualHD::createFolder(){
    string folderName, nextBlock, exists;
    getline(cin, folderName);
    exists = findFolder(folderName);
    if(exists.empty()){
        nextBlock = findEmptyBlock();
        if(!nextBlock.empty()){
            blocks[nextBlock].flag = 'P';
            blocks[nextBlock].blockAdrDad = currentPathAdr;

            //validate if the folderName has a acceptable size
            if(folderName.size() > sizeB - BLOCKSIZE_P)
                folderName = folderName.substr(0, sizeB - BLOCKSIZE_P);

            blocks[nextBlock].blockName = folderName;
        }else
            cout << "HD cheio !!!" << endl;
    }else
        cout << "Pasta ja existente" << endl;
}

void VirtualHD::renameFolder(){
    string oldName,
            newName,
            pos;
    getline(cin, oldName);
    getline(cin, newName);
    pos = findFolder(oldName);
    if(!pos.empty())
        blocks[pos].blockName = newName;
}

void VirtualHD::exitFolder() {
    Manager::removePath();
    currentPathAdr = blocks[currentPathAdr].blockAdrDad;
}

void VirtualHD::copyFolder(){
    string nameFolder, posFolderIni, posFolderEnd, path, tempPath;
    getline(cin, nameFolder);
    cin >> path;

    //encontra pasta que será movida
    posFolderIni = findFolder(nameFolder);

    //verifica se o caminho existe
    vector<string> newPath = split(path, '\\');
    vector<string>::iterator itPath;
    tempPath = currentPathAdr;
    currentPathAdr = binaryConvertITS(0);
    for(itPath = newPath.begin() ; itPath != newPath.end() && !(findFolder(*itPath)).empty(); ++itPath)
        currentPathAdr = findFolder(*itPath);

    if(itPath != newPath.end())
        cout << "Destino não encontrado" << endl;
    else{
        if(posFolderIni.empty())
            cout << "Pasta nao existe, verifique os parametros" << endl;
        else{
            copyFolderComplete(posFolderIni, currentPathAdr);
            for(it = blocks.begin(); it != blocks.end(); ++it)
                if(it->second.flag == 'P' && it->second.blockAdrDad == posFolderIni)
                    copyFolderComplete(it->second.blockAdrActual, posFolderIni);
        }
    }
    currentPathAdr = tempPath;
}

void VirtualHD::copyFolderComplete(string posFolder, string dadFolder) {
    string nextBlock = findEmptyBlock();
    if(blocks[posFolder].flag == 'P'){
        if(!nextBlock.empty()){
            blocks[nextBlock].flag = 'P';
            blocks[nextBlock].blockAdrDad = dadFolder;
            blocks[nextBlock].blockName = blocks[posFolder].blockName;

            for(it = blocks.begin(); it != blocks.end(); ++it)
                if(it->second.flag == 'P' && it->second.blockAdrDad == posFolder)
                    copyFolderComplete(it->second.blockAdrActual, blocks[nextBlock].blockAdrActual);
        }else
            cout << "HD cheio !!!" << endl;
    }else if(blocks[posFolder].flag == 'A'){

    }else{

    }

    //Tem arquivos
//    for(it = blocks.begin(); it != blocks.end(); ++it)
//        if(it->second.flag == 'A' && it->second.blockAdrDad == posFolder){
//            createFileComplete();
//
//            string posArq = it->second.blockAdrActual;
//            while(posArq != binaryConvertITS(END_OF_CONTENT)){
//                string dad, child;
//                blocks[posArq].blockName = "#";
//                if(blocks[posArq].flag == 'A'){
//                    blocks[posArq].blockAdrDad = binaryConvertITS(0);
//                    dad = blocks[posArq].blockAdrContent;
//                    blocks[posArq].blockAdrContent = binaryConvertITS(0);
//                    blocks[posArq].flag = 'V';
//                    posArq = dad;
//                }else{
//                    child = blocks[posArq].blockAdrDad;
//                    blocks[posArq].blockAdrDad = binaryConvertITS(0);
//                    blocks[posArq].blockAdrContent = binaryConvertITS(0);
//                    blocks[posArq].flag = 'V';
//                    posArq = child;
//                }
//            }
//        }
}

void VirtualHD::resetFolder(){
    string nameFolder, pos;
    cin >> nameFolder;
    pos = findFolder(nameFolder);
    if(pos.empty())
        cout << "Pasta nao existe, verifique os parametros" << endl;
    else{
        resetFolderComplete(pos);
        for(it = blocks.begin(); it != blocks.end(); ++it)
            if(it->second.flag == 'P' && it->second.blockAdrDad == pos)
                resetFolderComplete(it->second.blockAdrActual);
    }

}

void VirtualHD::resetFolderComplete(string posFolder) {
    blocks[posFolder].flag = 'V';
    blocks[posFolder].blockName = '#';
    blocks[posFolder].blockAdrDad = binaryConvertITS(0);
    blocks[posFolder].blockAdrContent = binaryConvertITS(0);

    //Tem arquivos
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'A' && it->second.blockAdrDad == posFolder){
            string posArq = it->second.blockAdrActual;
            while(posArq != binaryConvertITS(END_OF_CONTENT)){
                string dad, child;
                blocks[posArq].blockName = "#";
                if(blocks[posArq].flag == 'A'){
                    blocks[posArq].blockAdrDad = binaryConvertITS(0);
                    dad = blocks[posArq].blockAdrContent;
                    blocks[posArq].blockAdrContent = binaryConvertITS(0);
                    blocks[posArq].flag = 'V';
                    posArq = dad;
                }else{
                    child = blocks[posArq].blockAdrDad;
                    blocks[posArq].blockAdrDad = binaryConvertITS(0);
                    blocks[posArq].blockAdrContent = binaryConvertITS(0);
                    blocks[posArq].flag = 'V';
                    posArq = child;
                }
            }
        }

     //Tem sub pastas
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'P' && it->second.blockAdrDad == posFolder)
            resetFolderComplete(it->second.blockAdrActual);
}

//endregion

//region FileFunctions

void VirtualHD::viewFile(){
    string fileName,
            pos;
    getline(cin, fileName);
    pos = findFileContent(fileName);
    if(pos.empty())
        cout << "Arquivo nao existe, verifique os parametros" << endl;
    else{
        while(pos != binaryConvertITS(END_OF_CONTENT)){
            cout << blocks[pos].blockName;
            pos = blocks[pos].blockAdrDad;
        }
        cout << endl;
    }
}

void VirtualHD::createFile(){
    string fileName,
            exists,
            nextBlock,
            content;
    getline(cin, fileName);
    exists = findFileContent(fileName);
    if(exists.empty()){
        nextBlock = findEmptyBlock();
        if(!nextBlock.empty()){
            getline(cin, content);
            createFileComplete(nextBlock, fileName, content);
        }else
            cout << "HD cheio !!!" << endl;
    }else
        cout << "Arquivo ja existente" << endl;
}


void VirtualHD::createFileComplete(string block, string fileName, string content){
    string nextBlockContent;
    blocks[block].flag = 'A';
    blocks[block].blockAdrDad = currentPathAdr;

    //validate if fileName has a acceptable size
    if(fileName.size() > sizeB - BLOCKSIZE_A)
        fileName = fileName.substr(0, sizeB - BLOCKSIZE_A);

    blocks[block].blockName = fileName;

    nextBlockContent = findEmptyBlock();

    if(!nextBlockContent.empty()){
        blocks[block].blockAdrContent = nextBlockContent;
        createContent(content, nextBlockContent);
    }else
        cout << "HD cheio !!!" << endl;
}

void VirtualHD::createContent(string content, string nextBlockContent){
    string prevBlockContent = nextBlockContent;
    int size = sizeB - BLOCKSIZE_C;
    int qtdBlocks = ceil(content.size() / (double)size);
    int start = 0,
            end = size;
    blocks[nextBlockContent].flag = 'C';
    string temp = content.substr(start, size);
    blocks[nextBlockContent].blockName = temp;

    for(int i = 1; i < qtdBlocks; i++){
        nextBlockContent = findEmptyBlock();
        if(!nextBlockContent.empty()) {
            blocks[nextBlockContent].flag = 'C';
            blocks[prevBlockContent].blockAdrDad = nextBlockContent;
            start += size;
            end += size;
            temp = content.substr(start, size);
            blocks[nextBlockContent].blockName = temp;
        }else
            cout << "HD cheio - atencao, o arquivo foi parcialmente gravado" << endl;

        prevBlockContent = nextBlockContent;
    }
    blocks[prevBlockContent].blockAdrDad = binaryConvertITS(END_OF_CONTENT);
}

void VirtualHD::renameFile(){
    string oldName,
            newName,
            pos;
    getline (cin, oldName);
    getline (cin, newName);
    pos = findFile(oldName);
    if(!pos.empty())
        blocks[pos].blockName = newName;
}

void VirtualHD::resetBlock() {
    string name,
            pos;
    cin >> name;
    pos = findFile(name);
    if(pos.empty())
        cout << "Arquivo nao existe, verifique os parametros" << endl;
    else{
        while(pos != binaryConvertITS(END_OF_CONTENT)){
            string dad, child;
            blocks[pos].blockName = "#";
            if(blocks[pos].flag == 'A'){
                blocks[pos].blockAdrDad = binaryConvertITS(0);
                dad = blocks[pos].blockAdrContent;
                blocks[pos].blockAdrContent = binaryConvertITS(0);
                blocks[pos].flag = 'V';
                pos = dad;
            }else{
                child = blocks[pos].blockAdrDad;
                blocks[pos].blockAdrDad = binaryConvertITS(0);
                blocks[pos].blockAdrContent = binaryConvertITS(0);
                blocks[pos].flag = 'V';
                pos = child;
            }
        }

        cout << "Arquivo " << name << " removido com sucesso" << endl;
    }
}

void VirtualHD::moveFile() {
    string fileName,
            pos,
            destiny,
            tempPath;
    getline(cin, fileName);
    getline(cin, destiny);
    pos = findFile(fileName);
    if(pos.empty())
        cout << "Arquivo nao existe, verifique os parametros" << endl;
    else{
        vector<string> path = split(destiny, '\\');
        vector<string>::iterator itPath;
        tempPath = currentPathAdr;
        currentPathAdr = binaryConvertITS(0);
        for(itPath = path.begin() ; itPath != path.end() && !(findFolder(*itPath)).empty(); ++itPath)
            currentPathAdr = findFolder(*itPath);

        if(itPath == path.end())
            blocks[pos].blockAdrDad = currentPathAdr;
        else
            cout << "Destino não encontrado" << endl;

        currentPathAdr = tempPath;
    }
}

void VirtualHD::copyFile(){
    string fileName,
            pos,
            destiny,
            tempPath,
            newContent = "",
            newBlock;
    getline(cin, fileName);
    getline(cin, destiny);
    pos = findFileContent(fileName);

    if (pos.empty()) {
        cout << "Arquivo nao existe, verifique os parametros" << endl;
    } else {
        vector<string> path = split(destiny, '\\');
        vector<string>::iterator itPath;
        tempPath = currentPathAdr;
        currentPathAdr = binaryConvertITS(0);
        for(itPath = path.begin() ; itPath != path.end() && !(findFolder(*itPath)).empty(); ++itPath)
            currentPathAdr = findFolder(*itPath);

        if(itPath == path.end()){
            while(pos != binaryConvertITS(END_OF_CONTENT)){
                newContent += blocks[pos].blockName;
                pos = blocks[pos].blockAdrDad;
            }

            newBlock = findEmptyBlock();

            if(!newBlock.empty())
                createFileComplete(newBlock, fileName, newContent);
            else
                cout << "HD cheio !!!" << endl;
        } else
            cout << "Destino não encontrado" << endl;

        currentPathAdr = tempPath;
    }
}

//endregion

//region SearchFunctions

string VirtualHD::findEmptyBlock(){
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'V')
            return it->second.blockAdrActual;

    return "";
}

string VirtualHD::findFileContent(string name){
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'A' && it->second.blockName == name && it->second.blockAdrDad == currentPathAdr)
            return it->second.blockAdrContent;

     return "";
}

string VirtualHD::findFolder(string name){
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'P' && it->second.blockName == name && it->second.blockAdrDad == currentPathAdr)
            return it->second.blockAdrActual;

    return "";
}

string VirtualHD::findFile(string name){
    for(it = blocks.begin(); it != blocks.end(); ++it)
        if(it->second.flag == 'A' && it->second.blockName == name && it->second.blockAdrDad == currentPathAdr)
            return it->second.blockAdrActual;

    return "";
}
//endregion

#include "Path.h"

void Path::add(string str){
    caminhos.push_back(str);
}

void Path::print(){

    for(list<string>::iterator it = caminhos.begin() ; it != caminhos.end() ;it++){
        cout << *it;
    }
    cout << endl;
}

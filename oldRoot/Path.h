#ifndef PATH_H
#define PATH_H

#include "VisitTree.h"
#include "Configuracao.h"

// #include <string>
// #include <list>

// #include <iostream>
// #include <set>
// #include "Estado.h"
// #include "Formula.h"
// #include <vector>
// #include <map>
// #include <sstream>

class Path{

private:

    list<string> caminhos;

public:

    void add(string str){
        caminhos.push_back(str);
    }

    void print(){

        for(list<string>::iterator it = caminhos.begin() ; it != caminhos.end() ;it++){
            cout << *it;
        }
        cout << endl;
    }

};

#endif

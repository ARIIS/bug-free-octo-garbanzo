#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <list>

#include "arena/Estado.h"

using namespace std;

namespace ConstantConectivo{
enum Conectivo {
    C_AX,
    C_EX,
    C_OR,
    C_AND,
    C_NOT,
    C_MAXPT,
    C_MINPT,
    C_NONE
};
}

using namespace ConstantConectivo;


class Formula {
public:
    virtual string toStr(){
        return "afv";
    }

    virtual list<Formula*> getFilhos () {
        return *(new list<Formula*>);

    }

};

#endif

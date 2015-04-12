#ifndef FORMULAVARIAVEL_H
#define FORMULAVARIAVEL_H

#include "Estado.h"
#include "Formula.h"

class FormulaVariavel : public Formula {
public:
    FormulaVariavel(string value);
    string getValue();
    string toStr();
    list<Formula*> getFilhos ();

private:

    string value;

};

#endif

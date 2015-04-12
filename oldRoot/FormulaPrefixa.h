#ifndef FORMULAPREFIXA_H
#define FORMULAPREFIXA_H

#include "Formula.h"

class FormulaPrefixa : public Formula {
private:
    Conectivo conectivo;
    Formula *subFormula;

public:
    FormulaPrefixa(Conectivo conectivo, Formula *subFormula);
    Conectivo getConectivo();
    Formula* getSubformula();
    virtual string toStr();
    list<Formula*> getFilhos ();

};

#endif

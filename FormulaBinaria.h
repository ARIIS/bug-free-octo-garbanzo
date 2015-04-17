#ifndef FORMULABINARIA_H
#define FORMULABINARIA_H

#include "Formula.h"

class FormulaBinaria : public Formula {
private:
    Conectivo conectivo;
    Formula *subFormulaDir;
    Formula *subFormulaEsq;

public:
    FormulaBinaria(Conectivo conectivo, Formula *subFormulaDir, Formula *subFormulaEsq);
    Conectivo getConectivo();
    Formula *getSubformulaDir();
    Formula *getSubformulaEsq();
    string toStr();
    list<Formula*> getFilhos ();

};

#endif

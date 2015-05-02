// #include "Formula.h"
// #include <iostream>
// #include <typeinfo>

#include "FormulaBinaria.h"

FormulaBinaria::FormulaBinaria(Conectivo conectivo, Formula *subFormulaDir, Formula *subFormulaEsq){
    this->conectivo = conectivo;
    this->subFormulaDir = subFormulaDir;
    this->subFormulaEsq = subFormulaEsq;
}
string FormulaBinaria::toStr(){
    string ret = "";
    switch  (this->getConectivo()){
        case C_AND:
                ret = "AND";
                break;
        case C_OR :
               ret = "OR";
               break;
    }
    return ret;
}

Conectivo FormulaBinaria::getConectivo(){
    return this->conectivo;
}

Formula* FormulaBinaria::getSubformulaDir(){
    return this->subFormulaDir;
}

Formula* FormulaBinaria::getSubformulaEsq(){
    return this->subFormulaEsq;
}

list<Formula*> FormulaBinaria::getFilhos(){
    list<Formula*> *forms = new list<Formula*>;
    forms->push_front((this->subFormulaEsq));
    forms->push_front((this->subFormulaDir));
    return *forms;
}

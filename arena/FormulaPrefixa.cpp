#include "FormulaPrefixa.h"

FormulaPrefixa::FormulaPrefixa(Conectivo conectivo, Formula *subFormula) {
    this->conectivo = conectivo;
    this->subFormula = subFormula;
}

string FormulaPrefixa::toStr(){
    string ret = "";
    switch  (this->getConectivo()){
        case C_AX:
                ret = "AX";
                break;
        case C_EX :
               ret = "EX";
               break;
        case C_NOT :
            ret = "NOT";
            break;
        case C_MAXPT:
            ret = "MAXPT";
            break;
        case C_MINPT:
            ret = "MINPT";
            break;

    }
    return ret;
}

Conectivo FormulaPrefixa::getConectivo(){
    return this->conectivo;
}

Formula* FormulaPrefixa::getSubformula(){
    return this->subFormula;
}

list<Formula*> FormulaPrefixa::getFilhos(){
    list<Formula*> *forms = new list<Formula*>;
    forms->push_front((this->subFormula));
    return *forms;
}

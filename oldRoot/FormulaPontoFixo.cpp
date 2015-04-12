#include "FormulaPontoFixo.h"

FormulaPontoFixo::FormulaPontoFixo(Conectivo conectivo, Formula *subFormula, string variavel)
                                : FormulaPrefixa(conectivo,  subFormula) {
    this->variavel = variavel;
}

string FormulaPontoFixo::getVariavel(){
    return this->variavel;
}

string FormulaPontoFixo::toStr(){
    string ret = "";
    switch  (this->getConectivo()){
        case C_MINPT:
                ret = "MINPT";
                break;
        case C_MAXPT:
               ret = "MAXPT";
               break;

    }
    return ret + " " + this->getVariavel();
}

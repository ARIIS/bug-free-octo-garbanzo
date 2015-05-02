#ifndef FORMULAPONTOFIXO_H
#define FORMULAPONTOFIXO_H

#include "Formula.h"
#include "FormulaPrefixa.h"

class FormulaPontoFixo : public FormulaPrefixa {
private:
    string variavel;

public:
    FormulaPontoFixo(Conectivo conectivo, Formula *subFormula, string variavel);

    string getVariavel();
    string toStr();


};

#endif

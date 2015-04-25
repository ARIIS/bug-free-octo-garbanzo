#ifndef FORMULALITERAL_H
#define FORMULALITERAL_H value

#include "Formula.h"

class FormulaLiteral : public Formula {
public:
    FormulaLiteral(string literal, bool valorLogico);
    literalNegativo getLiteral();
    string toStr();
    list<Formula*> getFilhos ();

private:

    literalNegativo literal;

};

#endif

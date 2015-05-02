#include "FormulaLiteral.h"

FormulaLiteral::FormulaLiteral(string literal, bool valorLogico) {
    this->literal = *(new literalNegativo);
    this->literal.literal = literal;
    this->literal.valorLogico = valorLogico;

}

literalNegativo FormulaLiteral::getLiteral() {
    return this->literal;
}

string FormulaLiteral::toStr() {
    return  (this->literal.valorLogico ? " " : "NOT ") + this->getLiteral().literal  ;
}

list<Formula*> FormulaLiteral::getFilhos(){
    return *(new list<Formula*>) ;
}

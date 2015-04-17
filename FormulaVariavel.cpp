#include "FormulaVariavel.h"

FormulaVariavel::FormulaVariavel(string value){
    this->value = value;
}

string FormulaVariavel::getValue(){
    return this->value;
}

string FormulaVariavel::toStr(){
    return this->getValue();
}

list<Formula*> FormulaVariavel::getFilhos(){
    return *(new list<Formula*>) ;
}

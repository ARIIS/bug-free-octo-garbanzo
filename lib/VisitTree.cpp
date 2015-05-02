#include <sstream>

#include "VisitTree.h"

VisitTree::VisitTree(Formula* form, int numtab){
    this->numTab = numtab;
    this->form = form;
}

void VisitTree::visit(){
    for(int i = 0 ; i < numTab ; i++){
        cout << "    ";
    }
    cout << this->form->toStr() << endl;
  //  numTab++;
    list<Formula*> filhos = this->form->getFilhos();
    for(list<Formula*>::iterator it = filhos.begin() ; it != filhos.end() ; it++){
        //int temp = numTab;
        //numTab = temp;
        VisitTree *t = new VisitTree(*it, numTab + 1);
        t->visit();
    }
}

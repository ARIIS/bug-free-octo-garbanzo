#include "VertexWitness.h"

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition){
    this->setHead(head);
        if (head->getJogador() == PARATODO){
            this->setKind(ABELARDO);
        } else {
            this->setKind(EVA);
        }
    this->tail = tail;
    this->transition = transition;

}

Change* VertexWitness::getChange(){
    return this->mychange;
}

void VertexWitness::insertChange(Change* c){
    this->mychange = c;
}

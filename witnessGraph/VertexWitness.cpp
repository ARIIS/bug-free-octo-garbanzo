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

bool VertexWitness::isWitness(){
    return true;
}

Configuracao* VertexWitness::getTail(){
    return tail;
}

TipoTransicao VertexWitness::getTransition(){
    return transition;
}

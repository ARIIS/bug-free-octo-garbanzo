#include "../refineGame/VertexWitness.h"

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


revision VertexWitness::getRevision() {
    revision out = *(new revision);

    Conectivo con1 = this->getHead()->getConectivo();
    Conectivo con2 = this->getTail()->getConectivo();
    TipoTransicao type = this->getTransition();

    change ch;

    if (con1 == C_OR || con1 == C_AND) {
        ch.type = 1;
        ch.state1 = this->getTail()->getNumEstado();
        ch.state2 = -1;
        ch.lit = this->getTail()->getLiteralNegativo();

        out.push_back(ch);
    } else if (con1 == C_EX) {
        if (type == MAY) {
            ch.type = 3;
            ch.state1 = this->getHead()->getNumEstado();
            ch.state2 = this->getTail()->getNumEstado();
            out.push_back(ch);
        }
        if (con2 == C_NONE && this->getTail()->getCor() == C_INDEF) {
            ch.type = 1;
            ch.state1 = this->getTail()->getNumEstado();
            ch.state2 = -1;
            ch.lit = this->getTail()->getLiteralNegativo();
            out.push_back(ch);
        }
    }


    return out;
}

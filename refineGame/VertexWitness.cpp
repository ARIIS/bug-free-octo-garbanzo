#include "../refineGame/VertexWitness.h"
#include "RefineGame.h"

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition){
    this->setHead(head);
        if (head->getJogador() == PARATODO){
            this->setKind(ABELARDO);
        } else {
            this->setKind(EVA);
        }
    this->tail = tail;
    this->transition = transition;
    this->duplicated = false;

}

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition, list<TestemunhaDeFalha> w){
    this->duplicated = false;
    this->setHead(head);
        if (head->getJogador() == PARATODO){
            this->setKind(ABELARDO);
            if (head->getConectivo() == C_AX) {
            for (list<TestemunhaDeFalha>::iterator it = w.begin(); it != w.end(); it++) {
                if ((*it).isDuplicated) {
                    this->duplicated = true;
                }
            }
        }
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

bool VertexWitness::isDuplicated(){
    return this->duplicated;
}


revision VertexWitness::getRevision(bool dupli) {
    revision out = *(new revision);

    Conectivo con1 = this->getHead()->getConectivo();
    Conectivo con2 = this->getTail()->getConectivo();
    TipoTransicao type = this->getTransition();

    change ch;

    if (!dupli || con1 == C_AX) {
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
        } else if (con1 == C_AX) {
            if (type == MAY) {
                if (dupli) {
                    ch.type = 5;
                    ch.state1 = this->getHead()->getNumEstado();
                    ch.state2 = this->getTail()->getNumEstado();
                    out.push_back(ch);
                } else {
                    if (con2 == C_NONE && this->getTail()->getCor() == C_INDEF) {
                        ch.type = 1;
                        ch.state1 = this->getTail()->getNumEstado();
                        ch.state2 = -1;
                        ch.lit = this->getTail()->getLiteralNegativo();
                        out.push_back(ch);

                    }
                }
            } else {
                if (con2 == C_NONE && this->getTail()->getCor() == C_INDEF && !dupli) {
                    ch.type = 1;
                    ch.state1 = this->getTail()->getNumEstado();
                    ch.state2 = -1;
                    ch.lit = this->getTail()->getLiteralNegativo();
                    out.push_back(ch);
                }
            }
        }
    }

    return out;
}

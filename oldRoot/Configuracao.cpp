#include "Configuracao.h"
#include "VisitTree.h"
#include <typeinfo>
#include <vector>
#include "Estado.h"
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <list>

Conectivo Configuracao::getConectivo() {
    return this->conectivo;
}

Cor Configuracao::getCor() {
    return this->cor;
}

Jogador Configuracao::getJogador() {
    return this->jogador;
}

void Configuracao::setJogador(Jogador jog){
    this->jogador = jog;
}

Configuracao::Configuracao(literalNegativo literal, int numEstado, int numeroNome) {
    this->numConfigsColoridas = 0;
    this->parents = *(new list<Configuracao*>);
    this->conectivo = C_NONE;
    this->numeroNome = numeroNome;
    this->jogador = EXISTE;
    this->cor = C_UNCOLORED;
    this->literal = literal;
    this->numeroNome = numeroNome;
    this->numEstado = numEstado;
    this->filhos = *(new list<Configuracao::TransicaoConfig>);
    this->numeroComponente = 0;
}

Configuracao::Configuracao(Conectivo conectivo, int numEstado, int numeroNome) {
    this->numConfigsColoridas = 0;
    this->parents = *(new list<Configuracao*>);
    this->conectivo = conectivo;
    this->numeroNome = numeroNome;
    this->numEstado = numEstado;
    this->numeroComponente = 0;
    this->filhos = *(new list<Configuracao::TransicaoConfig>);
    switch (conectivo) {
        case C_AND: this->jogador = PARATODO;

            break;
        case C_AX: this->jogador = PARATODO;
            break;
        case C_MINPT:
            this->jogador = PARATODO;
            break;
        case C_EX:
            this->jogador = EXISTE;

            break;
        case C_OR: this->jogador = EXISTE;
            break;
        case C_MAXPT: this->jogador = EXISTE;
            break;

        default: this->jogador = EXISTE;

    }

    this->cor = C_UNCOLORED;
}

void Configuracao::addParent(Configuracao* parent) {
    this->parents.push_back(parent);
}

list<Configuracao*> Configuracao::getParents() {
    return this->parents;
}

void Configuracao::setCor(Cor cor) {
    if (this->cor == C_UNCOLORED && cor != C_UNCOLORED) {

    } else if (this->cor != C_UNCOLORED && cor == C_UNCOLORED) {

    }

    this->cor = cor;
}

void Configuracao::addFilho(Configuracao* filho) {
    this->addFilho(filho, false);
}

void Configuracao::addFilho(Configuracao* filho, bool transicaoIsMust) {
    Configuracao::TransicaoConfig trc = *(new Configuracao::TransicaoConfig);
    trc.destino = filho;
    trc.isMust = transicaoIsMust;
    this->filhos.push_back(trc);
}

int Configuracao::getNumNome() {
    return this->numeroNome;
}

list<Configuracao::TransicaoConfig> Configuracao::getFilhos() {
    return this->filhos;
}

int Configuracao::getNumComponente() {
    return this->numeroComponente;
}

void Configuracao::setNumeroComponente(int numComponente) {
    this->numeroComponente = numComponente;
}

int Configuracao::getLowIndex() {
    return this->lowIndex;
}

void Configuracao::setLowIndex(int numLowIndex) {
    this->lowIndex = numLowIndex;
}

bool Configuracao::isIntoStack() {
    return this->intoStack;
}

void Configuracao::setIntoStack(bool valor) {
    this->intoStack = valor;
}

bool Configuracao::wasVisited() {
    return this->visited;
}

void Configuracao::setVisited(bool value) {
    this->visited = value;
}

int Configuracao::getIntex(){
    return this->index;
}

void Configuracao::setIndex(int index){
    this->index = index;
}

literalNegativo Configuracao::getLiteralNegativo() {
    return this->literal;
}

bool Configuracao::isLiteral() {
    return (this->getFilhos().empty() && this->getConectivo() == C_NONE);
}

bool Configuracao::isVariavel() {
    return this->getConectivo() == C_NONE && !this->getFilhos().empty();
}

bool Configuracao::isMaxFixPoint() {

    if (this->isVariavel()) {
        list<Configuracao*> parents = this->getParents();

        for (list<Configuracao*>::iterator it = parents.begin();
                it != parents.end(); it++) {
            if ((*it)->getConectivo() == C_MAXPT) {
                return true;
            }
        }
    }

    return false;

}

bool Configuracao::isMinFixPoint() {

    if (this->isVariavel()) {
        list<Configuracao*> parents = this->getParents();

        for (list<Configuracao*>::iterator it = parents.begin();
                it != parents.end(); it++) {
            if ((*it)->getConectivo() == C_MINPT) {
                return true;
            }
        }
    }

    return false;

}

string Configuracao::toStr() {

    string fim = "\033[0m\n";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string black = "\033[1;30m";

    string jogador = this->jogador == EXISTE ? "[ext]" : "[prt]";
    string conectivo = "";
    stringstream ss;
    ss.str(" ");
    switch (this->conectivo) {
        case C_NONE: conectivo =
                    (this->literal.valorLogico ? "" : "NOT ")
                    + this->literal.literal;
            break;
        case C_AND: conectivo = " AND";
            break;
        case C_OR: conectivo = " OR";
            break;
        case C_AX: conectivo = " AX";
            break;
        case C_EX: conectivo = " EX";
            break;
        case C_MAXPT: conectivo = " MAX";
            break;
        case C_MINPT: conectivo = " MIN";
            break;
    }
    ss << "node(" << this->numeroNome << "::" << this->numEstado << ")" << " " << jogador
            << "{" << conectivo << "}";


    string final;

    if (this->getCor() == C_TRUE) {
        final = green;
    } else if (this->getCor() == C_FALSE) {
        final = red;
    } else if (this->getCor() == C_INDEF) {
        final = black;
    }

    final = final + ss.str() + fim;

    return final;
}

int Configuracao::getNumEstado() {
    return this->numEstado;
}



Componente::Componente(int numeroComponente) {
        this->configuracoes = *(new list<Configuracao*>);
        this->numComponente = numeroComponente;
        this->visitado = false;
        this->numConfiguracoesColoridas = 0;
    }

    void Componente::incrementNumConfiguracoesColoridos(){
        this->numConfiguracoesColoridas++;
    }

    void Componente::decrementNumConfiguracoesColoridos(){
        this->numConfiguracoesColoridas--;
    }

    list<Configuracao*> Componente::getConfiguracoes() {
        return this->configuracoes;
    }

    void Componente::addConfiguracao(Configuracao *configuracao) {
        this->configuracoes.push_back(configuracao);
    }

    string Componente::toStr() {
        stringstream ss;
        ss << "### Numero Componente :: " << this->numComponente << endl;
        for (list<Configuracao*>::iterator it = this->configuracoes.begin();
                it != this->configuracoes.end(); it++) {
            ss << "\t" << (*it)->toStr() << endl;

            list<Configuracao::TransicaoConfig> filhos = (*it)->getFilhos();


            for (list<Configuracao::TransicaoConfig>::iterator itFil = filhos.begin();
                    itFil != filhos.end(); itFil++) {
                ss << "\t\t" << (itFil->destino)->toStr() << endl;
            }

        }

        return ss.str();
    }

    vector< vector<bool> > * Componente::getRelacaoOrdem() {
        return this->relacaoEntreComponenetes;
    }

    void Componente::setRelacao(vector< vector<bool> > *relacaoEntreComponenetes) {
        this->relacaoEntreComponenetes = relacaoEntreComponenetes;
    }

    bool Componente::foiVisitado() {
        return this->visitado;
    }

    void Componente::setVisitado(bool value) {
        this->visitado = value;
    }

    int Componente::getNumComponente() {
        return this->numComponente;
    }

    void Componente::setNumComponente(int num) {
        this->numComponente = num;
        for(list<Configuracao*>::iterator it = this->configuracoes.begin() ;
                it != this->configuracoes.end() ; it++){
            (*it)->setNumeroComponente(num);
        }
    }

    int Componente::getNumConfiguracoesColoridas(){

        int cont = 0 ;

        for(list<Configuracao*>::iterator it = this->configuracoes.begin() ;
                it != this->configuracoes.end() ; it++){
            if((*it)->getCor() == C_TRUE || (*it)->getCor() == C_FALSE ||
                    (*it)->getCor() == C_INDEF){
                cont++;
            }
        }

        return cont;

        //return this->numConfiguracoesColoridas;
    }


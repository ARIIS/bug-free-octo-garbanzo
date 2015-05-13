#include "Vertex.h"

Vertex::Vertex(){
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
}

Vertex::Vertex(Vertex* v){
    this->idnum = v->getId();
    this->childset = *(new set<int>);
}

Vertex::Vertex(Configuracao* head){

	this->head = head;
        if (head->getJogador() == PARATODO){
            this->kind = ABELARDO;
        } else {
            this->kind = EVA;
        }
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
}

set<int> Vertex::getChildset(){
    return childset;
}

void Vertex::insertChildset(int child){
    childset.insert(child);
}

void Vertex::setChildset(set<int> input){
    childset = input;
}

Configuracao* Vertex::getHead(){
	return this->head;
}

virtual Configuracao* Vertex::getTail(){
    return 0;
}

VertexKind Vertex::getKind(){
	return this->kind;
}

void Vertex::setHead(Configuracao *head){
	this->head = head;
}

void Vertex::setKind(VertexKind kind){
	this->kind = kind;
}

void Vertex::setId(int id){
    idnum = id;
}

int Vertex::getId(){
    return idnum;
}

virtual bool Vertex::isWitness(){
    return false;
}

list<Vertex*> Vertex::getChildren(){
    return this->children;
}

list<Vertex*> Vertex::getParents(){
	return this->parents;
}

void Vertex::addChild(Vertex* child){
	this->children.push_back(child);
}

void Vertex::addParent(Vertex* dad){
	this->parents.push_back(dad);
}

Vertex* Vertex::getParent(){
    Vertex* v = parents.front();
    return v;
}

revision Vertex::getRevision(){
    revision out = *(new revision);
    if(this->isWitness()){
        Conectivo con1 = this->getHead()->getConectivo();
        Conectivo con2 = this->getTail()->getConectivo();
        TipoTransicao type = this->getTransition();

        change ch;

        if (con1 == C_OR || C_AND){
            ch.type = 1;
            ch.state1 = this-getHead()->getNumEstado();
            ch.lit = this->getTail()->getLiteralNegativo();

            out.push_back(ch);
        }

    }
    return out;
}

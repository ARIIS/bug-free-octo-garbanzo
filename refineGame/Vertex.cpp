#include "../refineGame/Vertex.h"

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

void Vertex::setComponent(Conectivo input){
    this->component = input;
}

Conectivo Vertex::getComponent(){
    return this->component;
}

void Vertex::setChildset(set<int> input){
    childset = input;
}

Configuracao* Vertex::getHead(){
	return this->head;
}

Configuracao* Vertex::getTail(){
    return this->head;
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

bool Vertex::isWitness(){
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

revision Vertex::getRevision(bool dupli){
    return *(new revision);
}

bool Vertex::isDuplicated(){
    return false;
}

TipoTransicao Vertex::getTransition(){
    return MUST;
}

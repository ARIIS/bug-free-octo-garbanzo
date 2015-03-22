#include "Vertex.h"

Vertex::Vertex(){
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
}
Vertex::Vertex(Configuracao* head, VertexKind kind){
	
	this->head = head;
	this->kind = kind;
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
	
}

Vertex::Vertex(Configuracao* head){
	
	this->head = head;
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
	
}

Configuracao* Vertex::getHead(){
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

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition){
	this->setHead(head);
	this->setKind(kind);
	this->tail = tail;
	this->transition = transition;
	
}

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition){
	this->setHead(head);
	this->tail = tail;
	this->transition = transition;
	
}

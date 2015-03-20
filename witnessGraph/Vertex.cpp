#include "Vertex.h"

Vertex::Vertex(Configuracao* head, VertexKind kind){
	
	this->head = head;
	this->kind = kind;
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
	
}

Configuracao* Vertex::getHead(){
	return this->head;
}

VertexKind Vertex::getKind(){
	return this->kind;
}

list<Vertex*> Vertex::getChildren(){
	return this->children;
}

list<Vertex*> Vertex::getParents(){
	return this->parents;
}

VertexWitness::VertexWitness(Configuracao* head, Configuracao* tail, VertexKind kind, TransitionKind transition){
	this->head = head;
	this->kind = kind;
	this->tail = tail;
	this->transition = transition;
	this->children = *(new list<Vertex*>);
	this->parents = *(new list<Vertex*>);
}

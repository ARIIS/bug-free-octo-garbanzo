#ifndef VERTEX_H
#define	VERTEX_H

#include "Configuracao.h"
#include "Estado.h"
#include <list>

typedef enum {
	EVA, ABELARDO
} VertexKind;

class Vertex{

private: 
	VertexKind kind;
	Configuracao *head;
	list<Vertex*> children;
	list<Vertex*> parents;
	
public:
	
	Vertex(Configuracao* head, VertexKind kind);
	Configuracao* getHead();
	VertexKind getKind();
	list<Vertex*> getChildren();
	list<Vertex*> getParents();
	void addChild(Vertex* child);
	void addParent(Vertex* dad); 

};

class VertexWitness: public Vertex {
	
	private:
		Configuracao *tail;
		TipoTransicao transition;
	
	public:
		VertexWitness(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition);
		Configuracao* getTail();
		TipoTransicao getTransition();
};

#endif

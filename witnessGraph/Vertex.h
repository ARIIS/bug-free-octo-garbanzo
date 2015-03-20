#ifndef VERTEX_H
#define	VERTEX_H

#include "Configuracao.h"
#include <list>

typedef enum {
	EVA, ABELARDO
} VertexKind;

typedef enum {
	MAY, MUST
} TransitionKind;

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

}

class VertexWitness: public Vertex {
	
	private:
		Configuracao *tail;
		TransitionKind transition
	
	public:
		VertexWitness(Configuracao* head, Configuracao* tail, VertexKind kind, TransitionKind transition);
		Configuracao* getTail();
		TransitionKind getTransition();
};

#endif

#ifndef VERTEX_H
#define	VERTEX_H

#include "Configuracao.h"
#include "Estado.h"
#include <list>

typedef enum {
	ABELARDO, EVA
} VertexKind;

class Vertex{

private: 
	VertexKind kind;
	Configuracao *head;
	list<Vertex*> children;
	list<Vertex*> parents;
	
public:
	
	Vertex();
	Vertex(Configuracao* head);
	Vertex(Configuracao* head, VertexKind kind);
	Configuracao* getHead();
	VertexKind getKind();
	void setHead(Configuracao *head);
	void setKind(VertexKind kind);
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
		VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
		Configuracao* getTail();
		TipoTransicao getTransition();
};

#endif

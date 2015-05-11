#ifndef VERTEX_H
#define	VERTEX_H

#include "../arena/Configuracao.h"
#include "../arena/Estado.h"
#include <list>
#include <set>

typedef enum {
	ABELARDO, EVA
} VertexKind;

class Vertex{

private:
	VertexKind kind;
	Configuracao *head;
	list<Vertex*> children;
	list<Vertex*> parents;
        int idnum;
        set<int> childset;

public:

	Vertex();
        Vertex::Vertex(Vertex* v);
	Vertex(Configuracao* head);
	Configuracao* getHead();
	VertexKind getKind();
	void setHead(Configuracao *head);
	void setKind(VertexKind kind);
        void setId(int id);
        int getId();
	list<Vertex*> getChildren();
	list<Vertex*> getParents();
	void addChild(Vertex* child);
	void addParent(Vertex* dad);
        set<int> getChildset();
        void insertChildset(int child);
        void setChildset(set<int> input);
        virtual bool isWitness();
        Vertex* getParent();
        virtual Configuracao* getTail()

};

#endif

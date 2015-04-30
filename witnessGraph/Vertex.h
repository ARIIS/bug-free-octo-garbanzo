#ifndef VERTEX_H
#define	VERTEX_H

#include "../modelChecking/Configuracao.h"
#include "../modelChecking/Estado.h"
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

class VertexWitness: public Vertex {
	
	private:
		Configuracao *tail;
		TipoTransicao transition;
                Change* mudanca;
	
	public:
		VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
		Configuracao* getTail();
		TipoTransicao getTransition();
                bool isWitness();
                Change* getChange();
                void insertChange(Change* c);
};

#endif

#ifndef VERTEX_H
#define	VERTEX_H

#include "../arena/Configuracao.h"
#include "../arena/Estado.h"
#include <list>
#include <set>

typedef enum {
	ABELARDO, EVA
} VertexKind;

typedef struct changeid {
    int type;
    int state1;
    int state2;
    literalNegativo lit;
} change;

/*bool setcomp(change ch1, change ch2) {
    if (ch1.type == ch2.type){
        if (ch1.state1 == ch2.state1){
            if (ch1.state2 == ch2.state2){
                if (ch1.lit.valorLogico == ch2.lit.valorLogico){
                    return ch1.lit.literal.compare(ch2.lit.literal) < 0;
                } else {
                    return ch1.lit.valorLogico && ch2.lit.valorLogico;
                }
            } else {
                return ch1.state2 < ch2.state2;
            }
        } else {
            return ch1.state1 < ch2.state1;
        }
    } else {
        return ch1.type < ch2.type;
    }
}

bool(*set_pt)(change,change) = setcomp; */

typedef list<change> revision;
typedef list<revision> revisionlist;

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
        Vertex(Vertex* v);
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
        virtual Configuracao* getTail();
        virtual revision getRevision();
        
};

#endif

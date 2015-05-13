#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include <vector>
#include "Vertex.h"
#include "../refineGame/RefineGame.h"

class WitnessGraph{
    typedef enum {
        EQUAL;
        LESS;
        GREATER;
        INCOMP;
    } comparation;

	private:
		vector<Vertex*> nTV;
		set<Configuracao*> visited;
                list<TestemunhadeFalha> witnesses;
		bool pertence(Configuracao* ci, Configuracao* cj);
		list<Vertex*> vertices;
                vector<Vertex*> verticesvector;
                void insertVertex(Vertex* v);
                Vertex* root;
                vector<revisionlist> vG;
                static int graphcount;
                int graphid;
                revisionlist evaMinimals(Vertex* v);
                revisionlist evaGraphs(Vertex* v);
                revisionlist alfa(Vertex* v);
                revisionlist beta(Vertex* v);
                comparation compare(revision rev1, revision rev2)
                revisionlist minimals(revisionlist input);

	public:
		WitnessGraph();
		WitnessGraph(Arena* a, list<TestemunhadeFalha> w);
                WitnessGraph(Vertex* v);
		Vertex* cycleAncestor(Configuracao* ci);
		Vertex* nextVertex(Configuracao* ci);
		void createEdge(Vertex* origin, Vertex* destination);
                void connect(WitnessGraph* sub);
                list<Vertex*> getVertices();
                int rootId();

};


#endif

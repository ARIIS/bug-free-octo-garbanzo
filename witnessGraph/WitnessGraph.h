#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include <vector>
#include "Vertex.h"
#include "../refineGame/RefineGame.h"
#include "Change.h"

class WitnessGraph{

    typedef list<WitnessGraph*> graphlist;

	private:
		vector<Vertex*> nTV;
		set<Configuracao*> visited;
                list<TestemunhadeFalha> witnesses;
		bool pertence(Configuracao* ci, Configuracao* cj);
		list<Vertex*> vertices;
                vector<Vertex*> verticesvector;
                void insertVertex(Vertex* v);
                Vertex* root;
                vector<graphlist> vG;
                static int graphcount;
                int graphid;

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
                graphlist evaMinimals(Vertex* v);
                graphlist alfa(Vertex* v);
                graphlist beta(Vertex* v);
                graphlist arrangealfa(Vertex* v);
                graphlist arrangebeta(Vertex* v);

};


#endif

#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include <vector>
#include "Vertex.h"
#include "../refineGame/RefineGame.h"
#include "Change.h"

class WitnessGraph{

    typedef list<WitnessGraph*> conjuntodegrafos;

	private:
		vector<Vertex*> nTV;
		set<Configuracao*> visitados;
                list<TestemunhadeFalha> witnesses;
		bool pertence(Configuracao* ci, Configuracao* cj);
		list<Vertex*> vertices;
                vector<Vertex*> verticesvector;
                void insertVertex(Vertex* v);
                Vertex* root;
                vector<conjuntodegrafos> vG;
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
                conjuntodegrafos evaMinimals(Vertex* v);
                conjuntodegrafos alfa(Vertex* v);
                conjuntodegrafos beta(Vertex* v);
                conjuntodegrafos organizealfa(Vertex* v);
                conjuntodegrafos organizebeta(Vertex* v);

};


#endif

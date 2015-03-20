#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include "Vertex.h"

class WitnessGraph{
	
	public:
		list<Vertex*> vertices;
		WitnessGraph();
		Vertex* CreateVertex(Configuracao* head, VertexKind kind);
		VertexWitness* CreateVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TransitionKind transition);
		void CreateEdge(Vertex* origin, Vertex* destination);
		 
};


#endif

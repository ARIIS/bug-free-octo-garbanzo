#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include "Vertex.h"
//#include "Estado.h"

class WitnessGraph{
	
	private:
		vector<Vertex*> nTV;
	
	public:
		list<Vertex*> vertices;
		WitnessGraph();
		WitnessGraph(Arena* a);
		Vertex* CreateVertex(Configuracao* head);
		Vertex* CreateVertex(Configuracao* head, VertexKind kind);
		VertexWitness* CreateVertex(Configuracao* head, Configuracao* tail, TipoTransicao transition);
		VertexWitness* CreateVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition);
		Vertex* CycleAncestor(vector<Vertex*> nTV, Configuracao* ci);
		void CreateEdge(Vertex* origin, Vertex* destination);
		 
};


#endif

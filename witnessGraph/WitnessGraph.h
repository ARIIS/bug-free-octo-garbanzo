#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include "Vertex.h"
//#include "Estado.h"

class WitnessGraph{
	
	private:
		vector<Vertex*> nTV;
		set<Configuracao*> visitados;
		bool pertence(list<Configuracao::TransicaoConfig> conjunto, Configuracao* ci);
		list<Vertex*> vertices;
	
	public:
		WitnessGraph();
		WitnessGraph(Arena* a);
		Vertex* createVertex(Configuracao* head);
		Vertex* createVertex(Configuracao* head, VertexKind kind);
		VertexWitness* createVertex(Configuracao* head, Configuracao* tail, TipoTransicao transition);
		VertexWitness* createVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition);
		Vertex* cycleAncestor(Configuracao* ci);
		Vertex* nextVertex(Configuracao* ci, list<Configuracao::TransicaoConfig> w);
		void createEdge(Vertex* origin, Vertex* destination);
		 
};


#endif

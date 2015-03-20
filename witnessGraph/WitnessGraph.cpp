#include "WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

Vertex* WitnessGraph::CreateVertex(Configuracao* head, VertexKind kind){
	Vertex* c = new Vertex(head,kind);
	this->vertices.push_back(c);
	return c;
}

VertexWitness* WitnessGraph::CreateVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TransitionKind transition){
	VertexWitness* c = new VertexWitness(head, tail, kind, transition);
	this->vertices.push_back(c);
	return c;
}

void WitnessGraph::CreateEdge(Vertex* origin, Vertex* destination){
	origin->children.push_back(destination);
	destination->parents.push_back(origin);
}

#include "WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

WitnessGraph::WitnessGraph(Arena* a){
	this->vertices = *(new list<Vertex*>);
	int n = a->getMatrizConfiguracao().size();
	this->nTV = *(new vector<Vertex*>(n));
	for(int i =0; i<n;i++){
		nTV[i] = 0;
	}
	Configuracao *czero = a->getMatrizConfiguracao().front();
	this->nTV[0] = CreateVertex(czero);
	this->vertices.push_back(this->nTV[0]);
}

Vertex* WitnessGraph::CreateVertex(Configuracao* head){
	Vertex* c = new Vertex(head);
	this->vertices.push_back(c);
	return c;
}

Vertex* WitnessGraph::CreateVertex(Configuracao* head, VertexKind kind){
	Vertex* c = new Vertex(head, kind);
	this->vertices.push_back(c);
	return c;
}

VertexWitness* WitnessGraph::CreateVertex(Configuracao* head, Configuracao* tail, TipoTransicao transition){
	VertexWitness* c = new VertexWitness(head, tail, transition);
	this->vertices.push_back(c);
	return c;
}

VertexWitness* WitnessGraph::CreateVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition){
	VertexWitness* c = new VertexWitness(head, tail, kind, transition);
	this->vertices.push_back(c);
	return c;
}

void WitnessGraph::CreateEdge(Vertex* origin, Vertex* destination){
	origin->addChild(destination);
	destination->addParent(origin);
}

Vertex* WitnessGraph::CycleAncestor(vector<Vertex*> nTV, Configuracao* ci){
	if (nTV[ci->getNumNome()]==0){
		Configuracao* cj;
		list<Configuracao::TransicaoConfig> filhos = ci->getFilhos();
		for (list<Configuracao::TransicaoConfig>::iterator it = filhos.begin(); it != filhos.end(); it++){
			if ((*it).destino->getCor() == C_INDEF){
				cj = (*it).destino;
			}
		}
		nTV[ci->getNumNome()] = CycleAncestor(nTV,cj);
	}
	return nTV[ci->getNumNome()];
}

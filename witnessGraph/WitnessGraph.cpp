#include "WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

WitnessGraph::WitnessGraph(Arena* a){
	this->visitados = *(new set<Configuracao*>);
	this->vertices = *(new list<Vertex*>);
	int n = a->getMatrizConfiguracao().size();
	this->nTV = *(new vector<Vertex*>(n));
	for(int i =0; i<n;i++){
		nTV[i] = 0;
	}
	Configuracao *czero = a->getMatrizConfiguracao().front();
	this->nTV[0] = createVertex(czero);
	this->vertices.push_back(this->nTV[0]);
	if (czero->getConectivo() != C_NONE){
		//Vertex* v = nextVertex(czero,/*ALGUMA COISA*/);
	}
}

Vertex* WitnessGraph::createVertex(Configuracao* head){
	Vertex* c = new Vertex(head);
	this->vertices.push_back(c);
	return c;
}

Vertex* WitnessGraph::createVertex(Configuracao* head, VertexKind kind){
	Vertex* c = new Vertex(head, kind);
	this->vertices.push_back(c);
	return c;
}

VertexWitness* WitnessGraph::createVertex(Configuracao* head, Configuracao* tail, TipoTransicao transition){
	VertexWitness* c = new VertexWitness(head, tail, transition);
	this->vertices.push_back(c);
	return c;
}

VertexWitness* WitnessGraph::createVertex(Configuracao* head, Configuracao* tail, VertexKind kind, TipoTransicao transition){
	VertexWitness* c = new VertexWitness(head, tail, kind, transition);
	this->vertices.push_back(c);
	return c;
}

void WitnessGraph::createEdge(Vertex* origin, Vertex* destination){
	origin->addChild(destination);
	destination->addParent(origin);
}

Vertex* WitnessGraph::cycleAncestor(Configuracao* ci){
	if (nTV[ci->getNumNome()]==0){
		Configuracao* cj;
		list<Configuracao::TransicaoConfig> filhos = ci->getFilhos();
		for (list<Configuracao::TransicaoConfig>::iterator it = filhos.begin(); it != filhos.end(); it++){
			if ((*it).destino->getCor() == C_INDEF){
				cj = (*it).destino;
			}
		}
		nTV[ci->getNumNome()] = cycleAncestor(cj);
	}
	return nTV[ci->getNumNome()];
}

bool WitnessGraph::pertence(list<Configuracao::TransicaoConfig> conjunto, Configuracao* ci){
	bool out = false;
	for (list<Configuracao::TransicaoConfig>::iterator it = conjunto.begin(); it != conjunto.end(); it++){
		if ((*it).destino == ci){
			out = true;
		}
	}
	return out;
}

Vertex* WitnessGraph::nextVertex(Configuracao* ci, list<Configuracao::TransicaoConfig> w){
	this->visitados.insert(ci);
	list<Configuracao::TransicaoConfig> t = *(new list<Configuracao::TransicaoConfig>);
	list<Configuracao::TransicaoConfig> filhos = ci->getFilhos();
	for (list<Configuracao::TransicaoConfig>::iterator it = filhos.begin(); it != filhos.end(); it++){
			if ((*it).destino->getCor() == C_INDEF || pertence(w,(*it).destino)){
				t.push_back((*it));
			}	
	}
	TipoTransicao tipo;
	Vertex* v;
	if (t.size() == 1 && pertence(w,t.front().destino)){
		
		Configuracao::TransicaoConfig trans = t.front();
		
		if (trans.isMust){
			tipo = MUST;
		} else {
			tipo = MAY;
		}
		v = createVertex(ci,trans.destino,tipo);
		nTV[ci->getNumNome()] = v;
		this->vertices.push_back(v);
	} else if (t.size() > 2){
		v = createVertex(ci);
		nTV[ci->getNumNome()] = v;
		this->vertices.push_back(v);
	}
	Configuracao* cj;
	Vertex* novov;
	for (list<Configuracao::TransicaoConfig>::iterator it = t.begin(); it != t.end(); it++){
		cj = (*it).destino;
		if ((*it).isMust){
			tipo = MUST;
		} else {
			tipo = MAY;
		}
		if (t.size() > 1 && cj->getCor() != C_INDEF || cj->getConectivo() == C_NONE){
			novov = createVertex(ci,cj,tipo);
			createEdge(nTV[ci->getNumNome()],novov);
			vertices.push_back(novov);
		} else {
			if (cj->getCor() == C_INDEF && cj->getConectivo() != C_NONE){
				novov = nTV[ci->getNumNome()];
				if (visitados.find(cj) != visitados.end()){
					novov = cycleAncestor(cj);
				} else {
					novov = nextVertex(cj,w);
				}
				if (pertence(w,cj) && t.size()==1){
					createEdge(nTV[ci->getNumNome()],novov);
				} else {
					if (pertence(w,cj)){
						Vertex* v1 = createVertex(ci,cj, tipo);
						createEdge(nTV[ci->getNumNome()],v1);
						createEdge(v1,novov);
					} else {
						if (t.size()>1){
							createEdge(nTV[ci->getNumNome()],novov);
						} else {
							nTV[ci->getNumNome()] = novov;
						}
					}
				}
			}
		}
	}
	
	return nTV[ci->getNumNome()];
}

/* int main(int argc , char **argv){
	
	return 0;
} */

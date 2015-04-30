#include "WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

WitnessGraph::WitnessGraph(Arena* a, list<TestemunhadeFalha> w){
        this->witnesses = w;
	this->visitados = *(new set<Configuracao*>);
	this->vertices = *(new list<Vertex*>);
	int n = a->getMatrizConfiguracao().size();
	this->nTV = *(new vector<Vertex*>(n));
	for(int i =0; i<n;i++){
		nTV[i] = 0;
	}
	Configuracao *czero = a->getMatrizConfiguracao().front();
	this->nTV[0] = new Vertex(czero);
	this->insertVertex(this->nTV[0]);
        root = nTV[0];
	if (czero->getConectivo() != C_NONE){
		Vertex* v = nextVertex(czero);
	}
        this->verticesvector = *(new vector<Vertex*>[vertices.size()]);
        for(list<Vertex*>::iterator it = vertices.begin(); it != vertices.end();it++){
            verticesvector[(*it)->getId()] = (*it);
        }
        this->vG = *(vector<conjuntodegrafos>[vertices.size()]);
}

WitnessGraph::WitnessGraph(Vertex* v){
    this->vertices = *(new list<Vertex*>);
    Vertex* vlinha;
    vlinha = new Vertex(v);
    root = vlinha;
    this->vertices.push_back(vlinha);
    this->graphid = graphcount++;
    if (v->isWitness()){
        Change *x = v->getChange();
        this->changes.push_back(x);
        x->include(graphid);
    }
}

void WitnessGraph::insertVertex(Vertex* v){
    v->setId(vertices.size());
    vertices.push_back(v);
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
                                break;
			}
		}
		nTV[ci->getNumNome()] = cycleAncestor(cj);
	}
	return nTV[ci->getNumNome()];
}

bool WitnessGraph::pertence(Configuracao* ci, Configuracao* cj){
	bool out = false;
	for (list<TestemunhadeFalha>::iterator it = witnesses.begin(); it != witnesses.end(); it++){
		if ((*it).origem == ci && ((*it).destino)-> == cj){
			out = true;
		}
	}
	return out;
}

Vertex* WitnessGraph::nextVertex(Configuracao* ci){
	this->visitados.insert(ci);
	list<Configuracao::TransicaoConfig> t = *(new list<Configuracao::TransicaoConfig>);
	list<Configuracao::TransicaoConfig> filhos = ci->getFilhos();
	for (list<Configuracao::TransicaoConfig>::iterator it = filhos.begin(); it != filhos.end(); it++){
			if ((*it).destino->getCor() == C_INDEF || pertence(ci,(*it).destino)){
				t.push_back((*it));
			}
	}
	TipoTransicao tipo;
	Vertex* v;
	if (t.size() == 1 && pertence(ci,t.front().destino)){

		Configuracao::TransicaoConfig trans = t.front();

		if (trans.isMust){
			tipo = MUST;
		} else {
			tipo = MAY;
		}
		v = new VertexWitness(ci,trans.destino,tipo);
		nTV[ci->getNumNome()] = v;
		this->insertVertex(v);
	} else if (t.size() > 2){
		v = new Vertex(ci);
		nTV[ci->getNumNome()] = v;
		this->insertVertex(v);
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
			novov = new VertexWitness(ci,cj,tipo);
			createEdge(nTV[ci->getNumNome()],novov);
			this->insertVertex(novov);
		} else {
			if (cj->getCor() == C_INDEF && cj->getConectivo() != C_NONE){
				novov = nTV[ci->getNumNome()];
				if (visitados.find(cj) != visitados.end()){
					novov = cycleAncestor(cj);
				} else {
					novov = nextVertex(cj,w);
				}
				if (pertence(ci,cj) && t.size()==1){
					createEdge(nTV[ci->getNumNome()],novov);
				} else {
					if (pertence(ci,cj)){
						Vertex* v1 = new VertexWitness(ci,cj, tipo);
                                                insertVertex(v1);
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

list<Vertex*> WitnessGraph::getVertices(){
    return vertices;
}

int WitnessGraph::rootId(){
    return this->root->getId();
}

void WitnessGraph::connect(WitnessGraph* sub){
    Vertex* v;
    for(list<Vertex*>::iterator it = sub->getVertices().begin(); it != sub->getVertices().end(); it++){
        v = new Vertex(*it);
        this->vertices.push_back(v);
    }
    this->root.insertChildset(sub->rootId());
}

conjuntodegrafos WitnessGraph::evaMinimals(Vertex* v){
    if (vG[v->getId()] == 0){
        if(v->getKind == EVA){
            vG[v->getId()] = alfa(v);
        } else {
            vG[v->getId()] = beta(v);
        }
    }
    return vG[v->getId()];
}

conjuntodegrafos WitnessGraph::alfa(Vertex* v){
    conjuntodegrafos out = *(new conjuntodegrafos);
    if (v->isWitness() && v->getTail()->getConectivo() == C_INDEF){
        out.push_back(new WitnessGraph(v));
    } else {
        list<conjuntodegrafos> children = *(new list<conjuntodegrafos>);
        for (list<Vertex*>::iterator filho = v->getChildren().begin(); filho != v->getChildren().end(); filho++){
            children.push_back(evaMinimals(*filho));
        }
        out = organizealfa(v,children);
    }

    return out;
}
/*
conjuntodegrafos WitnessGraph::beta(Vertex* v){
    conjuntodegrafos out = *(new conjuntodegrafos);
    if (v->isWitness() && v->getTail()->getConectivo() == C_INDEF){
        if (v->getHead() != v->getParent()->getHead()){
            out.push_back(new WitnessGraph(v));
        }
    } else {
        list<conjuntodegrafos> children = *(new list<conjuntodegrafos>);
        for (list<Vertex*>::iterator filho = v->getChildren().begin(); filho != v->getChildren().end(); filho++){
            children.push_back(evaMinimals(*filho));
        }
        out = organizebeta(v,children);
    }

    return out;
}*/

conjuntodegrafos WitnessGraph::organizealfa(Vertex* v, list<conjuntodegrafos> conjuntos){
    conjuntodegrafos min = *(new conjuntodegrafos);
    min = conjuntos.pop_front();
    for (list<conjuntodegrafos>::iterator it = conjuntos.begin(); it!=conjuntos.end();it++){
        for(conjuntodegrafos::iterator candidato = (*it).begin(); candidato!=(*it).end();candidato++){
            conjuntodegrafos::iterator mini;
            for(mini = min.begin(); mini!=min.end();mini++){
                comparacao relacao = compara((*candidato),(*mini));
                if (relacao == MAIOR){
                    break;
                } else if (relacao == IGUAL){
                    min.push_front((*candidato));
                    break;
                } else if (relacao == MENOR){
                    min.erase(mini);
                }
            }
            if (mini == min.end()){
                min.push_front((*candidato));
            }
        }
    }
    WitnessGraph* father;
    conjuntodegrafos out;
    for (conjuntodegrafos::iterator it = min.begin(); it != min.end(); it++){
        father = new WitnessGraph(v);
        father->connect(*it);
        out.push_back(father);
    }
    return out;
}

/* int main(int argc , char **argv){

	return 0;
} */

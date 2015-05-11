#include "WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

WitnessGraph::WitnessGraph(Arena* a, list<TestemunhadeFalha> w){
        this->graphcount = 0;
        this->witnesses = w;
	this->visited = *(new set<Configuracao*>);
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
        this->vG = *(new vector<graphlist>[vertices.size()]);
}

WitnessGraph::WitnessGraph(Vertex* v){
    this->changes = *(new list<Change*>);
    this->vertices = *(new list<Vertex*>);
    Vertex* vline;
    vline = new Vertex(v);
    root = vline;
    this->vertices.push_back(vline);
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
		list<Configuracao::TransicaoConfig> kids = ci->getFilhos();
		for (list<Configuracao::TransicaoConfig>::iterator it = kids.begin(); it != kids.end(); it++){
			if ((*it).destino->getCor() == C_INDEF){
				cj = (*it).destino;
                                break;
			}
		}
		nTV[ci->getNumNome()] = cycleAncestor(cj);
	}
	return nTV[ci->getNumNome()];
}

bool WitnessGraph::match(Configuracao* ci, Configuracao* cj){
	bool out = false;
	for (list<TestemunhadeFalha>::iterator it = witnesses.begin(); it != witnesses.end(); it++){
		if ((*it).origem == ci && ((*it).destino)-> == cj){
			out = true;
		}
	}
	return out;
}

Vertex* WitnessGraph::nextVertex(Configuracao* ci){
	this->visited.insert(ci);
	list<Configuracao::TransicaoConfig> t = *(new list<Configuracao::TransicaoConfig>);
	list<Configuracao::TransicaoConfig> kids = ci->getFilhos();
	for (list<Configuracao::TransicaoConfig>::iterator it = kids.begin(); it != kids.end(); it++){
			if ((*it).destino->getCor() == C_INDEF || match(ci,(*it).destino)){
				t.push_back((*it));
			}
	}
	TipoTransicao type;
	Vertex* v;
	if (t.size() == 1 && match(ci,t.front().destino)){

		Configuracao::TransicaoConfig trans = t.front();

		if (trans.isMust){
			type = MUST;
		} else {
			type = MAY;
		}
		v = new VertexWitness(ci,trans.destino,type);
		nTV[ci->getNumNome()] = v;
		this->insertVertex(v);
	} else if (t.size() > 2){
		v = new Vertex(ci);
		nTV[ci->getNumNome()] = v;
		this->insertVertex(v);
	}
	Configuracao* cj;
	Vertex* newv;
	for (list<Configuracao::TransicaoConfig>::iterator it = t.begin(); it != t.end(); it++){
		cj = (*it).destino;
		if ((*it).isMust){
			type = MUST;
		} else {
			type = MAY;
		}
		if (t.size() > 1 && cj->getCor() != C_INDEF || cj->getConectivo() == C_NONE){
			newv = new VertexWitness(ci,cj,type);
			createEdge(nTV[ci->getNumNome()],newv);
			this->insertVertex(newv);
		} else {
			if (cj->getCor() == C_INDEF && cj->getConectivo() != C_NONE){
				newv = nTV[ci->getNumNome()];
				if (visited.find(cj) != visited.end()){
					newv = cycleAncestor(cj);
				} else {
					newv = nextVertex(cj,w);
				}
				if (match(ci,cj) && t.size()==1){
					createEdge(nTV[ci->getNumNome()],newv);
				} else {
					if (match(ci,cj)){
						Vertex* v1 = new VertexWitness(ci,cj, type);
                                                insertVertex(v1);
						createEdge(nTV[ci->getNumNome()],v1);
						createEdge(v1,newv);
					} else {
						if (t.size()>1){
							createEdge(nTV[ci->getNumNome()],newv);
						} else {
							nTV[ci->getNumNome()] = newv;
						}
					}
				}
			}
		}
	}

	return nTV[ci->getNumNome()];
}

list<Vertex*> WitnessGraph::getVertices(){ //15
    return vertices;
}

int WitnessGraph::rootId(){ //13
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

graphlist WitnessGraph::evaMinimals(Vertex* v){
    int id = v->getId();
    if (vG[id] == 0){
        if(v->getKind == EVA){
            vG[id] = alfa(v);
        } else {
            vG[id] = beta(v);
        }
    }
    return vG[id];
}

graphlist WitnessGraph::alfa(Vertex* v){ //2
    graphlist out = *(new graphlist);
    if (v->isWitness() && v->getTail()->getConectivo() == C_INDEF){
        out.push_back(new WitnessGraph(v));
    } else {
        list<graphlist> children = *(new list<graphlist>);
        for (list<Vertex*>::iterator kid = v->getChildren().begin(); kid != v->getChildren().end(); kid++){
            children.push_back(evaMinimals(*kid));
        }
        out = organizealfa(v,children);
    }

    return out;
}
/*
graphlist WitnessGraph::beta(Vertex* v){
    graphlist out = *(new graphlist);
    if (v->isWitness() && v->getTail()->getConectivo() == C_INDEF){
        if (v->getHead() != v->getParent()->getHead()){
            out.push_back(new WitnessGraph(v));
        }
    } else {
        list<graphlist> children = *(new list<graphlist>);
        for (list<Vertex*>::iterator kid = v->getChildren().begin(); kid != v->getChildren().end(); kid++){
            children.push_back(evaMinimals(*kid));
        }
        out = organizebeta(v,children);
    }

    return out;
}*/

graphlist WitnessGraph::organizealfa(Vertex* v, list<graphlist> conjuntos){ //9
    graphlist min = *(new graphlist);
    min = conjuntos.pop_front();
    for (list<graphlist>::iterator it = conjuntos.begin(); it!=conjuntos.end();it++){
        for(graphlist::iterator candidato = (*it).begin(); candidato!=(*it).end();candidato++){
            graphlist::iterator mini;
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
    graphlist out;
    for (graphlist::iterator it = min.begin(); it != min.end(); it++){
        father = new WitnessGraph(v);
        father->connect(*it);
        out.push_back(father);
    }
    return out;
}

/* int main(int argc , char **argv){

	return 0;
} */

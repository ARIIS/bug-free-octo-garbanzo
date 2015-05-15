#include "../refineGame/WitnessGraph.h"

WitnessGraph::WitnessGraph(){
	this->vertices = *(new list<Vertex*>);
}

WitnessGraph::WitnessGraph(Arena* a, list<TestemunhaDeFalha> w){
        //this->graphcount = 0;
        this->witnesses = w;
	this->visited = *(new set<Configuracao*>);
	this->vertices = *(new list<Vertex*>);

	int n = a->getMatrizConfiguracao().size();
	this->nTV = *(new vector<Vertex*>(n));
	for(int i =0; i<n;i++){
		nTV[i] = 0;
	}

	Configuracao *czero = a->getMatrizConfiguracao().front();

	//this->nTV[0] = new Vertex(czero);
	//this->insertVertex(this->nTV[0]);
        //root = nTV[0];
	if (czero->getConectivo() != C_NONE){
		root = nextVertex(czero);
	}
        this->verticesvector = *(new vector<Vertex*>(vertices.size()));
        this->vG = *(new vector<revisionlist>(vertices.size()));
        for(list<Vertex*>::iterator it = vertices.begin(); it != vertices.end();it++){

            verticesvector[(*it)->getId()] = (*it);
            vG[(*it)->getId()] = *(new revisionlist);
        }

        /*for (list<TestemunhaDeFalha>::iterator it = this->witnesses.begin(); it!= this->witnesses.end(); it++){
            cout << (*it).origem->getNumEstado() << " " << (*it).origem->getConectivo() << " " << (*it).destino->destino->getNumEstado() << " " << (*it).destino->destino->getConectivo() << endl;
            cout << endl;
        }*/
        evaMinimals(root);

}

/*WitnessGraph::WitnessGraph(Vertex* v){
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
}*/

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
	for (list<TestemunhaDeFalha>::iterator it = witnesses.begin(); it != witnesses.end(); it++){
		if ((*it).origem == ci && ((*it).destino)->destino == cj){
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
		v = new VertexWitness(ci,trans.destino,type,this->witnesses);
		nTV[ci->getNumNome()] = v;
                if (ci->getNumNome()==0){
                    Vertex* vi = new Vertex(ci);
                    nTV[0] = vi;
                    this->createEdge(vi,v);
                }
		this->insertVertex(v);
	} else if (t.size() >= 2){

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
		if (t.size() > 1 && (cj->getCor() != C_INDEF || cj->getConectivo() == C_NONE)){

			newv = new VertexWitness(ci,cj,type,this->witnesses);

                        this->insertVertex(newv);
			createEdge(nTV[ci->getNumNome()],newv);


		} else {
			if (cj->getCor() == C_INDEF && cj->getConectivo() != C_NONE){

				//newv = nTV[ci->getNumNome()];
				if (visited.find(cj) != visited.end()){

					newv = cycleAncestor(cj);
				} else {

					newv = nextVertex(cj);

				}
				if (match(ci,cj) && t.size()==1){

					createEdge(nTV[ci->getNumNome()],newv);
				} else {

					if (match(ci,cj)){

						Vertex* v1 = new VertexWitness(ci,cj,type,this->witnesses);
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

/*void WitnessGraph::connect(WitnessGraph* sub){
    Vertex* v;
    for(list<Vertex*>::iterator it = sub->getVertices().begin(); it != sub->getVertices().end(); it++){
        v = new Vertex(*it);
        this->vertices.push_back(v);
    }
    this->root.insertChildset(sub->rootId());
}*/

revisionlist WitnessGraph::evaMinimals(Vertex* v){
    revisionlist out = minimals(evaGraphs(v));
    for (revisionlist::iterator it = out.begin(); it!= out.end();it++){
        cout << "{";
        for (revision::iterator it1 = (*it).begin(); it1!=(*it).end();it1++){
            cout << "(" << (*it1).state1 << "s,";
            if ((*it1).state2 != -1){
                cout << (*it1).state2 << "s)";
                if ((*it1).type == 3){
                    cout << "m ";
                } else {
                    cout << "c ";
                }
            } else {
                if (!(*it1).lit.valorLogico){
                    cout << "-";
                }
                cout << (*it1).lit.literal << ") ";
            }
        }
        cout << "}" << endl;
    }
    return out;
}

revisionlist WitnessGraph::evaGraphs(Vertex* v){
    int id = v->getId();
    //cout << id << endl;
    if (vG[id].size() == 0){
        if(v->getKind() == EVA){
            vG[id] = alfa(v);
        } else {
            vG[id] = beta(v);
        }
    }

    return vG[id];
}

revisionlist WitnessGraph::alfa(Vertex* v){
    revisionlist out = *(new revisionlist);
    revision aux;
    if (v->isWitness() && v->getTail()->getConectivo() == C_NONE){
        out.push_back(v->getRevision(false));
    } else {
        list<Vertex*> temp = v->getChildren();
        for (list<Vertex*>::iterator kid = temp.begin(); kid != temp.end(); kid++){
            revisionlist thiskid = evaGraphs(*kid);
            for (revisionlist::iterator it = thiskid.begin(); it != thiskid.end(); it++){

                if (v->isWitness()){
                    aux = v->getRevision(false);
                } else {
                    aux = *(new revision);
                }
                aux.splice(aux.begin(),(*it));
                out.push_back(aux);
            }
        }
    }

    return out;
}

revisionlist WitnessGraph::beta(Vertex* v){

    revisionlist out = *(new revisionlist);
    revision aux,aux1;
    if (v->getTail()->getConectivo()==C_NONE || (v->isWitness() && v->getTransition() == MAY)){
        aux = v->getRevision(true);
        aux1 = v->getRevision(false);
        if (aux.size() > 0) {
            out.push_back(aux);
        }
        out.push_back(aux1);
    }
    if(!v->isWitness() || (v->getTransition() == MAY && v->getTail()->getConectivo()!=C_NONE)){

        list<Vertex*> temp = v->getChildren();
        revisionlist aNow = *(new revisionlist);
        revisionlist aNext;
        aNow.push_back(*(new revision));
        for (list<Vertex*>::iterator kid = temp.begin(); kid != temp.end(); kid++){
            aNext = aNow;
            aNow = *(new revisionlist);
            //cout << v->getId() << " -> " << (*kid)->getId() << endl;
            revisionlist thiskid = evaGraphs(*kid);
            for (revisionlist::iterator it = aNext.begin(); it!=aNext.end();it++){
                for (revisionlist::iterator it1 = thiskid.begin(); it1 != thiskid.end(); it1++){
                    aux = (*it);
                    aux1 = (*it1);
                    aux.splice(aux.begin(),aux1);
                    aNow.push_back(aux);
                }
            }

        }
        out.splice(out.begin(),aNow);

    }
    //cout << v->getId()<< endl;
    return out;
}

comparation WitnessGraph::compare(revision rev1, revision rev2){
    comparation comp1;
    comparation comp2;
    comparation aux;
    comparation out;

    for(list<change>::iterator it1 = rev1.begin(); it1!=rev1.end(); it1++){
        aux = INCOMP;
        for(list<change>::iterator it2 = rev2.begin(); it2!=rev2.end(); it2++){
            if ((*it1).type == (*it2).type && (*it1).state1 == (*it2).state1 && (*it1).state2 == (*it2).state2 && (*it1).lit.literal.compare((*it2).lit.literal) && ((*it1).lit.valorLogico == (*it2).lit.valorLogico)){
                aux = LESS;
            }

        }
        if (aux == INCOMP){
            break;
        }
    }
    comp1 = aux;

    for (list<change>::iterator it1 = rev2.begin(); it1 != rev2.end(); it1++) {
        aux = INCOMP;
        for (list<change>::iterator it2 = rev1.begin(); it2 != rev1.end(); it2++) {
            if ((*it1).type == (*it2).type && (*it1).state1 == (*it2).state1 && (*it1).state2 == (*it2).state2 && (*it1).lit.literal.compare((*it2).lit.literal) && ((*it1).lit.valorLogico == (*it2).lit.valorLogico)) {
                aux = LESS;

            }

        }
        if (aux == INCOMP) {
            break;
        }
    }
    comp2 = aux;



    if (comp1 == LESS){
        if (comp2 == LESS){
            out = EQUAL;
        } else {
            out = LESS;
        }
    } else {
        if (comp2 == LESS){
            out = GREATER;
        } else {
            out = INCOMP;
        }
    }

    return out;
}

revisionlist WitnessGraph::minimals(revisionlist input) {
    revisionlist min = *(new revisionlist);
    for (revisionlist::iterator candidate = input.begin(); candidate != input.end(); candidate++) {
        revisionlist::iterator mini;
        for (mini = min.begin(); mini != min.end(); mini++) {
            comparation relation = compare((*candidate), (*mini));

            if (relation == GREATER) {
                break;
            } else if (relation == EQUAL) {
                min.push_front((*candidate));
                break;
            } else if (relation == LESS) {
                min.erase(mini);
            }
        }
        if (mini == min.end()) {
            min.push_front((*candidate));
        }

    }

    return min;
}

bool WitnessGraph::isConsistent(revision input){
    bool out = true;



    return out;
}

/* int main(int argc , char **argv){

	return 0;
} */

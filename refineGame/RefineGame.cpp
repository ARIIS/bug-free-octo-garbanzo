/*
 * File:   RefineGame.cpp
 * Author: jan
 *
 * Created on December 10, 2013, 4:58 PM
 */

#include "RefineGame.h"
#include "../modelChecking/ModelChecking.h"

RefineGame::RefineGame(Arena *arena) {

    this->arena = arena;

    list<Estado> *modeloFromArena = this->arena->getModelo();

    map<string, Estado*> mapModeloAuxiliar = *(new map<string, Estado*>);
    this->modelo = *(new list<Estado*>);

    for (list<Estado>::iterator itEst = modeloFromArena->begin();
            itEst != modeloFromArena->end(); itEst++) {
        this->modelo.push_back(&(*itEst));
    }


}

list<TestemunhaDeFalha> RefineGame::getFailWitness(Arena *arena) {

    list<TestemunhaDeFalha> testemunhasDeFalha = *(new list<TestemunhaDeFalha>);

        set < Configuracao*, bool(*)(Configuracao*, Configuracao*) > configs =
            arena->getIndefinedConfigs();

    list<Configuracao::TransicaoConfig*> testemunhas =
            *(new list<Configuracao::TransicaoConfig*>);

    TestemunhaDeFalha tFalha;
    Configuracao::TransicaoConfig *transConf;

    for (set < Configuracao*, bool(*)(Configuracao*, Configuracao*)>::iterator it = configs.begin();
            it != configs.end(); it++) {

        list<Configuracao::TransicaoConfig> filhos = (*it)->getFilhos();

        for (list<Configuracao::TransicaoConfig>::iterator it2 = filhos.begin();
                it2 != filhos.end(); it2++) {

            // TODO adicionar à tabela de relações de falha

            if ((it2)->destino->getCor() == C_INDEF &&
                    (it2)->destino->isLiteral()) {

                tFalha = *(new TestemunhaDeFalha);
                tFalha.origem = (*it);
                tFalha.isDuplicated = false;
                transConf = new Configuracao::TransicaoConfig;
                transConf->destino = it2->destino;
                transConf->isMust = it2->isMust;
                tFalha.destino = transConf; //&(*it2);
                testemunhasDeFalha.push_back(tFalha);
                //list<TestemunhaDeFalha>::iterator itAux = testemunhasDeFalha.end();
                //itAux--;
                //insertIntoRelatedFailTable(itAux);

                if ((*it)->getConectivo() == C_AX && !it2->isMust) {
                    tFalha = *(new TestemunhaDeFalha);
                    tFalha.origem = (*it);
                    tFalha.isDuplicated = true;
                    transConf = new Configuracao::TransicaoConfig;
                    transConf->destino = it2->destino;
                    transConf->isMust = it2->isMust;
                    tFalha.destino = transConf; //&(*it2);
                    testemunhasDeFalha.push_back(tFalha);
                    //list<TestemunhaDeFalha>::iterator itAux = testemunhasDeFalha.end();
                    //itAux--;
                    //insertIntoRelatedFailTable(itAux);
                }

            } else if (((*it)->getConectivo() == C_AX ||
                    (*it)->getConectivo() == C_EX) &&
                    !it2->isMust) {

                if (((*it)->getConectivo() == C_AX &&
                        (it2->destino->getCor() == C_FALSE ||
                        it2->destino->getCor() == C_INDEF)) ||
                        ((*it)->getConectivo() == C_EX &&
                        (it2->destino->getCor() == C_TRUE
                        || (it2->destino->getCor() == C_INDEF/* &&
                        it2->destino->isMaxFixPoint()*/)))
                        ) {

                    tFalha = *(new TestemunhaDeFalha);
                    tFalha.origem = (*it);
                    tFalha.isDuplicated = false;
                    transConf = new Configuracao::TransicaoConfig;
                    transConf->destino = it2->destino;
                    transConf->isMust = it2->isMust;
                    tFalha.destino = transConf;

                    //cout << " ++++++++++++++++++++++++++++++++++++++++  " << tFalha.destino->destino->toStr() << endl;
                    testemunhasDeFalha.push_back(tFalha);
                    //list<TestemunhaDeFalha>::iterator itAux = testemunhasDeFalha.end();
                    //itAux--;
                    //insertIntoRelatedFailTable(itAux);
                }

            }


        }



    }

    return testemunhasDeFalha;

}

void RefineGame::printModelWithRevision(revision mods){
    map<string,bool> usedliterals;
    for (list<Estado*>::iterator it = modelo.begin(); it != modelo.end(); it++){
        cout << (*it)->getNome() << "( " << (*it)->imprimirEstado();
        usedliterals = *(new map<string,bool>);
        for (revision::iterator it1 = mods.begin(); it1 != mods.end(); it1++){
            if ((*it1).type == 1 && (*it1).state1 == arena->namesToNumEstates((*it)->getNome()) && usedliterals.find((*it1).lit.literal) == usedliterals.end()){
                if (!((*it1).lit.valorLogico)){
                    cout << "not ";
                }

                cout << (*it1).lit.literal << " ";
                usedliterals[(*it1).lit.literal] = (*it1).lit.valorLogico;
            }
        }
        cout << ")" << endl;
    }
    int state1,state2;
    bool cut, must;
    list<Estado::Transicao> transitions;
    for (list<Estado*>::iterator it = modelo.begin(); it != modelo.end(); it++){
        transitions = (*it)->getTransicoes();
        for (list<Estado::Transicao>::iterator it1 = transitions.begin(); it1 != transitions.end(); it1++){
            cut = false;
            must = false;
            state1 = arena->namesToNumEstates((*it)->getNome());
            state2 = arena->namesToNumEstates((*it1).filho->getNome());
            for (revision::iterator it2 = mods.begin(); it2 != mods.end(); it2++){
                if (it2->state1 == state1 && it2->state2 == state2){
                    cut = it2->type == 5;
                    must = !cut;
                }
            }
            if (!cut){
                cout << "(" << (*it)->getNome() << "," << it1->filho->getNome() << ") : ";
                if ((it1)->tipo == MUST || must){
                    cout << "+";
                } else {
                    cout << "-";
                }
                cout << endl;
            }

        }
    }
}

void RefineGame::printAllRevisions(revisionlist input){
    int i = 0;
    for (revisionlist::iterator it = input.begin(); it != input.end(); it++){
        i++;
        cout << i << "."<< endl << endl;
        printModelWithRevision(*it);
        cout << endl << "----------------------------------------------------------" << endl;
    }
}

RefineGame::~RefineGame() {
}


/*
 * File:   RefineGame.h
 * Author: jan
 *
 * Created on December 10, 2013, 4:58 PM
 */

#ifndef REFINEGAME_H
#define	REFINEGAME_H

#include "../arena/Arena.h"
#include "../arena/Configuracao.h"
#include "../arena/Formula.h"
#include "../refineGame/Vertex.h"
#include "../arena/Estado.h"
// #include "FormulaBinaria.h"
// #include "FormulaPrefixa.h"

typedef struct {
    Configuracao *origem;
    Configuracao::TransicaoConfig *destino;
    bool isDuplicated;
} TestemunhaDeFalha;

typedef list< list<TestemunhaDeFalha>::iterator > listItTestFail;

typedef struct {
    mutable list<Configuracao*> confLiterais;
    mutable listItTestFail testemunhasFalhasRelacionadas;
} FalhasLiteral;

typedef struct {
    int numEstado;
    mutable list<Configuracao::TransicaoConfig*> transicoes;
    mutable listItTestFail testemunhasTransicoesRelacionadas;
} FalhasTransicoes;

typedef struct {
    set<FalhasLiteral, bool(*)(FalhasLiteral, FalhasLiteral) > literaisDeFalha;
    set <FalhasTransicoes, bool(*)(FalhasTransicoes, FalhasTransicoes) > transicoesDeFalha;
} TabelaConfigsDeFalhaRelacionadas;

using namespace ConstantConectivo;

typedef enum {
    OP_REMOVE_MAYG, OP_MAY_TO_MUST, OP_DEFN_LIT, OP_NULL
} Operation;

typedef struct {
    Operation operation;
    int from;
    int to;
    literalNegativo literal;

    void init(int x, int y, literalNegativo lit, Operation opX) {
        operation = opX;
        from = x;
        to = y;
        literal = lit;
    }

    void print() {
        if (operation == OP_DEFN_LIT) {
            cout << "DF _LIT " <<  ( (literal.valorLogico) ? " " : " not ") <<
                    literal.literal << endl;
            cout << to << endl;
        } else if (operation == OP_MAY_TO_MUST) {
            cout << "MAY_TO_MUST " << literal.literal << endl;
            cout << from << "  " << to << endl;
        } else if (operation == OP_REMOVE_MAYG) {
            cout << "REMOVE_MAY_G " << literal.literal << endl;
            cout << from << "  " << to << endl;
        }
    }

} OperationStruct;

typedef struct SetOperations {
    list<OperationStruct> removedMays;
    list<OperationStruct> transMaysToMus;
    list<OperationStruct> definedLiterals;

    void init() {
        this->removedMays = *(new list<OperationStruct>);
        this->transMaysToMus = *(new list<OperationStruct>);
        this->definedLiterals = *(new list<OperationStruct>);
    }

    void add(OperationStruct ops) {
        if (ops.operation == OP_DEFN_LIT) {
            this->definedLiterals.push_back(ops);
        } else if (ops.operation == OP_MAY_TO_MUST) {
            this->transMaysToMus.push_back(ops);
        } else if (ops.operation == OP_REMOVE_MAYG) {
            this->removedMays.push_back(ops);
        }
    }

    SetOperations copy() {
        SetOperations setOp = *(new SetOperations);

        setOp.init();

        for (list<OperationStruct>::iterator it = this->removedMays.begin();
                it != this->removedMays.end(); it++) {
            setOp.removedMays.push_back(*it);
        }

        for (list<OperationStruct>::iterator it = this->definedLiterals.begin();
                it != this->definedLiterals.end(); it++) {
            setOp.definedLiterals.push_back(*it);
        }

        for (list<OperationStruct>::iterator it = this->transMaysToMus.begin();
                it != this->transMaysToMus.end(); it++) {
            setOp.transMaysToMus.push_back(*it);
        }

        return setOp;

    }

    void print() {

        //cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
        for (list<OperationStruct>::iterator it = this->removedMays.begin();
                it != this->removedMays.end(); it++) {
            it->print();
        }

        for (list<OperationStruct>::iterator it = this->definedLiterals.begin();
                it != this->definedLiterals.end(); it++) {
            it->print();
        }

        for (list<OperationStruct>::iterator it = this->transMaysToMus.begin();
                it != this->transMaysToMus.end(); it++) {
            it->print();
        }
    }

} SetOperations;

class RefineGame {
public:

    list<TestemunhaDeFalha> getFailWitness(Arena *arena);
    void printAllRevisions(revisionlist input);
    RefineGame(Arena *arena);
    virtual ~RefineGame();


private:

    Arena *arena;
    list<TestemunhaDeFalha> testemunhasDeFalha;
    vector< TabelaConfigsDeFalhaRelacionadas> tabelaFalhasRelacionadas;
    list<Estado*> modelo;

    list<SetOperations> modificationsList;

    //list<TestemunhaDeFalha> getFailWitness(Arena *arena);
    void printModelWithRevision(revision mods);
    
    
    list<Estado> prepareModelToArena();




};

#endif	/* REFINEGAME_H */


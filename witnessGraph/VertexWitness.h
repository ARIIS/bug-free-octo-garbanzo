#ifndef VERTEXWITNESS_H
#define VERTEXWITNESS_H value

#include "Vertex.h"

class VertexWitness: public Vertex {

    private:
        Configuracao *tail;
        TipoTransicao transition;
        Change* mychange;

    public:
        VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
        Configuracao* getTail();
        TipoTransicao getTransition();
        bool isWitness();
        Change* getChange();
        void insertChange(Change* c);
};

#endif

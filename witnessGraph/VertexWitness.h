#ifndef VERTEXWITNESS_H
#define VERTEXWITNESS_H value

#include "Vertex.h"

class VertexWitness: public Vertex {

    private:
        Configuracao *tail;
        TipoTransicao transition;

    public:
        VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
        Configuracao* getTail();
        TipoTransicao getTransition();
        bool isWitness();
};

#endif

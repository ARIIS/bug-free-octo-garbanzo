#ifndef VERTEXWITNESS_H
#define VERTEXWITNESS_H value

#include "../refineGame/Vertex.h"

class VertexWitness: public Vertex {

    private:
        Configuracao *tail;
        TipoTransicao transition;

    public:
        VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
        Configuracao* getTail();
        TipoTransicao getTransition();
        bool isWitness();
        revision getRevision();
};

#endif

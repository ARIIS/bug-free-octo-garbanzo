#ifndef VERTEXWITNESS_H
#define VERTEXWITNESS_H value

#include "../refineGame/Vertex.h"
#include "../refineGame/RefineGame.h"

class VertexWitness: public Vertex {

    private:
        Configuracao *tail;
        TipoTransicao transition;
        bool duplicated;

    public:
        VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition);
        VertexWitness(Configuracao* head, Configuracao* tail, TipoTransicao transition, list<TestemunhaDeFalha> w);
        Configuracao* getTail();
        TipoTransicao getTransition();
        bool isWitness();
        revision getRevision(bool dupli);
        bool isDuplicated();
};

#endif

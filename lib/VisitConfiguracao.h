#ifndef VISITCONFIGURACAO_H
#define VISITCONFIGURACAO_H

#include "Path.h"

class VisitConfiguracao{
public:

    VisitConfiguracao (Configuracao *config, int numtab);
    void visit(Path *path);
    Path getPath();

private:
    Configuracao *configuracao;
    int numTab;
    bool visitado;
};

#endif

/*
 * File:   VisitTree.h
 * Author: jandson
 *
 * Created on 28 de Outubro de 2013, 18:05
 */

#ifndef VISITTREE_H
#define	VISITTREE_H

#include <string>
#include <iostream>

#include "../arena/Formula.h"
// #include "Configuracao.h"

using namespace std;

class VisitTree {

public:
    VisitTree(Formula *form, int numtab);
    void visit();

private:

    Formula *form;
    int numTab ;
};

#endif	/* VISITTREE_H */

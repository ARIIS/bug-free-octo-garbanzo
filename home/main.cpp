#include <cstdlib>
#include <iostream>
// #include "lex.yy.c"
#include "../modelChecking/Formula.h"
#include "../lib/VisitTree.h"
//#include "../read/scanner.c"
#include "../read/Leitor.h"
//#include "parser.h"
#include "../modelChecking/Configuracao.h"
#include "../modelChecking/ModelChecking.h"
#include "../refine/RefineGame.h"
#include <typeinfo>

#include <iostream>
#include <stdlib.h>


using namespace std;


//extern int yyparse();
//extern Formula *principal;

int  main(int argc , char **argv) {

        Leitor *lf = new Leitor(argv[1]);

        VisitTree *vs = new VisitTree(lf->lerFormulas(), 0);

        Formula *f = (new FormulaLiteral("p",true));

        Arena *ar = new Arena( lf->lerEstados(), lf->lerFormulas());

        ModelChecking mc(ar);

        mc.colorir();

        RefineGame rf = *(new RefineGame(ar,lf->lerEstados().size()));
	return 0;
}

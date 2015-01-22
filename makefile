# g++ main.cpp hello.cpp factorial.cpp -o hello

#target: dependencies
#   system command

# bison grammarFormulas.y
# flex lexicoFormulas.lex
# g++ -g -o parser *.cpp

CC=g++
CFLAGS= -c -Wall
LDFLAGS= -g -o

all: grammar lexic parser

grammar:
	cd parserFiles; bison grammarFormulas.y

lexic:
	cd parserFiles; flex lexicoFormulas.lex

parser: main.o Configuracao.o Estado.o Formula.o Leitor.o ModelChecking.o RefineGame.o VisitTree.o
	$(CC) home/main.o modelChecking/Configuracao.o modelChecking/Estado.o modelChecking/Formula.o read/Leitor.o modelChecking/ModelChecking.o refine/RefineGame.o lib/VisitTree.o -o parser

# agora temos que referencias os includes internos seguindo o novo sistema de diretórios
main.o: home/main.cpp
	cd home; $(CC) $(CFLAGS) main.cpp

Configuracao.o: Configuracao.cpp
	cd modelChecking; $(CC) $(CFLAGS) Configuracao.cpp

Estado.o: Estado.cpp
	cd modelChecking; $(CC) $(CFLAGS) Estado.cpp

Formula.o: Formula.cpp
	cd modelChecking; $(CC) $(CFLAGS) Formula.cpp

Leitor.o: Leitor.cpp
	cd read; $(CC) $(CFLAGS) Leitor.cpp

ModelChecking.o: ModelChecking.cpp
	cd modelChecking; $(CC) $(CFLAGS) ModelChecking.cpp

RefineGame.o: RefineGame.cpp
	cd refine; $(CC) $(CFLAGS) RefineGame.cpp

VisitTree.o: VisitTree.cpp
	cd lib; $(CC) $(CFLAGS) VisitTree.cpp

clean:
	rm -rf *o parser

cleanAll:
	rm -rf *o parser scanner.* *.tab.c

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
	bison grammarFormulas.y

lexic:
	flex lexicoFormulas.lex

parser: main.o Configuracao.o Arena.o Estado.o Formula.o Leitor.o ModelChecking.o RefineGame.o VisitTree.o
	$(CC) main.o Configuracao.o Arena.o Estado.o Formula.o Leitor.o ModelChecking.o RefineGame.o VisitTree.o -o parser

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Configuracao.o: Configuracao.cpp
	$(CC) $(CFLAGS) Configuracao.cpp

Arena.o: Arena.cpp
	$(CC) $(CFLAGS) Arena.cpp

Estado.o: Estado.cpp
	$(CC) $(CFLAGS) Estado.cpp

Formula.o: Formula.cpp
	$(CC) $(CFLAGS) Formula.cpp

Leitor.o: Leitor.cpp
	$(CC) $(CFLAGS) Leitor.cpp

ModelChecking.o: ModelChecking.cpp
	$(CC) $(CFLAGS) ModelChecking.cpp

RefineGame.o: RefineGame.cpp
	$(CC) $(CFLAGS) RefineGame.cpp

VisitTree.o: VisitTree.cpp
	$(CC) $(CFLAGS) VisitTree.cpp

clean:
	rm -rf *o parser

cleanAll:
	rm -rf *o parser scanner.* *.tab.c

# This file is part of Refiner Algorithm KMTS
#
#   Description: Makefile.
#   Author: Marino Souza [intmarinoreturn0@gmail.com] <@marinofull>
#   Date: 20 - 01 - 2015
#

#syntax
#
# target: dependencies
# [TAB]system command
#
# UPCASEWORD= means constant expression
#
# $^ is substituted with all of the target ’ s dependancy files
# $< is the first dependancy and $@ is the target files

# Marvin OS project example
# {
	# commit 883ef6021dcb87241827c7a1d79569b31d736027, diffview Makefile:
	# 26 -boot0.bin: mkbin
	# 27 -	nasm src/boot/boot0.asm -f bin -I src/boot/ -o bin/boot0.bin
	# 35 +bin/boot0.bin: src/boot/boot0.asm
	# 36 +	nasm $< -f bin -I src/boot/ -o $@

	# commit 36ed6176d622c9c9f6eee336d08a53120d092993, Makefile:
	# 64 %.o: %.c ${HEADERS}
	# 65 	$(CC) -o $@ -c $< $(INC_DIRS) $(CFLAGS)
# }

CC=g++
# CFLAGS= -c -Wall
CFLAGS= -c
LDFLAGS= -g -o
TREE=lib/VisitTree.cpp lib/VisitConfiguracao.cpp lib/Path.cpp
FORMULAS=Formula.cpp FormulaBinaria.cpp FormulaLiteral.cpp FormulaVariavel.cpp FormulaPrefixa.cpp FormulaPontoFixo.cpp
ARENA=Configuracao.cpp Componente.cpp Arena.cpp Estado.cpp
REFINE=RefineGame.cpp Vertex.cpp VertexWitness.cpp WitnessGraph.cpp
SOURCES=main.cpp ModelChecking.cpp $(ARENA) $(FORMULAS) $(TREE) $(REFINE) Leitor.cpp
GRAMMAR=
OBJECTS=$(addprefix bin/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=refiner


all: grammarlexic bin/ $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@
	# enjoy :D

# Regular Expression very OverPower
# bin/%.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@
# #
# the command above can replace each ones bellow.
# if you want undone this comment and comment the other ones, you can do, but i prefer keep the things as it is
#

bin/main.o: home/main.cpp
	$(CC) $(CFLAGS) $< -o $@

# lib folder
bin/%.o: lib/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# bin/VisitConfiguracao.o: lib/VisitConfiguracao.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Path.o: lib/Path.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# arena folder

bin/%.o: arena/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# bin/Estado.o: arena/Estado.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Configuracao.o: arena/Configuracao.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Componente.o: arena/Componente.cpp
# 	$(CC) $(CFLAGS) $< -o $@


# bin/Formula.o: arena/Formula.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/FormulaBinaria.o: arena/FormulaBinaria.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/FormulaLiteral.o: arena/FormulaLiteral.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/FormulaVariavel.o: arena/FormulaVariavel.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/FormulaPrefixa.o: arena/FormulaPrefixa.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/FormulaPontoFixo.o: arena/FormulaPontoFixo.cpp
# 	$(CC) $(CFLAGS) $< -o $@


# read folder

bin/Leitor.o: read/Leitor.cpp
	$(CC) $(CFLAGS) $< -o $@

# modelChecking folder

bin/ModelChecking.o: modelChecking/ModelChecking.cpp
	$(CC) $(CFLAGS) $< -o $@

# refineGame folder

bin/%.o: refineGame/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# other dependencies

bin/:
	mkdir bin

grammarlexic: read/grammarFormulas.tab.c read/scanner.c

read/grammarFormulas.tab.c: grammar/grammarFormulas.y
	bison $< -o $@

read/scanner.c: grammar/lexicoFormulas.lex
	flex $<

# every command above belongs to the tree of "all" command.
# from here, the commands below are independents.

clean: cleanBin cleanGrammar cleanTestResult

cleanBin:
	rm -rf bin/*.o $(EXECUTABLE)

cleanGrammar:
	rm -rf read/scanner.* read/*.tab.c

cleanTestResult:
	rm -rf sandbox/out-result*

# help

help:
	@echo "type 'make' to compile the toll"
	@echo "type 'make clean' to clear the binaries and grammar files"
	@echo "to run, type './refiner input'"

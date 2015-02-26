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
CFLAGS= -c -Wall
LDFLAGS= -g -o
SOURCES=home/main.cpp modelChecking/Configuracao.cpp modelChecking/Estado.cpp modelChecking/Formula.cpp read/Leitor.cpp modelChecking/ModelChecking.cpp refine/RefineGame.cpp lib/VisitTree.cpp
GRAMMAR=
OBJECTS=$(addprefix bin/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=refiner


all: grammarlexic bin/ $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

# Regular Expression very OverPower
# %.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@
# #
# the command above can replace the eight commands bellow.
# if you want undone this comment and comment the other ones, you can do, but i prefer keep the things as it is
#

bin/main.o: home/main.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/Configuracao.o: modelChecking/Configuracao.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/Estado.o: modelChecking/Estado.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/Formula.o: modelChecking/Formula.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/Leitor.o: read/Leitor.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/ModelChecking.o: modelChecking/ModelChecking.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/RefineGame.o: refine/RefineGame.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/VisitTree.o: lib/VisitTree.cpp
	$(CC) $(CFLAGS) $< -o $@

# every command above belongs to the tree of "all" command.
# from here, the commands below are independents.

grammarlexic: read/grammarFormulas.tab.c read/scanner.c

read/grammarFormulas.tab.c: parserFiles/grammarFormulas.y
	bison $<
	mv parserFiles/*.tab.c read

read/scanner.c: parserFiles/lexicoFormulas.lex
	flex $<
	mv scanner.* read

clean: cleanBin cleanGrammar

cleanBin:
	rm -rf bin/*.o $(EXECUTABLE)

cleanGrammar:
	rm -rf read/scanner.* read/*.tab.c

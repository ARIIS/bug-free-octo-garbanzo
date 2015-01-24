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
# $ ^ is substituted with all of the target ’ s dependancy files
# $ < is the first dependancy and $@ is the target files

# ---Some comments of help and learning---
#
# bison grammarFormulas.y
# flex lexicoFormulas.lex
# g++ -g -o parser *.cpp

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

all: grammarlexic mkbin refiner

grammarlexic: parserFiles/grammarFormulas.tab.c parserFiles/scanner

parserFiles/grammarFormulas.tab.c: parserFiles/grammarFormulas.y
	bison $<
	mv $@ read

parserFiles/scanner: parserFiles/lexicoFormulas.lex
	flex $<
	mv scanner.* read

mkbin:
	mkdir -p bin/

refiner: bin/main.o bin/Configuracao.o bin/Estado.o bin/Formula.o bin/Leitor.o bin/ModelChecking.o bin/RefineGame.o bin/VisitTree.o
	$(CC) $^ -o refiner

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

clean:
	rm -rf bin/*.o refiner

cleanAll:
	rm -rf bin/*.o refiner read/scanner.* read/*.tab.c

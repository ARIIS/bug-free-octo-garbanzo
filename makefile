# This file is part of Refiner Algorithm KMTS
#
#   Description: Makefile.
#   Author: Marino Souza <@marinofull>
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

# Marvin OS project example:
# boot0.bin: src/boot/boot0.asm
#   nasm src/boot/boot0.asm -f bin -I src/boot/ -o bin/boot0.bin
# bin/boot0.bin: src/boot/boot0.asm
#   nasm $< -f bin -I src/boot/ -o $@

CC=g++
CFLAGS= -c -Wall
LDFLAGS= -g -o

all: grammarlexic refiner

grammarlexic: parserFiles/grammarFormulas.tab.c parserFiles/scanner

# grammar:
# 	cd parserFiles; bison grammarFormulas.y

parserFiles/grammarFormulas.tab.c: parserFiles/grammarFormulas.y
	bison $<
	mv $@ read

# lexic:
# 	cd parserFiles; flex lexicoFormulas.lex

parserFiles/scanner: parserFiles/lexicoFormulas.lex
	flex $<
	mv scanner.* read

refiner: home/main.o modelChecking/Configuracao.o modelChecking/Estado.o modelChecking/Formula.o read/Leitor.o modelChecking/ModelChecking.o refine/RefineGame.o lib/VisitTree.o
	$(CC) $^ -o refiner

# agora temos que referencias os includes internos seguindo o novo sistema de diretórios
home/main.o: home/main.cpp
	$(CC) $(CFLAGS) $< -o $@

modelChecking/Configuracao.o: modelChecking/Configuracao.cpp
	$(CC) $(CFLAGS) $< -o $@

modelChecking/Estado.o: modelChecking/Estado.cpp
	$(CC) $(CFLAGS) $< -o $@

modelChecking/Formula.o: modelChecking/Formula.cpp
	$(CC) $(CFLAGS) $< -o $@

read/Leitor.o: read/Leitor.cpp
	$(CC) $(CFLAGS) $< -o $@

modelChecking/ModelChecking.o: modelChecking/ModelChecking.cpp
	$(CC) $(CFLAGS) $< -o $@

refine/RefineGame.o: refine/RefineGame.cpp
	$(CC) $(CFLAGS) $< -o $@

lib/VisitTree.o: lib/VisitTree.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o refiner

cleanAll:
	rm -rf *o refiner read/scanner.* read/*.tab.c
# lccgomes@gmail.com
# sbpc.net sociedade brasileira pelo progresso da ciência

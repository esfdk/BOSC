all: listmachine

LIBS=
CC = gcc

listmachine: listmachine.o -m32
	${CC} -m32 -Wall -o $@ listmachine.o

clean:
	rm -rf *o listmachine

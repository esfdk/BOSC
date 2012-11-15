all: listmachine

LIBS= -m32 -Wall
CC = gcc

listmachine: listmachine.o
	${CC} -o $@ listmachine.o ${LIBS}

listmachine.o: listmachine.c
	${CC} -c listmachine.c ${LIBS}

clean:
	rm -rf *.o listmachine
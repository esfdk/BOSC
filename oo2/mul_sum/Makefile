all: mulsum
LIBS= -lpthread -lm
CC = gcc
mulsum: mulsum.o
	${CC} -o $@ mulsum.o ${LIBS}
clean:
	rm -rf *o mulsum

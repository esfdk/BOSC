all: banker
LIBS= -lpthread -lm
CC = gcc
banker: banker.o
	${CC} -o $@ banker.o ${LIBS}
clean:
	rm -rf *o banker

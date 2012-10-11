all: mulsum
LIBS= -lpthread -lm
CC = gcc
mulsum: mulsum.o
	${CC} -o $@  ${LIBS} mulsum.o
clean:
	rm -rf *o mulsum

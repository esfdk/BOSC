all: 1 2 4 7 11 helloworld
LIBS= -lrt -lpthread -lm
CC=gcc

1: 1.o
	${CC} -o $@ 1.o ${LIBS}
2: 2.o
	${CC} -o $@ 2.o ${LIBS}
11: 11.o
	${CC} -o $@ 11.o ${LIBS}
7: 7.o
	${CC} -o $@ 7.o ${LIBS}
4: 4.o
	${CC} -o $@ 4.o ${LIBS}
helloworld: helloworld.o
	${CC} -o $@ helloworld.o ${LIBS}
clean:
	rm -rf *o 1 2 4 7 11

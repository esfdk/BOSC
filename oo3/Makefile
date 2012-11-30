all: lm1 lm2 lm3

LIBS= -m32 -Wall
CC = gcc

lm1: listmachineV1.o
	${CC} -o $@ listmachineV1.o ${LIBS}

listmachineV1.o: listmachineV1.c
	${CC} -c listmachineV1.c ${LIBS}

lm2: listmachineV2.o
	${CC} -o $@ listmachineV2.o ${LIBS}

listmachineV2.o: listmachineV2.c
	${CC} -c listmachineV2.c ${LIBS}

lm3: listmachineV3.o
	${CC} -o $@ listmachineV3.o ${LIBS}

listmachineV3.o: listmachineV3.c
	${CC} -c listmachineV3.c ${LIBS}

clean:
	rm -rf *.o lm1 lm2 lm3
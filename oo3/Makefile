all: listmachine

LIBS= -lreadline -ltermcap
CC = gcc

listmachine: listmachine.o ${OBJS}
	${CC} -o $@  ${LIBS} listmachine.o ${OBJS}

clean:
	rm -rf *o listmachine

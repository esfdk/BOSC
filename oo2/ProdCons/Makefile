all: prodcons

OBJS = List/list.o
LIBS = -lm -lpthread

fifoTestNoThreads: main.o ${OBJS}
	gcc -o $@ main.o ${OBJS} ${LIBS}
	
clean:
	rm -rf *o prodcons

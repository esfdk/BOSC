all: prodcons

OBJS = List/list.o
LIBS = -lrt -lpthread

prodcons: main.o ${OBJS}
	gcc -o $@ main.o ${OBJS} ${LIBS}
	
clean:
	rm -rf *o prodcons

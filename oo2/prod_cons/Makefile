all: prodcons

OBJS = List/list.o
LIBS = -lrt -lpthread

prodcons: prodCons.o ${OBJS}
	gcc -o $@ prodCons.o ${OBJS} ${LIBS}
	
clean:
	rm -rf *o prodcons

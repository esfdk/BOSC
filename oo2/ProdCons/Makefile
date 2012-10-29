all: prodcons

LIBS = -lm -lpthread

fifoTestNoThreads: main.o
	gcc -o $@ main.o ${LIBS}
	
clean:
	rm -rf *o prodcons

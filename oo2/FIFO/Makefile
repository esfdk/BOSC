all: fifo

OBJS = list.o test.o
LIBS = -lm -lpthread

fifo: main.o ${OBJS}
	gcc -o $@ main.o ${OBJS} ${LIBS}

clean:
	rm -rf *o fifo

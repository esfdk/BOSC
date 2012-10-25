all: fifo fifoThread

OBJS = list.o
LIBS = -lm -lpthread

fifo: main.o ${OBJS}
	gcc -o $@ main.o ${OBJS} ${LIBS}

fifoThread: test.o ${OBJS}
	gcc -o $@ test.o ${OBJS} ${LIBS}

clean:
	rm -rf *o fifo

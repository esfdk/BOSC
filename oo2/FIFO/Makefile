all: fifoTestNoThreads fifoTestThreads

OBJS = list.o
LIBS = -lm -lpthread

fifoTestNoThreads: testNoThreads.o ${OBJS}
	gcc -o $@ testNoThreads.o ${OBJS} ${LIBS}

fifoTestThreads: testThreads.o ${OBJS}
	gcc -o $@ testThreads.o ${OBJS} ${LIBS}

clean:
	rm -rf *o fifo

all: a.out

a.out: queue.o
	gcc -o a.out queue.o

queue.o: queue.o
	gcc -c queue.c

clean:
	rm queue.o a.out

run: a.out
	a.out

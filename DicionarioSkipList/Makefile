all: main.o skiplist.o
	gcc -o main main.o skiplist.o

main.o: main.c skiplist.h
	gcc -c main.c

cartas.o: skiplist.c skiplist.h
	gcc -c skiplist.c

run:
	./main

clean:
	rm *.o main
all: main.o spot.o
	gcc -o main main.o spot.o

main: main.c spot.h
	gcc -c main.c

spot: spot.c spot.h
	gcc -c spot.h

run:
	./main

clear:
	rm *.o main
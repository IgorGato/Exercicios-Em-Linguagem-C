all: main.o sub.o
	gcc -o main main.o sub.o

main.o: main.c sub.h
	gcc -c main.c

sub.o: sub.c sub.h
	gcc -c sub.c

run:
	./main

clean:
	rm *.o main
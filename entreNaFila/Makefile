all: main.o covid.o
	gcc -o main main.o covid.o

main.o: main.c covid.h
	gcc -c main.c

cartas.o: covid.c covid.h
	gcc -c covid.c

run:
	./main

clean:
	rm *.o main
all: main.o cartas.o
	gcc -o main main.o cartas.o

main.o: main.c cartas.h
	gcc -c main.c

cartas.o: cartas.c cartas.h
	gcc -c cartas.c

run:
	./main

clean:
	rm *.o main

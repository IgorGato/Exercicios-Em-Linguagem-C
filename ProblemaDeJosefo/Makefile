all: main.o josefo.o
	gcc -o main main.o josefo.o

main: main.c josefo.h
	gcc -c main.c

josefo: josefo.c josefo.h
	gcc -c josefo.c

run:
	./main

clean: rm *.o main


all: main.o back.o
	gcc -o main main.o back.o

main: main.c back.h
	gcc -c main.c

back: back.c back.h
	gcc -c back.c

run:
	./main

clean: rm *.o main

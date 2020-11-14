all: main.o GrandesNumeros.o
	gcc -o main main.o GrandesNumeros.o

main: main.c GrandesNumeros.h
	gcc -c main.c

bnumbers: GrandesNumeros.c GrandesNumeros.h
	gcc -c GrandesNumeros.c

run:
	./main

clear: 
	rm *.o main
all: main.o rubro_negra.o
	gcc -o main main.o rubro_negra.o

main.o: main.c rubro_negra.h
	gcc -c main.c

rubro_negra.o: rubro_negra.c rubro_negra.h
	gcc -c rubro_negra.c

run:
	./main

clean:
	rm *.o main
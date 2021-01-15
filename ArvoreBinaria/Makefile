all: main.o ab_print.o
	gcc -o main main.o ab_print.o

main.o: main.c ab_print.h
	gcc -c main.c

ab_print.o: ab_print.c ab_print.h
	gcc -c ab_print.c

run:
	./main

clean:
	rm *.o main
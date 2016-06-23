FLAGS=-Wextra -Wall -Werror -pedantic -std=c99 -lm

all: start

start: main.o complex.o smatrix.o queue.o
	gcc $(FLAGS) -o kp7 complex.o smatrix.o queue.o main.o

main.o: main.c
	gcc -c $(FLAGS) main.c

complex.o: complex.c
	gcc -c $(FLAGS) complex.c

smatrix.o: smatrix.c
	gcc -c $(FLAGS) smatrix.c

queue.o: queue.c
	gcc -c $(FLAGS) queue.c

clear:
	-rm -f *.o *.gch kp8
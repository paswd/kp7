FLAGS=-Wextra -Wall -Werror -pedantic -std=c99

all: start

start: main.o complex.o
	gcc $(FLAGS) -o kp7 complex.o main.o

main.o: main.c
	gcc -c $(FLAGS) main.c

complex.o: complex.c
	gcc -c $(FLAGS) complex.c

clear:
	-rm -f *.o *.gch kp8
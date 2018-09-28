CFLAGS = -g -Wall -pedantic

CircuitRouter-SeqSolver: coordinate.o grid.o CircuitRouter-SeqSolver.o maze.o router.o lib/list.o lib/pair.o lib/queue.o lib/vector.o -lm

coordinate.o: coordinate.c
	gcc $(CFLAGS) -c coordinate.c -o coordinate.o
grid.o: grid.c grid.h coordinate.h lib/types.h lib/vector.h
	gcc $(CFLAGS) -c grid.c -o grid.o
CircuitRouter-SeqSolver.o: CircuitRouter-SeqSolver.c lib/list.h grid.h maze.h router.h lib/timer.h lib/types.h
	gcc $(CFLAGS) -c CircuitRouter-SeqSolver.c -o CircuitRouter-SeqSolver.o
maze.o: maze.c maze.h coordinate.h grid.h lib/list.h lib/queue.h lib/pair.h lib/types.h lib/vector.h
	gcc $(CFLAGS) -c maze.c -o maze.o

router.o: router.c router.h coordinate.h grid.h lib/queue.h lib/vector.h
	gcc $(CFLAGS) -c router.c -o router.o

list.o: lib/list.c lib/list.h lib/types.c
	gcc $(CFLAGS) -c list.c -o list.o

pair.o: lib/pair.c lib/pair.h
	gcc $(CFLAGS) -c lib/par.c -o pair.o

queue.o: lib/queue.c lib/queue.h lib/types.h
	gcc $(CFLAGS) -c lib/queue.c -o queue.o

vector.o: lib/vector.c lib/vector.h lib/utility.h
	gcc $(CFLAGS) -c lib/vector.c -o vector.o

clean:
	rm -f *.o lib/*.o CircuitRouter-SeqSolver


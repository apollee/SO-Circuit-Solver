CFLAGS = -Wall -g -std=gnu99 -pthread
SOURCES=$(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o) $(wildcard ../lib/*.o)
CC = gcc

all: $(OBJS)

list.o: list.c list.h types.h
pair.o: pair.c pair.h
queue.o: queue.c queue.h types.h
vector.o: vector.c vector.h types.h utility.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)

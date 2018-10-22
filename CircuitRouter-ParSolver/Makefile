CFLAGS = -Wall -g -std=gnu99
TARGET = CircuitRouter-ParSolver
SOURCES=$(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o) $(wildcard ../lib/*.o)
CC = gcc
LDFLAGS=-lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) 

CircuitRouter-ParSolver.o: CircuitRouter-ParSolver.c
$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)

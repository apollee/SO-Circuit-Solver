CFLAGS = -Wall -g -std=gnu99
TARGET = CircuitRouter-SimpleShell
SOURCES=$(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o) $(wildcard ../lib/*.o)
CC = gcc
LDFLAGS=-lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) 

commandlinereader.o: commandlinereader.c commandlinereader.h
link.o: link.c link.h CircuitRouter-SimpleShell.h
CircuitRouter-SimpleShell.o: CircuitRouter-SimpleShell.c CircuitRouter-SimpleShell.h commandlinereader.h link.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)

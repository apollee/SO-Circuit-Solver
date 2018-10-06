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
run_command.o: run_command.c run_command.h ../lib/list.h
CircuitRouter-SimpleShell.o: CircuitRouter-SimpleShell.c ../lib/timer.h commandlinereader.h run_command.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)

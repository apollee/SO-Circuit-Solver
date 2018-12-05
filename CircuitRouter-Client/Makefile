# Makefile, versao 1
# Sistemas Operativos, DEI/IST/ULisboa 2018-19

SOURCES = CircuitRouter-Client.c 
SOURCES+= lib/commandlinereader.c ../lib/library.c
OBJS = $(SOURCES:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -std=gnu99 -I../
LDFLAGS=-lm
TARGET = CircuitRouter-Client

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) 

CircuitRouter-Client.o: CircuitRouter-Client.c lib/commandlinereader.h ../lib/library.h
lib/commandlinereader.o: lib/commandlinereader.c lib/commandlinereader.h
../lib/library.o: ../lib/library.c ../lib/library.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

CircuitRouter-SeqSolver:
	(cd ../CircuitRouter-SeqSolver/ && make)

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)
	rm file*
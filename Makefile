VPATH = ./src
CC = gcc
CFLAGS= -Wall -pedantic -Wextra -Wconversion -std=gnu11 
BIN = ./bin

all: server

server: server.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@ -lulfius -ljansson -lorcania

server.o: server.c
	$(CC) $(CFLAGS) -c $< -o $@ -lulfius -ljansson -lorcania


clean:
	rm *.o $(BIN)/server*

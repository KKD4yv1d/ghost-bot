CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -I include/
LDFLAGS = -lcurl -ldiscord
EXEC = bot
SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard **/**/*.c) $(wildcard **/**/**/*.c) $(wildcard **/**/**/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

all: dirs build

dirs:
	mkdir -p $(BIN)/

build: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/$(EXEC) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -f $(OBJ)
	rm -f $(BIN)/*

mrproper: clean

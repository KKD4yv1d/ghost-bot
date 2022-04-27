CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -I include/ -I ../concord/include -I ../concord/lib
LDFLAGS = -lcurl -ldiscord -L ../concord/include -L ../concord/lib
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

CC = gcc
CFLAGS = -g -O3 -Wall -Wstrict-prototypes -I include/
LDFLAGS = -L/usr/local/lib -ldiscord -lcurl -lhiredis -lpthread -pthread -lm

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) \
			$(wildcard src/**/**/**/*.c) $(wildcard src/**/**/**/**/*.c)         \
			$(wildcard src/**/**/**/**/**/*.c) $(wildcard src/**/**/**/**/**/**/*.c)
HDR = $(wildcard include/*.h) $(wildcard include/**/*.h) $(wildcard include/**/**/*.h) \
			$(wildcard include/**/**/**/*.h) $(wildcard include/**/**/**/**/*.h)         \
			$(wildcard include/**/**/**/**/**/*.h) $(wildcard include/**/**/**/**/**/**/*.h)

OBJ = $(SRC:.c=.o)

all: mkdirs compile_bin

mkdirs:
	mkdir -p bin

clean:
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

compile_bin: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/bot $(OBJ)

lint:
	clang-tidy $(SRC) $(HDR) -- -I include/

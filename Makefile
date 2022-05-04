CC = gcc
CFLAGS = -g -O3 -Wall -Wstrict-prototypes -I include/
LDFLAGS = -L/usr/local/lib -ldiscord -lcurl -lhiredis -lpthread -pthread

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) \
			$(wildcard src/**/**/**/*.c) $(wildcard src/**/**/**/**/*.c)         \
			$(wildcard src/**/**/**/**/**/*.c) $(wildcard src/**/**/**/**/**/**/*.c)
HDR = $(wildcard include/*.h) $(wildcard include/**/*.h) $(wildcard include/**/**/*.h) \
			$(wildcard include/**/**/**/*.h) $(wildcard include/**/**/**/**/*.h)         \
			$(wildcard include/**/**/**/**/**/*.h) $(wildcard include/**/**/**/**/**/**/*.h)

OBJ = $(SRC:.c=.o)

all: msg_start mkdirs compile_bin msg_end

mkdirs:
	mkdir -p bin

clean:
	rm -f $(OBJ)

msg_start:
	@echo "\033[38;2;200;200;200m-- Compiling... ------------------------\033[0m"

%.o: %.c
	@echo "\033[38;2;255;255;150m[*] Compiling $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

compile_bin: $(OBJ)
	@echo "\033[38;2;100;255;190m-- Linking bin/bot... ------------------\033[0m"
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/bot $(OBJ)

msg_end:
	@echo "\033[38;2;100;255;150m-- Compilation done! -------------------\033[0m"

lint:
	clang-tidy $(SRC) $(HDR) -- -I include/

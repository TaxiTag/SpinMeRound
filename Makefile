CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=undefined,address -g
FILES = init.o main.o payload.o settle.o
RM = rm
RM_FLAGS = -rf
TARGET = spin_me_round

all: confloose sanitize clean


# Building the confloose itself
confloose: settle_o payload_o main_o init_o
	$(CC) $(CFLAGS) $(FILES) -o $(TARGET)

init_o:
	$(CC) -c src/confloose/init.c

main_o:
	$(CC) -c src/confloose/main.c

payload_o:
	$(CC) -c src/confloose/payload.c

settle_o:
	$(CC) -c src/confloose/settle.c

# Building the sanitizer
sanitize:
	$(CC) $(CFLAGS) src/sanitize/sanitize.c -o sanitizer

.PHONY: clean

clean:
	$(RM) $(RM_FLAGS) $(FILES)
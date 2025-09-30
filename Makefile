CC=gcc
CFLAGS=-Wall -Wextra -g

all: shell

shell: shell.c
	$(CC) $(CFLAGS) -o shell shell.c

clean:
	rm -f shell

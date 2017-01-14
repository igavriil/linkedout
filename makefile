CC=gcc
CFLAGS=-O3

all: linkedout

linkedout:
	$(CC) $(CFLAGS) *.c -o linkedout

clean:
	rm linkedout


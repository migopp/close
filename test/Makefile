all:
	mkdir -p bin
	$(CC) -Wall -Wextra -O0 -g -std=c99 -fsanitize=address,undefined -o bin/test ../target/close.o test.c

clean:
	rm -rf bin

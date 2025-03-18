all:
	mkdir -p bin
	$(CC) -Wall -Wextra -O0 -g -std=c99 -o bin/test ../target/close.o test.c

dump:
	objdump -d ./bin/test > ./bin/test.dump

clean:
	rm -rf bin

.phony: all, dump, clean

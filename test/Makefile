all:
	mkdir -p bin
	$(CC) -Wall -Wextra -O0 -g -std=c99 -o bin/build build.c
	./bin/build

dump: ./bin/test
	objdump -d ./bin/test > ./bin/test.dump

clean:
	rm -rf bin

.phony: all, clean

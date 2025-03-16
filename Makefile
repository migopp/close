CC					= gcc
D_FLAGS				= -Wall -Wextra -O0 -g -std=c99 -fsanitize=address,undefined
R_FLAGS				=

TARGET				= target
CLOSE				= close.c
CLOSE_O				= close.o

all: close

close:
	@mkdir -p $(TARGET)
	gcc -c $(D_FLAGS) -o $(TARGET)/$(CLOSE_O) $(CLOSE);

clean:
	rm -rf $(TARGET)

.phony: all, close, clean


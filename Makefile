CC					= gcc
D_FLAGS				= -Wall -Wextra -O0 -g -std=c99 -fsanitize=address,undefined
R_FLAGS				=

TARGET				= target
CLOSE_C				= close.c
CLOSE_O				= close.o

all: $(TARGET)/$(CLOSE_O)

$(TARGET)/$(CLOSE_O): $(CLOSE_C)
	@mkdir -p $(TARGET)
	gcc -c $(D_FLAGS) -o $(TARGET)/$(CLOSE_O) $(CLOSE_C);

clean:
	rm -rf $(TARGET)

.phony: all, clean


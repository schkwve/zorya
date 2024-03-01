UNAME_S = $(shell uname -s)

DEBUG ?= y

CC = clang
CFLAGS  =  -Isrc -Ilib/glad/include -Ilib/glfw/include -Ilib/stb
LDFLAGS =  lib/glad/src/glad.o lib/glfw/src/libglfw3.a -lm

ifeq ($(DEBUG),y)
CFLAGS += -D__DEBUG -g
LDFLAGS += -g # symbols and shit
endif

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread -lGL
endif

SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs libs game

libs:
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/glfw && cmake . && make
dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/SusieBrowser

game: $(OBJ)
	@echo "  [LINK] $(BIN)/SusieBrowser"
	@$(CC) -o $(BIN)/SusieBrowser $^ $(LDFLAGS)

%.o: %.c
	@echo "  [  CC] $@"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

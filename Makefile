UNAME_S = $(shell uname -s)

CC = clang
CPP = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wno-newline-eof
CFLAGS += -Ilib -Ilib/flgl/inc -Ilib/flgl/lib/glfw/include -Ilib/flgl/lib/glad/include -Ilib/flgl/lib/glm/ -Ilib/flgl/lib/stb
LDFLAGS = lib/flgl/lib/glad/src/glad.o lib/flgl/lib/glfw/src/libglfw3.a
LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) 
LIBSRC = $(wildcard lib/**/**/*.cpp) $(wildcard lib/**/*.cpp) 
OBJ = $(SRC:.cpp=.o)
LIBOBJ = $(LIBSRC:.cpp=.o)
BIN = bin

.PHONY: all clean subs init a r

r: a run

run: adrift
	$(BIN)/adrift

subs:
	git submodule update --remote --init --recursive

build: libs adrift

all: dirs subs libs adrift

dirs:
	mkdir -p ./$(BIN)

libs:
	cd lib/flgl/lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/flgl/lib/glfw && cmake . && make

a: adrift

adrift: $(OBJ) $(LIBOBJ)
	$(CPP) -o $(BIN)/adrift $^ $(LDFLAGS)

%.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ) ./lib/flgl/lib/glfw/CMakeCache.txt

trim:
	rm -rf ./lib/flgl/lib/glfw/tests ./lib/flgl/lib/glfw/examples ./lib/flgl/lib/glm/test


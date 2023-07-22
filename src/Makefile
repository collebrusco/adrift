# # EXAMPLE 1 build flgl, glad & glfw into dylib & link
# UNAME_S = $(shell uname -s)

# CC = clang++
# CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wno-newline-eof -Wno-unused-parameter
# CFLAGS += -Ilib/flgl/inc -Ilib/flgl/lib/glfw/include -Ilib/flgl/lib/glm/
# LDFLAGS = -Llib/flgl/bin/ -lflgl -Wl,-rpath,./lib/flgl/bin

# .PHONY: all clean

# TARGET = risklike
# SRC = main.cpp $(wildcard lib/flgl/src/*.cpp) 
# OBJ = $(SRC:.cpp=.o)
# BIN = bin

# all: libs $(OBJ)
# 	 clang++ -o $(TARGET) $(OBJ) $(LDFLAGS)

# libs: 
# 	cd lib/flgl && make dylib

# %.o: %.cpp
# 	$(CC) -o $@ -c %< $(CFLAGS)

# clean:
# 	cd lib/flgl && make clean
# 	rm ./risklike


# EXAMPLE 2 build flgl, glad & glfw with your project
UNAME_S = $(shell uname -s)

CC = clang
CPP = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wno-newline-eof
CFLAGS += -Ilib/flgl/inc -Ilib/flgl/lib/glfw/include -Ilib/flgl/lib/glad/include -Ilib/flgl/lib/glm/ -Ilib/flgl/lib/stb
LDFLAGS = lib/flgl/lib/glad/src/glad.o lib/flgl/lib/glfw/src/libglfw3.a
LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa

SRC = $(wildcard ./*.cpp) $(wildcard ./**/*.cpp) $(wildcard lib/flgl/src/*.cpp) $(wildcard lib/**/*.cpp) 
OBJ = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: dirs libs risklike

dirs:
	mkdir -p ./$(BIN)

libs:
	git submodule update --remote --init --recursive
	cd lib/flgl/lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/flgl/lib/glfw && cmake . && make

risklike: $(OBJ)
	$(CPP) -o $(BIN)/risklise $^ $(LDFLAGS)

%.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ) 



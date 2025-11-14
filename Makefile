CXX = clang++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Iinclude

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

TARGET = bin/borgc

all: dirs $(TARGET)  

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs: 
	mkdir -p build
	mkdir -p bin

clean:
	rm -rf build bin
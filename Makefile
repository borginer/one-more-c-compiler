CXX = clang++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Iinclude -MMD -MP

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
DEP = $(OBJ:.o=.d)

TARGET = bin/omcc

all: dirs $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

dirs:
	mkdir -p build
	mkdir -p bin

clean:
	rm -rf build bin
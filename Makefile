CC = clang++
CFLAGS = -Wextra -Wall -std=c++17
ROOT = src
BIN = bin
OBJS=$(BIN)/main.o

main: main.o tokenizer.o utils.o
	$(CC) $(CFLAGS) -o main main.o tokenizer.o utils.o

main.o: $(ROOT)/main.cpp 
	$(CC) $(CFLAGS) -c $(ROOT)/main.cpp

tokenizer.o: $(ROOT)/tokenizer.cpp utils.o
	$(CC) $(CFLAGS) -c $(ROOT)/tokenizer.cpp

utils.o: $(ROOT)/utils.cpp
	$(CC) $(CFLAGS) -c $(ROOT)/utils.cpp

clean:
	rm -rf *.o
	rm main	
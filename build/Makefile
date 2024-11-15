CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion
CFLAGS += -I/opt/homebrew/Cellar/sfml/2.6.1/include -I../lib
BIN = ./bin

LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window

SRC = $(wildcard ../src/**/*.cpp ../src/*.cpp)

.PHONY: clean

run:
	mkdir -p $(BIN)
	$(CC) $(SRC) -o $(BIN)/main $(CFLAGS) $(LDFLAGS)
	./$(BIN)/main
	
clean:
	clear && rm -rf $(BIN) && rm -rf $(SPV)
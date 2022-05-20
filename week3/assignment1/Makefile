
SRC = src
SOURCES=$(SRC)/main.cpp $(SRC)/Graph.cpp $(SRC)/DijkstraAlgorithm.cpp
FLAGS= -g -Werror
INC = include/
BUILD = bin
OUT = $(BUILD)/dijkstraalgorithm

all: main.o Graph.o DijkstraAlgorithm.o
	g++ $(FLAGS) main.o Graph.o DijkstraAlgorithm.o -o $(OUT)

main.o: $(SRC)/main.cpp
	g++ -c $(SRC)/main.cpp -I$(INC)

Graph.o: $(SRC)/Graph.cpp $(INC)/Graph.hpp
	g++ -c $(SRC)/Graph.cpp -I$(INC)

DijkstraAlgorithm.o: $(SRC)/DijkstraAlgorithm.cpp $(INC)/DijkstraAlgorithm.hpp
	g++ -c $(SRC)/DijkstraAlgorithm.cpp -I$(INC)

clean:
	rm *.o
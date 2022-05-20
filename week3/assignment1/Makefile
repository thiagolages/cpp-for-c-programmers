
SOURCES=main.cpp Graph.cpp DijkstraAlgorithm.cpp
FLAGS= -g -Werror

all: 
	g++ $(FLAGS) $(SOURCES) -o main

main: main.o Graph.o DijkstraAlgorithm.o
	g++ main.o Graph.o DijkstraAlgorithm.o -o main

main.o: main.cpp
	g++ -c main.cpp

Graph.o: Graph.cpp Graph.hpp
	g++ -c Graph.cpp

DijkstraAlgorithm.o: DijkstraAlgorithm.cpp DijkstraAlgorithm.hpp
	g++ -c DijkstraAlgorithm.cpp

clean:
	rm *.o
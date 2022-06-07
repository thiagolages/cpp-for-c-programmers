GRAPH_SRC_DIR=../week3/assignment1/src
GRAPH_INCLUDE_DIR=../week3/assignment1/include

all:
	make MinimumSpanningTree

MinimumSpanningTree: MinimumSpanningTree.cpp Graph.o
	g++ MinimumSpanningTree.cpp Graph.o -o MinimumSpanningTree

Graph.o:
	g++ -c $(GRAPH_SRC_DIR)/Graph.cpp -I$(GRAPH_INCLUDE_DIR)

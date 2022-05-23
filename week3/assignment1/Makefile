
SRC = src
TEST = test
SOURCES=$(SRC)/main.cpp $(SRC)/Graph.cpp $(SRC)/DijkstraAlgorithm.cpp
LIBS = /usr/local/lib/libgtest_main.a -lgtest
INC = include/
BUILD = bin
OUT = $(BUILD)/dijkstraalgorithm
OUT_TEST = $(BUILD)/test_dijkstraalgorithm

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /usr/local/include/gtest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/*.h \
                $(GTEST_DIR)/internal/*.h

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Werror -Wextra -pthread # -Wall can be used instead of -Werror

GTEST_LIB = gtest_main.a

all: main tests

main: $(SRC)/main.cpp Graph.o DijkstraAlgorithm.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC)/main.cpp Graph.o DijkstraAlgorithm.o -I$(INC) -o $(OUT) $(LIBS)

Graph.o: $(SRC)/Graph.cpp $(INC)/Graph.hpp
	$(CXX) -c $(SRC)/Graph.cpp -I$(INC)

DijkstraAlgorithm.o: $(SRC)/DijkstraAlgorithm.cpp $(INC)/DijkstraAlgorithm.hpp
	$(CXX) -c $(SRC)/DijkstraAlgorithm.cpp -I$(INC)

# TESTS
tests: GraphTest.o Graph.o DijkstraAlgorithm.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) GraphTest.o Graph.o DijkstraAlgorithm.o -o $(OUT_TEST) -I$(INC) $(LIBS) -I$(GTEST_HEADERS)

GraphTest.o: $(TEST)/GraphTest.cpp Graph.o
	$(CXX) -c $(TEST)/GraphTest.cpp -I$(INC)

clean:
	rm *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
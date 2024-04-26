CXX = g++
CXXFLAGS = -std=c++11 -Wall -ggdb

SOURCES = SplayTree.cpp splay_tree_test.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

all: splay_tree_test.exe forest_test.exe forest_time.exe

splay_tree_test.exe: SplayTree.o splay_tree_test.o
	$(CXX) $(CXXFLAGS) -o $@ SplayTree.o splay_tree_test.o

forest_test.exe: Forest.o SplayTree.o forest_test.o
	$(CXX) $(CXXFLAGS) -o $@ Forest.o SplayTree.o forest_test.o

forest_time.exe: Forest.o SplayTree.o forest_time.o
	$(CXX) $(CXXFLAGS) -o $@ Forest.o SplayTree.o forest_time.o

.cpp.o: 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.exe *.o


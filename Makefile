CXX = g++
CXXFLAGS = -std=c++11 -Wall -ggdb

SOURCES = SplayTree.cpp splay_tree_test.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

all: splay_tree_test.exe

test: splay_tree_test.exe

splay_tree_test.exe: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

.cpp.o: 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f splay_tree_test.exe $(OBJECTS)


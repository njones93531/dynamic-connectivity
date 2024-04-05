CXX = g++
CXXFLAGS = -std=c++11 -Wall

SOURCES = SplayTree.cpp splay_tree_test.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

all: splay_tree_test

test: splay_tree_test

splay_tree_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

.cpp.o: 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)


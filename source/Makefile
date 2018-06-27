HEADERS = graph.h kruskal.h ufs.h
OBJECTS = graph.o kruskal.o ufs.o
SOURCES = graph.cpp kruskal.cpp ufs.cpp

CXXC = g++
CXXFLAGS = -std=c++11 -O2

DEL = rm -rf

all: $(OBJECTS)

%.o: %.cpp %.h Makefile
	$(CXXC) $(CXXFLAGS) -c $*.cpp -o $*.o

clean:
	-$(DEL) *.o

rebuild:
	make clean
	make all

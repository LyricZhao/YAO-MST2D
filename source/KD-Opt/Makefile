HEADERS = kdTree.h
OBJECTS = kdTree.o
SOURCES = kdTree.cpp

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

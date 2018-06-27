APP_NAME = main

SOURCE_DIR = ../source
KD_SOURCE_DIR = ../source/KD-Opt
SOURCE_OBJS = $(SOURCE_DIR)/graph.o $(SOURCE_DIR)/kruskal.o $(SOURCE_DIR)/ufs.o $(SOURCE_DIR)/cell.o $(SOURCE_DIR)/2d_Solver.o $(KD_SOURCE_DIR)/kdTree.o
TESTING_OBJS = main.o rand.o time.o normal_Solver.o

CXXC = g++-7
CXXFLAGS = -std=c++11 -O2 -fopenmp
LINKFLAGS = -fopenmp

DEL = rm -rf

$(APP_NAME): $(SOURCE_OBJS) $(TESTING_OBJS) Makefile
	$(CXXC) $(LINKFLAGS) $(SOURCE_OBJS) $(TESTING_OBJS) -o main

$(APP_NAME).o: $(APP_NAME).cpp Makefile # no need for header
	$(CXXC) $(CXXFLAGS) -c $(APP_NAME).cpp -o $(APP_NAME).o

%.o: %.cpp %.h Makefile
	$(CXXC) $(CXXFLAGS) -c $*.cpp -o $*.o

clean:
	-$(DEL) $(KD_SOURCE_DIR)/*.o
	-$(DEL) $(SOURCE_DIR)/*.o
	-$(DEL) *.o
	-$(DEL) ./$(APP_NAME)

run:
	make
	./$(APP_NAME)

rebuild:
	make clean
	make $(APP_NAME)

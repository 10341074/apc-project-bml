CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -march=native -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
CXXGLAGS_OMP = -fopenmp -openmp
MPICXX = mpic++

INCLUDE_DIR = include
INCLUDE_MATRIX = include/matrix

_DEPS = Template.h Color.h Car.h Tokenize.h Traffic.h
_DEPS_MATRIX = Row.h DynRow.h VecVector.h Col.h DynRowDeque.h
_DEPS_MATRIX += VecVectorS.h VecVectorD.h

DEPS = $(patsubst %, $(INCLUDE_DIR)/%,  $(_DEPS)) $(patsubst %, $(INCLUDE_MATRIX)/%, $(_DEPS_MATRIX))

SRC_DIR = src
SRC_MATRIX_DIR = src/matrix

OBJ_DIR = obj
OBJ_MATRIX_DIR = obj/matrix

_OBJ = main.o Tokenize.o Traffic.o
_OBJ_MATRIX = Row.o DynRow.o VecVector.o Col.o DynRowDeque.o
_OBJ_MATRIX += VecVectorS.o VecVectorD.o

OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ)) $(patsubst %, $(OBJ_MATRIX_DIR)/%, $(_OBJ_MATRIX))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_MATRIX_DIR)/%.o : $(SRC_MATRIX_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
apcbml_st: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
run:
	./apcbml_st data/problem.csv
distclean:
	-rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~
clean:
	-rm apcbml_* $(OBJ_DIR)/*.o $(OBJ_MATRIX_DIR)/*.o
	-rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~ *.csv 


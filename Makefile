CXX = g++
CXXFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -march=native -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
CXXGLAGS_OMP = -fopenmp -openmp
MPICXX = mpic++

INCLUDE_DIR = include
INCLUDE_MATRIX = include/matrix

_DEPS = Traffic.h
_DEPS_MATRIX =

DEPS = $(patsubst %, $(INCLUDE_DIR)/%,  $(_DEPS)) $(patsubst %, $(INCLUDE_MATRIX)/%, $(_DEPS_MATRIX))

SRC_DIR = src
SRC_MATRIX_DIR = src/matrix

OBJ_DIR = obj
OBJ_MATRIX_DIR = obj/matrix

_OBJ = main.o
_OBJ_MATRIX =

OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ)) $(patsubst %, $(OBJ_MATRIX_DIR)/%, $(_OBJ_MATRIX))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_MATRIX_DIR)/%.o : $(SRC_MATRIX_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
apcbml_st: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
run:
	./apcbml_st
distclean:
	rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~
clean:
	-rm apcbml_* $(OBJ_DIR)/*.o $(OBJ_MATRIX_DIR)/*.o
	-rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~


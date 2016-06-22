CXX = g++
CXXFLAGS = -pg -g -std=c++11 -Wall -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX) -I$(INCLUDE_NEW_MATRIX)
# CXXFLAGS += -fprofile-arcs -ftest-coverage -g -pg
# CXXFLAGS = -O3 -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -march=native -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
CXXGLAGS_OMP = -fopenmp -openmp
MPICXX = mpic++

INCLUDE_DIR = include
INCLUDE_MATRIX = include/matrix
INCLUDE_NEW_MATRIX = include/new_matrix

_DEPS = Template.h Color.h Car.h Tokenize.h Traffic.h Coordinates.h CellTraffic.h
_DEPS_MATRIX = Row.h DynRow.h VecVector.h Col.h DynRowDeque.h
_DEPS_MATRIX += VecVectorS.h VecVectorD.h Cell.h CellMatrix.h CellData.h
_DEPS_NEW_MATRIX = Matrix.h MatrixRow.h MatrixCol.h

DEPS = $(patsubst %, $(INCLUDE_DIR)/%,  $(_DEPS)) $(patsubst %, $(INCLUDE_MATRIX)/%, $(_DEPS_MATRIX))
DEPS_NEW = $(patsubst %, $(INCLUDE_NEW_MATRIX)/%, $(_DEPS_NEW_MATRIX))

SRC_DIR = src
SRC_MATRIX_DIR = src/matrix
SRC_NEW_MATRIX_DIR = src/new_matrix

OBJ_DIR = obj
OBJ_MATRIX_DIR = obj/matrix
OBJ_NEW_MATRIX_DIR = obj/new_matrix

_OBJ = Tokenize.o Traffic.o CellTraffic.o
_OBJ_MATRIX = Row.o DynRow.o VecVector.o Col.o DynRowDeque.o
_OBJ_MATRIX += VecVectorS.o VecVectorD.o Cell.o CellMatrix.o CellData.o

_OBJ_NEW_MATRIX = Matrix.o MatrixRow.o MatrixCol.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ)) $(patsubst %, $(OBJ_MATRIX_DIR)/%, $(_OBJ_MATRIX))
OBJ_NEW = $(patsubst %, $(OBJ_NEW_MATRIX_DIR)/%, $(_OBJ_NEW_MATRIX))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_MATRIX_DIR)/%.o : $(SRC_MATRIX_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

apcbml_st_D: $(OBJ) obj/main_D.o
	$(CXX) $(CXXFLAGS) -o $@ $^
apcbml_st: $(OBJ) obj/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^
run_D:
	./apcbml_st_D data/problem.csv
run:
	./apcbml_st data/problem.csv
distclean:
	-rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~
clean:
	-rm apcbml_* $(OBJ_DIR)/*.o $(OBJ_MATRIX_DIR)/*.o
	-rm *~ $(INCLUDE_DIR)/*~ $(INCLUDE_MATRIX)/*~ $(SRC_DIR)/*~ $(SRC_MATRIX_DIR)/*~ $(OBJ_DIR)/*~ $(OBJ_MATRIX_DIR)/*~ *.csv
	-rm generator/main
	-rm $(OBJ_DIR)/*.gcda $(OBJ_MATRIX_DIR)/*.gcda
	-rm $(OBJ_DIR)/*.gcno $(OBJ_MATRIX_DIR)/*.gcno
	-rm *.out
	-rm $(INCLUDE_NEW_MATRIX)/*~ $(SRC_NEW_MATRIX)/*~ $(OBJ_NEW_MATRIX_DIR)/*~ $(OBJ_NEW_MATRIX_DIR)/*.o

$(OBJ_NEW_MATRIX_DIR)/%.o : $(SRC_NEW_MATRIX_DIR)/%.cpp $(DEPS_NEW)
	$(CXX) -std=c++11 -Wall -Iinclude/new_matrix -c -o $@ $<
test: $(OBJ_NEW) $(DEPS_NEW)
	g++ -std=c++11 -o apcbml_test src/main-test.cpp $^ -Iinclude/new_matrix
gen:
	$(CXX) -Wall -std=c++11 -o generator/main generator/main.cpp
	generator/main 10 10 8 generator/input.csv

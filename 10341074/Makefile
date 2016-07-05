CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS += -fprofile-arcs -ftest-coverage -g -pg
# CXXFLAGS = -O3 -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
# CXXFLAGS = -O3 -march=native -std=c++11 -Wall -Wextra -I$(INCLUDE_DIR) -I$(INCLUDE_MATRIX)
CXXFLAGS_OMP = -fopenmp -openmp
MPICXX = mpic++

INCLUDE_DIR = include
INCLUDE_MATRIX = include/matrix

_DEPS = Template.h Color.h Tokenize.h Data.h MoveSingle.h DataLocal.h
_DEPS_MATRIX = Matrix.h MatrixRow.h MatrixCol.h ColumnIt.h CSR.h CSC.h
_DEPS_MPI = Move.h

DEPS = $(patsubst %, $(INCLUDE_DIR)/%,  $(_DEPS)) $(patsubst %, $(INCLUDE_MATRIX)/%, $(_DEPS_MATRIX))
DEPS_MPI = $(DEPS) $(patsubst %, $(INCLUDE_DIR)/%, $(_DEPS_MPI))

SRC_DIR = src
SRC_MATRIX_DIR = src/matrix
SRC_MPI_DIR = src/src_mpi

OBJ_DIR = obj
OBJ_MATRIX_DIR = obj/matrix
OBJ_MPI_DIR = obj/obj_mpi

_OBJ = MoveSingle.o DataLocal.o Data.o Tokenize.o
_OBJ_MATRIX = Matrix.o MatrixRow.o MatrixCol.o ColumnIt.o CSR.o CSC.o
_OBJ_MPI = Move.o

OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ)) $(patsubst %, $(OBJ_MATRIX_DIR)/%, $(_OBJ_MATRIX))
OBJ_MPI = $(OBJ) $(patsubst %, $(OBJ_MPI_DIR)/%, $(_OBJ_MPI))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS) $(DEPS_MPI)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)/%_mpi.o : $(SRC_DIR)/%_mpi.cpp $(DEPS) $(DEPS_MPI)
	$(MPICXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_MATRIX_DIR)/%.o : $(SRC_MATRIX_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_MPI_DIR)/%.o : $(SRC_MPI_DIR)/%.cpp $(DEPS)
	$(MPICXX) $(CXXFLAGS) -c -o $@ $<
apcbml_st: $(OBJ) obj/main_st.o
	$(CXX) $(CXXFLAGS) -o $@ $^
run:
	./apcbml_st data/problem.csv
apcbml_mpi: $(OBJ_MPI) obj/main_mpi.o
	$(MPICXX) $(CXXFLAGS) -o $@ $^
run_mpi:
	mpiexec -n 2 ./apcbml_mpi data/problem.csv

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

gen:
	$(CXX) -Wall -std=c++11 -o generator/main generator/main.cpp
	generator/main 10 10 8 generator/input.csv
	
apcbml_compare: $(OBJ) src/main_compare.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
run_compare:
	./apcbml_compare 

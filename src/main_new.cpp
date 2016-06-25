#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include <fstream>
#include <string>
#include <sstream>
/*
#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "Col.h"

#include "Traffic.h"
#include "Tokenize.h"

#include "CellTraffic.h"
*/
#include "Tokenize.h"
#include "Template.h"

#include "Matrix.h"
#include "MatrixRow.h"
#include "MatrixCol.h"
#include "Data.h"

#include "mpi.h"

int main(int argc, char ** argv){
  MPI_Init(&argc, &argv);
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	std::vector<std::size_t> times(1, 0);  
  Data data_global(None);
  Data data_local(None);
  if(my_rank == 0) {
    std::string   if_string(argv[1]);
    std::ifstream if_stream(if_string);

  	std::string first_line;

	
  	if(std::getline(if_stream, first_line))
  		tokenize_first_line(first_line,times);
	
  	std::cout << times;

  	if_stream >> data_global;
  	if_stream.close();
	  
	  std::size_t rows = data_global.rows();
	  std::size_t cols = data_global.cols();
	  MatrixType type_global = data_global.type();
  // choice for all white vs color
  // send type
  // send dimensions
  // index partition
	
    std::vector< std::size_t > index_global;
    std::vector< std::size_t > index_local;
	// send memory base
	
	// choice row vs col each thread
	
  	data_global.print();
  }
	MPI_Finalize();
  return 0;
}

#include <iostream>
#include <stdexcept>
#include <vector>
//#include <memory>

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

#include "Color.h"
#include "Matrix.h"
#include "MatrixRow.h"
#include "MatrixCol.h"
#include "CSR.h"
#include "Data.h"

#include "mpi.h"

void read_from_file(std::string if_string, Data & data_global, std::vector< std::size_t > & times);
void initialization_local(std::size_t & global_count, std::size_t & inn_size, std::size_t & single_count, std::size_t & local_count, std::size_t & global_remain, std::vector< std::size_t > & indices, MatrixType & type_local, std::size_t rows_global,	std::size_t cols_global, MatrixType type_global, int comm_sz, int my_rank);
int main(int argc, char ** argv){
  MPI_Init(&argc, &argv);
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  /////////////////////////////////////////////////////////////////
	std::vector< std::size_t > times(1, 0);  
  Data data_global(Input);
  
  std::size_t rows_global;
	std::size_t cols_global;
	MatrixType  type_global;

  if(my_rank == 0) {
    std::string   if_string(argv[1]);
    read_from_file(if_string, data_global, times);
    
    rows_global = data_global.rows();
  	cols_global = data_global.cols();
  	type_global = data_global.type();
  }

  MPI_Bcast(&rows_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&cols_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&type_global, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //////////////////////////////////////////////////////////////////
  std::size_t global_count = 0;
  std::size_t inn_size = 0;
  std::size_t single_count = 0;
  std::size_t local_count = 0;
  std::size_t global_remain = 0;
  std::vector< std::size_t > indices;
  MatrixType type_local;
  
  initialization_local(global_count, inn_size, single_count, local_count, global_remain, indices, type_local, rows_global, cols_global, type_global, comm_sz, my_rank);

  // if_comm _sz < global -> serial
   
  Data data_local(None);
  data_local.build_comp(type_local, rows_global, cols_global, indices);                                                                                 // +1  
  // verify indices = local_count +1
  std::vector< int > sendcnts(comm_sz, single_count * inn_size); sendcnts[0] = (single_count + global_remain) * inn_size;
  std::vector< int > displs(comm_sz); for(int k = 0; k < comm_sz; ++k) displs[k] = (single_count * k + global_remain) * inn_size; displs[0] = 0;
//  MPI_Scatterv( & * data_global.begin(), &sendcnts[0], &displs[0], MPI_INT, & * data_local.begin(), remain + local_count, MPI_INT, 0, MPI_COMM_WORLD);
  Scalar temp;
  void * sendbuf = & temp;
  if(my_rank == 0) sendbuf = & data_global[0];
  
//  std::cout << "rank "<< my_rank << sendcnts <<std::endl;
//  std::vector<Scalar> v(local_count*5);
  MPI_Scatterv(sendbuf, &sendcnts[0], &displs[0], MPI_INT, & data_local[inn_size], local_count * inn_size, MPI_INT, 0, MPI_COMM_WORLD);                                 // recv: + local
  // print size to verify 
  
  // choice for all white vs color
  // send type
  // send dimensions
  // index partition
    std::vector< std::size_t > index_global;
    std::vector< std::size_t > index_local;
  // send memory base
	// choice row vs col each thread
/*  
if(my_rank == 0) {data_global.print();
  Scalar * send =& data_global[0];
  for(std::size_t l = 0; l< rows_global*cols_global; ++l) {
  std::cout << *send;
  ++send;
  }
  std::cout << '\n';
}
  std::cout << "locl" <<std::endl;
  Scalar * send =& v[0];
  for(std::size_t l = 0; l< (local_count)*5; ++l) {
  std::cout << *send;
  ++send;
  }
  std::cout << '\n';
*/
  data_local.print();
  
/*
  if(trd.choose_white()) {
    move = & CellTraffic::move_white;
    std::cout << "Choosen white\n";
  } else {
    std::cout << "Choosen coloured\n";
  }

  for(std::size_t interval=0; interval<times.size()-1; ++interval){
    for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount){
      CALL_MEMBER_FN(trd,move)(*pYes,cYes);
//			(trd).*(move(*pYes, cYes));
      std::swap(pYes,pNo);
      std::swap(cYes,cNo);
    }
    std::stringstream convert;
    convert << times[interval+1];
    std::string ofname=convert.str();
    ofname.append(".csv");
    std::ofstream of(ofname);

    of << trd ;
    of.close();
  }
*/
	MPI_Finalize();
  return 0;
}
void read_from_file(std::string if_string, Data & data_global, std::vector< std::size_t > & times) {
  std::ifstream if_stream(if_string);
  std::string first_line;

  if(std::getline(if_stream, first_line))
    tokenize_first_line(first_line,times);

  std::cout << times;

  if_stream >> data_global;
  if_stream.close();
  
  return;
}
void initialization_local(std::size_t & global_count, std::size_t & inn_size, std::size_t & single_count, std::size_t & local_count, std::size_t & global_remain, std::vector< std::size_t > & indices, MatrixType & type_local, std::size_t rows_global, std::size_t cols_global, MatrixType type_global, int comm_sz, int my_rank) {
  switch(type_global) {
    case(ByRows) :
      type_local = ByCSR;
      global_count = rows_global;
      inn_size = cols_global;
      break;
    case(ByCols) :
      type_local = ByCSC;
      global_count = cols_global;
      inn_size = rows_global;
      break;
    default:
      break;
  }
        type_local = ByCSR;
      global_count = rows_global;
      inn_size = cols_global;

  global_remain = global_count % comm_sz;
  single_count = global_count / comm_sz;

  std::size_t a_local;
  if(my_rank == 0) {
    local_count = single_count + global_remain;
    a_local = 0;
  } else {
    local_count = single_count;
    a_local =my_rank * single_count + global_remain;
  }
  
  indices.resize(local_count + 1); // + preceding 
  if(my_rank == 0) {
    indices[0] = global_count - 1;
  } else {
    indices[0] = a_local - 1;
  }
  std::size_t i_local = a_local;
  for(std::size_t k = 0; k < local_count; ++k) {
    indices[k + 1] = i_local;
    ++i_local;
  }
  return;
}
/*
int MPI_Scatterv (
               void *sendbuf,
               int *sendcnts,
               int *displs,
               MPI_Datatype sendtype,
               void *recvbuf,
               int recvcnt,
               MPI_Datatype recvtype,
               int root,
               MPI_Comm comm )
*/

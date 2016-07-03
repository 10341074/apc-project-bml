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
#include "CSC.h"
#include "Data.h"
#include "DataLocal.h"
#include "Move.h"

#include "mpi.h"

void copy(const std::vector< Scalar > & from, std::vector< Scalar > & to);
void read_from_file(std::string if_string, Data & data_global, std::vector< std::size_t > & times);
void initialization_local(std::size_t & global_count, std::size_t & inn_size, std::size_t & single_count, std::size_t & local_count, std::size_t & global_remain, std::vector< std::size_t > & indices, MatrixType & type_local, std::size_t rows_global,	std::size_t cols_global, MatrixType type_global, int comm_sz, int my_rank);
MoveType choose_move_type(std::size_t white_count_g, std::size_t blue_count_g, std::size_t red_count_g);

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
  std::size_t times_size = times.size();
  MPI_Bcast(&times_size, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  times.resize(times_size);
  MPI_Bcast(& times[0], times_size, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  
  std::cout << times;
  MPI_Bcast(&rows_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&cols_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&type_global, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //////////////////////////////////////////////////////////////////
  std::size_t global_count = 0;
  std::size_t single_count = 0;
  std::size_t local_count = 0;
  std::size_t global_remain = 0;
  std::size_t inn_size = 0;

  std::vector< std::size_t > indices;
  MatrixType type_local;
  
  initialization_local(global_count, inn_size, single_count, local_count, global_remain, indices, type_local, rows_global, cols_global, type_global, comm_sz, my_rank);

  //inn_size;
  std::size_t ext_size = indices.size();
  Matrix matrix_local(ext_size,inn_size);   

  Data data_local(None);
  data_local.build_comp(type_local, rows_global, cols_global, indices);
  
  Scalar temp;
  void * sendbuf = & temp;
  if(my_rank == 0)
    sendbuf = & data_global[0];
  {
  std::vector< int > sendcnts(comm_sz, single_count * inn_size); sendcnts[0] = (single_count + global_remain) * inn_size;
  std::vector< int > displs(comm_sz); for(int k = 0; k < comm_sz; ++k) displs[k] = (single_count * k + global_remain) * inn_size; displs[0] = 0;
  MPI_Scatterv(sendbuf, &sendcnts[0], &displs[0], MPI_INT, & matrix_local[inn_size], local_count * inn_size, MPI_INT, 0, MPI_COMM_WORLD);
  }
  {
  std::vector< int > sendcnts(comm_sz, inn_size);
  std::vector< int > displs(comm_sz); for(int k = 0; k < comm_sz; ++k) displs[k] = (single_count * k + global_remain - 1) * inn_size; displs[0] = (global_count - 1) * inn_size;
  MPI_Scatterv(sendbuf, &sendcnts[0], &displs[0], MPI_INT, & matrix_local[0], inn_size, MPI_INT, 0, MPI_COMM_WORLD);  
  }
  // print size to verify 
	// choice row vs col each thread
  /////////////////////////////////////////////////////////////////////  
  // choice for all white vs color
//	data_local.load_colors_comp(indices);
//  data_local.load_moving_colors_comp(indices);
  std::size_t white_count_g = 0;
  std::size_t blue_count_g  = 0;
  std::size_t red_count_g   = 0;
  std::size_t white_count_l = 0;
  std::size_t blue_count_l  = 0;
  std::size_t red_count_l   = 0;

  DataLocalColor data_white(ext_size, inn_size);
  DataLocalColor data_blue(ext_size, inn_size);
  DataLocalColor data_red(ext_size, inn_size);

  load_local_colors(& matrix_local, data_white, data_blue, data_red, white_count_l, blue_count_l, red_count_l);

  MPI_Allreduce(& white_count_l,  & white_count_g,  1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD );
  MPI_Allreduce(& blue_count_l,   & blue_count_g,   1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD );
  MPI_Allreduce(& red_count_l,    & red_count_g,    1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD );
    // optimization redifine swap
//  std::cout << "my_rank " << my_rank << white_count_g << blue_count_g << red_count_g << std::endl;

  MoveType move_type_global = choose_move_type(white_count_g, blue_count_g, red_count_g);
//  data_local.unload_moving_colors_comp(move_type_global);


  Move move_object(type_local, move_type_global, data_white, data_blue, data_red);
    
  void (* current)(std::vector< Scalar > & mat, Move & m);
  void (* pausing)(std::vector< Scalar > & mat, Move & m);
  current = odd_move;
  pausing = even_move;

  //////////////////////////////////////////////////////
  std::stringstream convertm;
  convertm << my_rank;
  std::string ofnamem=convertm.str();
  ofnamem.append("_my.csv");
  std::ofstream ofm(ofnamem);

  ofm << matrix_local;
  ofm << "white\n";  data_white.print(ofm);
  ofm << "blue\n";  data_blue.print(ofm);
  ofm << "red\n";  data_red.print(ofm);
  std::cout << "rank " << my_rank << " " << local_count << std::endl;
///*  //////////////////////////////////////////////////////
  std::vector< int > recvcnts(comm_sz, single_count * inn_size); recvcnts[0] = (single_count + global_remain) * inn_size;
  std::vector< int > displs(comm_sz); for(int k = 0; k < comm_sz; ++k) displs[k] = (single_count * k + global_remain) * inn_size; displs[0] = 0;
  void * recvbuf = sendbuf;

//  for(std::size_t interval=0; interval<2; ++interval){
  for(std::size_t interval=0; interval<times.size()-1; ++interval){
    for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount) {
//    for(std::size_t timeCount=0; timeCount<4; ++timeCount){
      current(matrix_local.matrix(), move_object);
      std::swap(current, pausing);
//      ofm << "time " << timeCount << " rank  " << my_rank <<std::endl;
      copy(matrix_local.matrix(), data_local.matrix());
      ofm << data_local;
    }
    
    MPI_Gatherv( & matrix_local[inn_size], local_count * inn_size, MPI_INT, recvbuf, & recvcnts[0],  & displs[0], MPI_INT, 0, MPI_COMM_WORLD);
    
    if(my_rank == 0) {
      std::stringstream convert;
      convert << times[interval+1];
      std::string ofname=convert.str();
      ofname.append(".csv");
      std::ofstream of(ofname);
      of << data_global;
      of.close();
    }
//     data_local.print();

  }
//*/  ///////////////////////////////////////////////////////
  ofm.close();

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
MoveType choose_move_type(std::size_t white_count_g, std::size_t blue_count_g, std::size_t red_count_g) {
  if(2 * white_count_g > blue_count_g + red_count_g) {
    std::cout << "Choosen moving color" << std::endl;
    return MoveColor;
  } else {
    std::cout << "Choosen moving white" << std::endl;
    return MoveWhite;
  }
}
void copy(const std::vector< Scalar > & from, std::vector< Scalar > & to) {
  if(from.size() != to.size())
    throw std::logic_error("copy different size vectors");
  auto i_from = from.begin();
  for(Scalar & i_to : to) {
    i_to = * i_from;
    ++i_from;
  }
/*  std::cout << "from\t\t";
  for(Scalar i : from) std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "to\t\t";
  for(Scalar i : to) std::cout << i << " ";
  std::cout << std::endl;
*/
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

int MPI_Gatherv ( void *sendbuf, int sendcnt, MPI_Datatype sendtype,
                         void *recvbuf, int *recvcnts, int *displs,
                        MPI_Datatype recvtype,
                         int root, MPI_Comm comm )

*/

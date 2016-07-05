#include <iostream>
#include <stdexcept>
#include <vector>

#include <fstream>
#include <string>
#include <sstream>

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
void choose_move_type(MoveType & move_type, std::size_t white_count_g, std::size_t blue_count_g, std::size_t red_count_g);

int main(int argc, char ** argv){
  MPI_Init(&argc, &argv);
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  /////////////////////////////////////////////////////////////////
  // Read Input
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
  /////////////////////////////////////////////////////////////////
  // Broadcast time steps
  std::size_t times_size = times.size();
  MPI_Bcast(&times_size, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  times.resize(times_size);
  MPI_Bcast(& times[0], times_size, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  
  MPI_Bcast(&rows_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&cols_global, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  MPI_Bcast(&type_global, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //////////////////////////////////////////////////////////////////
  std::size_t global_count = 0;
  std::size_t single_count = 0;
  std::size_t local_count = 0;
  std::size_t global_remain = 0;
  std::size_t inn_size = 0;
  std::size_t ext_size = 0;
  Matrix matrix_local;
  
  std::vector< std::size_t > indices;
  MatrixType type_local;
   
  initialization_local(global_count, inn_size, single_count, local_count, global_remain, indices, type_local, rows_global, cols_global, type_global, comm_sz, my_rank);
  
  // std::cout << "rank " << my_rank << " global " << global_count << " single " << single_count << " local " << local_count << " size " << indices.size() << std::endl;
  /////////////////////////////////////////////////////////////////
  // 1 thread branch
  int ext_size_single = global_count;
  if(comm_sz == 1 || (ext_size_single < comm_sz)) {
    if(my_rank == 0) {  
      ext_size = ext_size_single;
      matrix_local = Matrix(ext_size, inn_size);
      copy(data_global.matrix(), matrix_local.matrix());
    
      std::size_t white_count_g = 0;
      std::size_t blue_count_g  = 0;
      std::size_t red_count_g   = 0;
    
      DataSingleColor data_white(ext_size, inn_size);
      DataSingleColor data_blue(ext_size, inn_size);
      DataSingleColor data_red(ext_size, inn_size);

      load_local_colors(& matrix_local, data_white, data_blue, data_red, white_count_g, blue_count_g, red_count_g);
  
      MoveType move_type_global;
      choose_move_type(move_type_global, white_count_g, blue_count_g, red_count_g);
      
//      move_type_global = 
      MoveSingle move_object(type_local, move_type_global, data_white, data_blue, data_red);
      std::cout << "MoveSingleobject constructed  with MatriType = " << MatrixTypeStr[type_local] << " and MoveType = " << MoveTypeStr[move_type_global] << std::endl;
  
      void (* current)(std::vector< Scalar > & mat, MoveSingle & m);
      void (* pausing)(std::vector< Scalar > & mat, MoveSingle & m);
      current = odd_move;
      pausing = even_move;
      
      for(std::size_t interval=0; interval<times.size()-1; ++interval){
        for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount) {
          current(matrix_local.matrix(), move_object);
          std::swap(current, pausing);
//        copy(matrix_local.matrix(), data_global.matrix());
//        std::cout << data_global;
      }
      
      copy(matrix_local.matrix(), data_global.matrix());
      std::stringstream convert;
      convert << times[interval+1];
      std::string ofname=convert.str();
      ofname.append(".csv");
      std::ofstream of(ofname);
      of << data_global;
      of.close();
      }
    }    
    std::cout << "Finished 1 thread branch by rank " << my_rank << std::endl;
    MPI_Finalize();
    return 0;
  }  
  //inn_size;
  ext_size = indices.size();
  matrix_local = Matrix(ext_size,inn_size);   

  Data data_local(None);
  data_local.build_comp(type_local, rows_global, cols_global, indices);
//  std::cout << "type_local" << MatrixTypeStr[type_local] << " rows_global " << rows_global << " cols_global " <<  cols_global << std::endl;
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
  /////////////////////////////////////////////////////////////////
  // choice  white vs color
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

  MoveType move_type_global;
  choose_move_type(move_type_global, white_count_g, blue_count_g, red_count_g);
  /////////////////////////////////////////////////////////////////
  // Move initialization
//  move_type_global = MoveWhite;
  Move move_object(type_local, move_type_global, data_white, data_blue, data_red);
  std::cout << "Move object constructed  with MatriType = " << MatrixTypeStr[type_local] << " and MoveType = " << MoveTypeStr[move_type_global] << std::endl;

  void (* current)(std::vector< Scalar > & mat, Move & m);
  void (* pausing)(std::vector< Scalar > & mat, Move & m);
  current = odd_move;
  pausing = even_move;
  /////////////////////////////////////////////////////////////////
  std::stringstream convert_my;
  convert_my << my_rank;
  std::string ofname_my=convert_my.str();
  ofname_my.append("_my.csv");
  std::ofstream of_my(ofname_my);
/*
  of_my << matrix_local;
  of_my << "white :\n";  data_white.print(of_my);
  of_my << "blue\n";  data_blue.print(of_my);
  of_my << "red\n";  data_red.print(of_my);
  std::cout << "rank " << my_rank << " " << local_count << std::endl << std::endl;
//*/
  /////////////////////////////////////////////////////////////////

//*
  /////////////////////////////////////////////////////////////////
  std::vector< int > recvcnts(comm_sz, single_count * inn_size); recvcnts[0] = (single_count + global_remain) * inn_size;
  std::vector< int > displs(comm_sz); for(int k = 0; k < comm_sz; ++k) displs[k] = (single_count * k + global_remain) * inn_size; displs[0] = 0;
  void * recvbuf = sendbuf;

//  for(std::size_t interval=0; interval<2; ++interval){
  for(std::size_t interval=0; interval<times.size()-1; ++interval){
    for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount) {
//    for(std::size_t timeCount=0; timeCount<4; ++timeCount){
      current(matrix_local.matrix(), move_object);
      std::swap(current, pausing);
//      of_my << "time " << timeCount << " rank  " << my_rank <<std::endl;
//      copy(matrix_local.matrix(), data_local.matrix());
//      of_my << data_local;
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
  /////////////////////////////////////////////////////////////////
//*/  
  of_my.close();

	MPI_Finalize();
  return 0;
}
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

void read_from_file(std::string if_string, Data & data_global, std::vector< std::size_t > & times) {
  std::ifstream if_stream(if_string);
  std::string first_line;
  
  // read times
  if(std::getline(if_stream, first_line))
    tokenize_first_line(first_line,times);

  std::cout << times;
  
  // read matrix
  if_stream >> data_global;
  
  // or
//  data_global.load_input(if_stream),
//  data_global.load_matrix(ByRows);
    
  if_stream.close();
  return;
}
void initialization_local(std::size_t & global_count, std::size_t & inn_size, std::size_t & single_count, std::size_t & local_count, std::size_t & global_remain, std::vector< std::size_t > & indices, MatrixType & type_local, std::size_t rows_global, std::size_t cols_global, MatrixType type_global, int comm_sz, int my_rank) {
/*
output
              std::size_t & global_count,
              std::size_t & inn_size,
              std::size_t & single_count,
              std::size_t & local_count,
              std::size_t & global_remain,
              std::vector< std::size_t > & indices, 
              MatrixType & type_local, 
input:
              std::size_t rows_global, 
              std::size_t cols_global,
              MatrixType type_global, 
              int comm_sz, 
              int my_rank
*/
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
void choose_move_type(MoveType & move_type, std::size_t white_count_g, std::size_t blue_count_g, std::size_t red_count_g) {
  if(2 * white_count_g > blue_count_g + red_count_g) {
    std::cout << "Chosen to move color" << std::endl;
    move_type = MoveColor;
  } else {
    std::cout << "Chosen to move white" << std::endl;
    move_type = MoveWhite;
  }
  return;
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

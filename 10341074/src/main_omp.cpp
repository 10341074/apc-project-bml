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
#include "MoveSingle.h"

#include "omp.h"

void copy(const std::vector< Scalar > & from, std::vector< Scalar > & to);
void read_from_file(std::string if_string, Data & data_global, std::vector< std::size_t > & times);
void initialization_local(std::size_t & global_count, std::size_t & inn_size, MatrixType & type_local, std::size_t rows_global, std::size_t cols_global, MatrixType type_global);
void choose_move_type(MoveType & move_type, std::size_t white_count_g, std::size_t blue_count_g, std::size_t red_count_g);

int main(int argc, char ** argv){
  // Read Input
	std::vector< std::size_t > times(1, 0);  
  Data data_global(Input);

  std::size_t rows_global;
	std::size_t cols_global;
	MatrixType  type_global;
	{
    std::string   if_string(argv[1]);
    read_from_file(if_string, data_global, times);
    
    rows_global = data_global.rows();
  	cols_global = data_global.cols();
  	type_global = data_global.type();
  }
  //////////////////////////////////////////////////////////////////
  std::size_t global_count = 0;
//  std::size_t single_count = 0;
//  std::size_t local_count = 0;
//  std::size_t global_remain = 0;
  std::size_t inn_size = 0;
  std::size_t ext_size = 0;
  Matrix matrix_local;
  
//  std::vector< std::size_t > indices;
  MatrixType type_local;
   
  initialization_local(global_count, inn_size, type_local, rows_global, cols_global, type_global);
  
  // std::cout << "rank " << my_rank << " global " << global_count << " single " << single_count << " local " << local_count << " size " << indices.size() << std::endl;
  /////////////////////////////////////////////////////////////////

      ext_size = global_count;
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
      #pragma omp parallel default(none) shared(matrix_local, move_object, data_global, times)
      {
      
      void (* current)(std::vector< Scalar > & mat, MoveSingle & m);
      void (* pausing)(std::vector< Scalar > & mat, MoveSingle & m);
      current = odd_move;
      pausing = even_move;
      
      
      for(std::size_t interval=0; interval<times.size()-1; ++interval){
        for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount) {
          if(timeCount % 2 == 0)
            odd_move(matrix_local.matrix(), move_object);
          else
            even_move(matrix_local.matrix(), move_object);
          //*/  
          /*
          current(matrix_local.matrix(), move_object);
          std::swap(current, pausing);
          //*/
          #pragma omp barrier
//        copy(matrix_local.matrix(), data_global.matrix());
//        std::cout << data_global;
      }
    if(omp_get_thread_num() == 0) {
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
      }
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
void initialization_local(std::size_t & global_count, std::size_t & inn_size, MatrixType & type_local, std::size_t rows_global, std::size_t cols_global, MatrixType type_global) {
/*
output
              std::size_t & global_count,
              std::size_t & inn_size,
              MatrixType & type_local,
input:
              std::size_t rows_global, 
              std::size_t cols_global,
              MatrixType type_global, 
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
  return;
}

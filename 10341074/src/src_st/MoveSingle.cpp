#include "MoveSingle.h"
void swap(Scalar & s1, Scalar & s2) {
  Scalar s3 = s1;
  s1 = s2;
  s2 = s3;
  return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void move_parall(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment) {
  std::size_t inn_count               = data_color.inn_count_;
  std::vector< std::size_t > & inside  = data_color.inside;
  
  std::vector< std::size_t > temp;  temp.reserve(inside.size());
  // inside
  for(std::size_t & i : inside) {
    if(mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i / inn_count) * inn_count + (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  return;
}
void move_across(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment) {
  std::size_t inn_count               = data_color.inn_count_;
  std::size_t tot_count = data_color.ext_count_ * inn_count;
  std::vector< std::size_t > & inside   = data_color.inside;
  
  std::vector< std::size_t > temp;
  temp.reserve(inside.size());

  // incremenr +1 or -1
  std::size_t increment_big = inn_count * increment;

  // inside
  for(std::size_t & i : inside) {
    if(mat[(i + increment_big + tot_count) % tot_count] == second_color) {
      temp.push_back(i);
      i = (i + increment_big + tot_count) % tot_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i + increment_big + tot_count) % tot_count]);
  }
  return;
}

MoveSingle::MoveSingle(MatrixType matrix_type, MoveType move_type, DataSingleColor & data_white, DataSingleColor & data_blue, DataSingleColor & data_red) : matrix_type_(matrix_type), move_type_(move_type) {
  switch(move_type) {
    case(MoveColor) :
      data_white = DataSingleColor();
      blue_ = ParametersSingle(& data_blue, Blue, White, 1);
      red_  = ParametersSingle(& data_red,  Red,  White, 1);
      switch(matrix_type) {
        case(ByCSR) :
          move_active = move_across;
          move_inactive = move_parall;
          break;
        case(ByCSC) :
          move_active = move_parall;
          move_inactive = move_across;
          break;
        default:
          throw std::logic_error("MoveSingle::MoveSingle not compact matrix_type");
          break;
      }
      break;
    case(MoveWhite) :
      data_blue = DataSingleColor();
      data_red = DataSingleColor();
      blue_ = ParametersSingle(& data_white, White, Blue, -1);
      red_  = ParametersSingle(& data_white, White, Red,  -1);
      switch(matrix_type) {
        case(ByCSR) :
          move_active = move_across;
          move_inactive = move_parall;
          break;
        case(ByCSC) :
          move_active = move_parall;
          move_inactive = move_across;
          break;
        default:
          throw std::logic_error("MoveSingle::MoveSingle not compact matrix_type");
          break;
      }
      break;
  }
}
void odd_move(std::vector< Scalar > & mat, MoveSingle & m) {
  ParametersSingle * current = & m.blue_; 
  if(m.matrix_type_ == ByCSC)
    move_parall(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
  else
    move_across(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
//  m.move_active(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
//  std::swap(m.move_active, m.move_inactive);
  return;
}
void even_move(std::vector< Scalar > & mat, MoveSingle & m) {
  ParametersSingle * current = & m.red_; 
   if(m.matrix_type_ == ByCSC)
    move_across(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
  else
    move_parall(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
//  m.move_active(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_);
//  std::swap(m.move_active, m.move_inactive);
  return;
}

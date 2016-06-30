#include "Move.h"
#include <numeric>
void swap(Scalar & s1, Scalar & s2) {
  Scalar s3 = s1;
  s1 = s2;
  s2 = s3;
  return;
}
void move_parall(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
//  std::size_t & ext_count             = data_color.ext_count_;
  std::size_t & inn_count             = data_color.inn_count_;
  std::vector< std::size_t > & first  = data_color.first;
  std::vector< std::size_t > & last   = data_color.last;
  std::vector< std::size_t > & inside  = data_color.inside;
  
  std::vector< std::size_t > temp;  temp.reserve(inn_count);
  
  // first
  for(std::size_t & i : first) {
    if(mat[(i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  // inside
  for(std::size_t & i : inside) {
    if(mat[(i / inn_count) + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i / inn_count) + (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  // last
  for(std::size_t & i : last) {
    if(mat[(i / inn_count) + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i / inn_count) + (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  return;
}
void move_across(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
  std::size_t & ext_count             = data_color.ext_count_;
  std::size_t & inn_count             = data_color.inn_count_;
  std::vector< std::size_t > & inside  = data_color.inside;
  
  std::vector< std::size_t > temp;  temp.reserve(border_move.size() + inside.size());

  // incremenr +1 or -1
  increment *= inn_count;
  out_border.clear();
  on_border.clear();

  // border
  for(std::size_t & i : border_move) {
    if(mat[i + increment] == second_color) {
      temp.push_back(i);
      out_border.push_back(i % inn_count);
      i = i + increment;
    }
  }
  // inside
  for(std::size_t & i : inside) {
    if(mat[i + increment] == second_color) {
      if((i + increment) / ext_count == border_no_move) {
        on_border.push_back((i + increment) % inn_count);
      }
      temp.push_back(i);
      i = i + increment;
    }
  }
  
  for(std::size_t i : temp) {
    swap(mat[i],mat[i + increment]);
  }

  return;
}


void move_parall() {}
void move_across() {}


Move::Move(MatrixType matrix_type, MoveType move_type, MoveTypeDirection blue_direction, MoveTypeDirection red_direction, Data & data_local) : matrix_type_(matrix_type), move_type_(move_type) {
  int flag = 0; // 0 = parallel, 1 = orthogonal
  switch(matrix_type) {
  case(ByCSR) :
    break;
  case(ByCSC) :
    flag = 1 - flag;
    break;
  default:
    throw std::logic_error("Move::Move not compact matrix_type");
    break;
  }
  switch(blue_direction) {
    case(Horizontal) :
      break;
    case(Vertical) :
      flag = 1 - flag;
      break;
    default:
      break;
  }
  // initialiiztion
  switch(flag) {
    case(0) :
      move = move_parall;
      break;
    case(1) :
      move = move_across;
      break;
    default:
      break;  
  }
  switch(move_type) {
    case(MoveWhite) :
      increment = -1;
      blue = data_local.data_white;
      red = data_local.data_white;
      blue_add = & blue->last_new;
      blue_rem = & blue->first_new;
      red_add = & red->last_new;
      red_rem = & red->first_new;
    case(MoveColor) :
      increment = +1;
      blue = data_local.data_blue;
      red = data_local.data_red;
      blue_add = & blue->first_new;
      blue_rem = & blue->last_new;
      red_add = & red->first_new;
      red_rem = & red->last_new;
  }
}


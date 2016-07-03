#include "Move.h"
#include "mpi.h"
void swap(Scalar & s1, Scalar & s2) {
  Scalar s3 = s1;
  s1 = s2;
  s2 = s3;
  return;
}
void ngbd(int & out_ngbd, int & on_ngbd, int increment) {
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  on_ngbd =(my_rank + increment + comm_sz) % comm_sz;
  out_ngbd =(my_rank - increment + comm_sz) % comm_sz;
  return;
}
void move_parall(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
//  std::cout << "move_parall" << std::endl;
//  std::cout << "ext " << data_color.ext_count_ << " inn " << data_color.inn_count_ << mat << std::endl;
//  std::cout << "incr " << increment << " second " << second_color << std::endl;
  
  std::size_t inn_count               = data_color.inn_count_;
  std::vector< std::size_t > & first  = data_color.first;
  std::vector< std::size_t > & last   = data_color.last;
  std::vector< std::size_t > & inside  = data_color.inside;
  
  std::vector< std::size_t > temp;  temp.reserve(inn_count + inside.size());
 // std::cout << "first " << first << " inside  " << inside << " last " << last << std::endl; 
  // first
  for(std::size_t & i : first) {
    if(mat[(i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
  //    std::cout << "i before "<< i <<std::endl;
      i = (i + increment + inn_count) % inn_count;
    //        std::cout << "i after "<< i <<std::endl;

    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  // inside
  for(std::size_t & i : inside) {
    if(mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
//            std::cout << "i before "<< i <<std::endl;

      i = (i / inn_count) * inn_count + (i + increment + inn_count) % inn_count;
 //     std::cout << "i after "<< i <<std::endl;

    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
  // last
  for(std::size_t & i : last) {
    if(mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i / inn_count) * inn_count + (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
//    std::cout << "ext " << data_color.ext_count_ << " inn " << data_color.inn_count_ << mat << std::endl;

  return;
}
void move_across(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
//  std::cout << "move_across" << std::endl;
  std::size_t inn_count               = data_color.inn_count_;
  std::size_t ext_count               = data_color.ext_count_;
  std::vector< std::size_t > & inside   = data_color.inside;
  
  std::vector< std::size_t > temp;
  temp.reserve(border_move.size() + inside.size());

//  std::cout << "first " << data_color.first << " inside  " << inside << " last " << data_color.last <<  "no_move "<< border_move << std::endl; 
  // incremenr +1 or -1
  std::size_t increment_big = inn_count * increment;
  out_border.clear();
  on_border.clear();
  out_border.push_back(0);    // size record
  on_border.push_back(0);     // size record

  std::vector< std::size_t > inside_temp;
  inside_temp.reserve(inside.capacity());
  // border
  for(std::size_t & i : border_move) {
    if(mat[i + increment_big] == second_color) {
      temp.push_back(i);
      inside_temp.push_back(i + increment_big);
      out_border.push_back(i % inn_count);
    }
  }
  // inside
  for(std::size_t & i : inside) {
    if(mat[i + increment_big] == second_color) {
      if((i + increment_big) / inn_count == border_no_move) {
        temp.push_back(i);
        on_border.push_back((i + increment_big) % inn_count);
      } else {
        temp.push_back(i);
        inside_temp.push_back(i + increment_big);
      }
    } else {
    inside_temp.push_back(i);
    }
  }
  inside_temp.swap(inside); // it will be destroyed

  for(std::size_t i : temp) {
    swap(mat[i],mat[i + increment_big]);
  }
  
  out_border[0] = out_border.size() - 1;
  on_border[0] = on_border.size() - 1;
  int out_ngbd = 0, on_ngbd = 0;
  ngbd(out_ngbd, on_ngbd, increment);

//  MPI_Sendrecv on
  std::vector< std::size_t > out_from_on(inn_count); // add on out_border
  MPI_Sendrecv(& on_border[0], on_border[0] + 1, MPI_UNSIGNED_LONG_LONG, on_ngbd, 0, & out_from_on[0], inn_count, MPI_UNSIGNED_LONG_LONG, out_ngbd, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//  MPI_Sendrecv out
  std::vector< std::size_t > on_from_out(inn_count); // rm from on_border
  MPI_Sendrecv(& out_border[0], out_border[0] + 1, MPI_UNSIGNED_LONG_LONG, out_ngbd, 0, & on_from_out[0], inn_count, MPI_UNSIGNED_LONG_LONG, on_ngbd, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  
  std::size_t out_index = data_color.ext_count_ - 1 - border_no_move;
  std::size_t on_index = border_no_move;

  std::size_t out_from_on_end = out_from_on[0] + 1;
  for(std::size_t k = 1; k < out_from_on_end; ++k) {
    mat[out_index * inn_count + out_from_on[k]] = first_color;
  }
  on_from_out.resize(on_from_out[0]+1);
  std::size_t on_from_out_end = on_from_out[0] + 1;
  for(std::size_t k = 1; k < on_from_out_end; ++k) {
    mat[on_index * inn_count + on_from_out[k]] = second_color;
//      std::cout << "onind"<< on_index<< "onfromout "<< on_from_out ;//
//std::cout << "new "<< on_index * inn_count + on_from_out[k] << mat[on_index * inn_count + on_from_out[k]] <<std::endl;
  }
  
  data_color.first.clear();
  data_color.last.clear();
  // first last update
  for(std::size_t k = 0 ; k < inn_count; ++k) {
    if(mat[k] == first_color) {
      data_color.first.push_back(k);
    }
  }
  
  for(std::size_t k = (ext_count - 1) * inn_count ; k < ext_count * inn_count; ++k) {
    if(mat[k] == first_color) {
      data_color.last.push_back(k);
    }
  }

  out_border.clear();
  on_border.clear();
  return;
}

Move::Move(MatrixType matrix_type, MoveType move_type, Data & data_local) : matrix_type_(matrix_type), move_type_(move_type) {
  switch(matrix_type) {
  case(ByCSR) :
    move_active = move_across;
    break;
  case(ByCSC) :
    move_active = move_parall;
    break;
  default:
    throw std::logic_error("Move::Move not compact matrix_type");
    break;
  }
  switch(move_type) {
    case(MoveColor) :
      break;
    case(MoveWhite) :
      break;
  }
}
Move::Move(MatrixType matrix_type, MoveType move_type, DataLocalColor & data_white, DataLocalColor & data_blue, DataLocalColor & data_red) : matrix_type_(matrix_type), move_type_(move_type) {
  switch(move_type) {
    case(MoveColor) :
      data_white = DataLocalColor();
      blue_ = Parameters(& data_blue, Blue, White, 1, & data_blue.first, data_blue.ext_count_ - 1);
      red_  = Parameters(& data_red,  Red,  White, 1, & data_red.first,  data_red.ext_count_ - 1);
      switch(matrix_type) {
        case(ByCSR) :
          move_active = move_across;
          move_inactive = move_parall;
          if(data_blue.ext_count_ == 2) {
            std::cout << "bi form" << std::endl;
            move_active = move_across_bi;
            move_inactive = move_parall_bi;
          }
          out_border.reserve(data_blue.inn_count_);
          out_border.clear();
          on_border.reserve(data_blue.inn_count_);
          on_border.clear();
          break;
        case(ByCSC) :
          move_active = move_parall;
          move_inactive = move_across;
          if(data_blue.ext_count_ == 2) {
            std::cout << "bi form" << std::endl;
            move_active = move_parall_bi;
            move_inactive = move_across_bi;
          }
          out_border.reserve(data_red.inn_count_);
          out_border.clear();
          on_border.reserve(data_red.inn_count_);
          on_border.clear();
          break;
        default:
          throw std::logic_error("Move::Move not compact matrix_type");
          break;
      }
      break;
    case(MoveWhite) :
      data_blue = DataLocalColor();
      data_red = DataLocalColor();
      blue_ = Parameters(& data_white, White, Blue, -1, & data_white.last, 0);
      red_  = Parameters(& data_white, White, Red,  -1, & data_white.last, 0);
      switch(matrix_type) {
        case(ByCSR) :
          move_active = move_across;
          move_inactive = move_parall;
          if(data_blue.ext_count_ == 2) {
            std::cout << "bi form" << std::endl;
            move_active = move_across_bi;
            move_inactive = move_parall_bi;
          }
          out_border.reserve(data_white.inn_count_);
          out_border.clear();
          on_border.reserve(data_white.inn_count_);
          on_border.clear();
          break;
        case(ByCSC) :
          move_active = move_parall;
          move_inactive = move_across;
          if(data_blue.ext_count_ == 2) {
            std::cout << "bi form" << std::endl;
            move_active = move_parall_bi;
            move_inactive = move_across_bi;
          }
          out_border.reserve(data_white.inn_count_);
          out_border.clear();
          on_border.reserve(data_white.inn_count_);
          on_border.clear();
          break;
        default:
          throw std::logic_error("Move::Move not compact matrix_type");
          break;
      }
      break;
  }
}
void odd_move(std::vector< Scalar > & mat, Move & m) {
  Parameters * current = & m.blue_; 
  m.move_active(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_, * (current->border_move_p_), current->border_no_move_, m.out_border, m.on_border);

  std::swap(m.move_active, m.move_inactive);
  return;
}
void even_move(std::vector< Scalar > & mat, Move & m) {
  Parameters * current = & m.red_; 
  m.move_active(mat, * (current->data_color_), current->first_color_, current->second_color_, current->increment_, * (current->border_move_p_), current->border_no_move_, m.out_border, m.on_border);

  std::swap(m.move_active, m.move_inactive);
  return;
}
void move_parall_bi(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
//  std::cout << "move_parall" << std::endl;
//  std::cout << "ext " << data_color.ext_count_ << " inn " << data_color.inn_count_ << mat << std::endl;
//  std::cout << "incr " << increment << " second " << second_color << std::endl;
  
  std::size_t inn_count               = data_color.inn_count_;
  std::vector< std::size_t > & first  = data_color.first;
  std::vector< std::size_t > & last   = data_color.last;
//  std::vector< std::size_t > & inside  = data_color.inside;
  
  std::vector< std::size_t > temp;  temp.reserve(inn_count);
 // std::cout << "first " << first << " inside  " << inside << " last " << last << std::endl; 
  // first
  for(std::size_t & i : first) {
    if(mat[(i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
  //    std::cout << "i before "<< i <<std::endl;
      i = (i + increment + inn_count) % inn_count;
    //        std::cout << "i after "<< i <<std::endl;

    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i + increment + inn_count) % inn_count]);
  }
  temp.clear();
/*
  // inside
  for(std::size_t & i : inside) {
    if(mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
//            std::cout << "i before "<< i <<std::endl;

      i = (i / inn_count) * inn_count + (i + increment + inn_count) % inn_count;
 //     std::cout << "i after "<< i <<std::endl;

    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
*/
  // last
  for(std::size_t & i : last) {
    if(mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count] == second_color) {
      temp.push_back(i);
      i = (i / inn_count) * inn_count + (i + increment + inn_count) % inn_count;
    }
  }
  for(std::size_t i : temp) {
    swap(mat[i],mat[(i / inn_count) * inn_count + (i + increment + inn_count) % inn_count]);
  }
  temp.clear();
//    std::cout << "ext " << data_color.ext_count_ << " inn " << data_color.inn_count_ << mat << std::endl;

  return;
}
void move_across_bi(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border) {
//  std::cout << "move_across" << std::endl;
  std::size_t inn_count               = data_color.inn_count_;
  std::size_t ext_count               = data_color.ext_count_;
//  std::vector< std::size_t > & inside   = data_color.inside;
  
  std::vector< std::size_t > temp;
  temp.reserve(border_move.size());

//  std::cout << "first " << data_color.first << " inside  " << inside << " last " << data_color.last <<  "no_move "<< border_move << std::endl; 
  // incremenr +1 or -1
  std::size_t increment_big = inn_count * increment;
  out_border.clear();
  on_border.clear();
  out_border.push_back(0);    // size record
  on_border.push_back(0);     // size record

//  std::vector< std::size_t > inside_temp;
//  inside_temp.reserve(inside.capacity());
  // border
  for(std::size_t & i : border_move) {
    if(mat[i + increment_big] == second_color) {
      temp.push_back(i);
//      inside_temp.push_back(i + increment_big);
      out_border.push_back(i % inn_count);
      on_border.push_back((i + increment_big) % inn_count);
    }
  }
  /*
  // inside
  for(std::size_t & i : inside) {
    if(mat[i + increment_big] == second_color) {
      if((i + increment_big) / inn_count == border_no_move) {
        temp.push_back(i);
        on_border.push_back((i + increment_big) % inn_count);
      } else {
        temp.push_back(i);
        inside_temp.push_back(i + increment_big);
      }
    } else {
    inside_temp.push_back(i);
    }
  }
  inside_temp.swap(inside); // it will be destroyed
*/
  for(std::size_t i : temp) {
    swap(mat[i],mat[i + increment_big]);
  }
  
  out_border[0] = out_border.size() - 1;
  on_border[0] = on_border.size() - 1;
  int out_ngbd = 0, on_ngbd = 0;
  ngbd(out_ngbd, on_ngbd, increment);

//  MPI_Sendrecv on
  std::vector< std::size_t > out_from_on(inn_count); // add on out_border
  MPI_Sendrecv(& on_border[0], on_border[0] + 1, MPI_UNSIGNED_LONG_LONG, on_ngbd, 0, & out_from_on[0], inn_count, MPI_UNSIGNED_LONG_LONG, out_ngbd, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//  MPI_Sendrecv out
  std::vector< std::size_t > on_from_out(inn_count); // rm from on_border
  MPI_Sendrecv(& out_border[0], out_border[0] + 1, MPI_UNSIGNED_LONG_LONG, out_ngbd, 0, & on_from_out[0], inn_count, MPI_UNSIGNED_LONG_LONG, on_ngbd, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  
  std::size_t out_index = data_color.ext_count_ - 1 - border_no_move;
  std::size_t on_index = border_no_move;

  std::size_t out_from_on_end = out_from_on[0] + 1;
  for(std::size_t k = 1; k < out_from_on_end; ++k) {
    mat[out_index * inn_count + out_from_on[k]] = first_color;
  }
  on_from_out.resize(on_from_out[0]+1);
  std::size_t on_from_out_end = on_from_out[0] + 1;
  for(std::size_t k = 1; k < on_from_out_end; ++k) {
    mat[on_index * inn_count + on_from_out[k]] = second_color;
//      std::cout << "onind"<< on_index<< "onfromout "<< on_from_out ;//
//std::cout << "new "<< on_index * inn_count + on_from_out[k] << mat[on_index * inn_count + on_from_out[k]] <<std::endl;
  }
  
  data_color.first.clear();
  data_color.last.clear();
  // first last update
  for(std::size_t k = 0 ; k < inn_count; ++k) {
    if(mat[k] == first_color) {
      data_color.first.push_back(k);
    }
  }
  
  for(std::size_t k = (ext_count - 1) * inn_count ; k < ext_count * inn_count; ++k) {
    if(mat[k] == first_color) {
      data_color.last.push_back(k);
    }
  }

  out_border.clear();
  on_border.clear();
  return;
}

/*
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
*/

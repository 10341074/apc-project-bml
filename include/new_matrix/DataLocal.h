#ifndef DATA_LOCAL_H
#define DATA_LOCAL_H

#include "Data.h"


struct DataLocalColor {
  std::size_t                   ext_count_ = 0;
  std::size_t                   inn_count_ = 0;
//  std.:size_t                   first_ind = 0;
//  std.:size_t                   last_ind = 0;
  std::vector< std::size_t >    inside;
  std::vector< std::size_t >    first;
  std::vector< std::size_t >    last;
//  std::vector< std::size_t >    first_new;
//  std::vector< std::size_t >    last_new;
  DataLocalColor() {}
  DataLocalColor(std::size_t ext_count, std::size_t inn_count) : ext_count_(ext_count), inn_count_(inn_count) {
    inside.reserve( (ext_count - 2) * inn_count );
    first.reserve( inn_count );
    last.reserve( inn_count );
//    first_new.reserve( inn_count );
//    last_new.reserve( inn_count );
  }
  void print(std::ostream & os) {
    os << "inside " << inside;
    os << "first " << first;
    os << "last " << last;
  }
}; // finish class

void load_local_colors(const Matrix * ptr, DataLocalColor & data_local_white, DataLocalColor & data_local_blue, DataLocalColor & data_local_red, std::size_t & white_count, std::size_t & blue_count, std::size_t & red_count);


#endif  

#ifndef DATA_LOCAL_H
#define DATA_LOCAL_H

#include "Data.h"


struct DataLocalColor {
  std::size_t                   ext_count_ = 0;
  std::size_t                   inn_count_ = 0;
  std::vector< std::size_t >    inside;
//  std.:size_t                   first_ind = 0;
//  std.:size_t                   last_ind = 0;
  std::vector< std::size_t >    first;
  std::vector< std::size_t >    last;
//  std::vector< std::size_t >    first_new;
//  std::vector< std::size_t >    last_new;
  DataLocalColor(std::size_t ext_count, std::size_t inn_count) : ext_count_(ext_count), inn_count_(inn_count) {
    inside.reserve( (ext_count - 2) * inn_count );
    first.reserve( inn_count );
    last.reserve( inn_count );
//    first_new.reserve( inn_count );
//    last_new.reserve( inn_count );
  }
}; // finish class
#endif  

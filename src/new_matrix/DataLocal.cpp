#include "DataLocal.h"

DataLocalColor & switch_local_color(const Scalar & s, DataLocalColor & white, DataLocalColor & blue, DataLocalColor & red) {
      switch( s ) {
        case(White):
          return white;
          break;
        case(Blue):
          return blue;
          break;
        case(Red):
          return red;
          break;
        default:
          throw std::logic_error("switch_local_color exception");
          break;
      }
}
DataSingleColor & switch_local_color(const Scalar & s, DataSingleColor & white, DataSingleColor & blue, DataSingleColor & red) {
      switch( s ) {
        case(White):
          return white;
          break;
        case(Blue):
          return blue;
          break;
        case(Red):
          return red;
          break;
        default:
          throw std::logic_error("switch_local_color exception");
          break;
      }
}
void load_local_colors(const Matrix * ptr, DataLocalColor & data_local_white, DataLocalColor & data_local_blue, DataLocalColor & data_local_red, std::size_t & white_count, std::size_t & blue_count, std::size_t & red_count) {
  if(ptr == nullptr) {
    throw std::logic_error("load_local from nullptr");
  }
  std::size_t inn_count = ptr->inn_count();
  std::size_t ext_count = ptr->ext_count();

  data_local_white = DataLocalColor(ext_count, inn_count);
  data_local_blue = DataLocalColor(ext_count, inn_count);
  data_local_red = DataLocalColor(ext_count, inn_count);

  std::vector< Scalar >::const_iterator it_from = ptr->begin();
  
  std::size_t k = 0;
  // first
  for( ; k < inn_count; ++k) {
    DataLocalColor & c = switch_local_color(* it_from, data_local_white, data_local_blue, data_local_red);
    c.first.push_back(k);
    ++it_from;
  }
  for( ; k < (ext_count - 1) * inn_count; ++k) {
    DataLocalColor & c = switch_local_color(* it_from, data_local_white, data_local_blue, data_local_red);
    c.inside.push_back(k);
    ++it_from;
  }
  for( ; k < ext_count * inn_count; ++k) {
    DataLocalColor & c = switch_local_color(* it_from, data_local_white, data_local_blue, data_local_red);
    c.last.push_back(k);
    ++it_from;
  }

  white_count  = data_local_white.inside.size() + data_local_white.last.size();
  blue_count  = data_local_blue.inside.size() + data_local_blue.last.size();
  red_count  = data_local_red.inside.size() + data_local_red.last.size();
  return;
}
void load_local_colors(const Matrix * ptr, DataSingleColor & data_local_white, DataSingleColor & data_local_blue, DataSingleColor & data_local_red, std::size_t & white_count, std::size_t & blue_count, std::size_t & red_count) {
  if(ptr == nullptr) {
    throw std::logic_error("load_local from nullptr");
  }
  std::size_t inn_count = ptr->inn_count();
  std::size_t ext_count = ptr->ext_count();

  data_local_white = DataSingleColor(ext_count, inn_count);
  data_local_blue = DataSingleColor(ext_count, inn_count);
  data_local_red = DataSingleColor(ext_count, inn_count);

  std::vector< Scalar >::const_iterator it_from = ptr->begin();
  
  std::size_t k = 0;
  for( ; k < ext_count * inn_count; ++k) {
    DataSingleColor & c = switch_local_color(* it_from, data_local_white, data_local_blue, data_local_red);
    c.inside.push_back(k);
    ++it_from;
  }

  white_count  = data_local_white.inside.size();
  blue_count  = data_local_blue.inside.size();
  red_count  = data_local_red.inside.size();
  return;
}


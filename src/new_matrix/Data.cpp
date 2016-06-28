#include "Data.h"

#define START '0'
Data::Data(MatrixType t) : t_(t) {
  switch(t) {
    case(None) :
      break;
    case(Input) :
      m_inp = new MatrixInp;
      break;
    default:
      break;
  }
}
Data::~Data() {
  if(m_inp != nullptr) {
    delete m_inp;
    m_inp = nullptr;
    }
  if(m_lin != nullptr) {
    delete m_lin;
    m_lin = nullptr;
    }
  if(white != nullptr) {
    delete white;
    white = nullptr;
    }
  if(blue != nullptr) {
    delete blue;
    blue = nullptr;
    }
  if(red != nullptr) {
    delete red;
    red = nullptr;
    }
  if(first != nullptr) {
    delete first;
    first = nullptr;
    }
  if(last != nullptr) {
    delete last;
    last = nullptr;
    }
  if(data_white != nullptr) {
    delete data_white;
    data_white = nullptr;
    }
  if(data_blue != nullptr) {
    delete data_blue;
    data_blue = nullptr;
    }
  if(data_red != nullptr) {
    delete data_red;
    data_red = nullptr;
    }
}
void Data::build_full(MatrixType t, std::size_t m, std::size_t n) {
  switch(t) {
    case(ByRows) :
      t_  = ByRows;
      m_lin = new MatrixRow(m, n);
      rows_ = m;
      cols_ = n;
      break;
    case(ByCols) :
      t_ = ByCols;
      m_lin = new MatrixCol(m, n);
      rows_ = m;
      cols_ = n;
      break;
    default:
      break;
  }
  return;
}
void Data::build_comp(MatrixType t, std::size_t r, std::size_t c, const std::vector< std::size_t > & indices) {
  switch(t) {
    case(ByCSR) :
      t_ = ByCSR;
      m_lin = new CSR(r, c, indices, c);
      rows_ = r;
      cols_ = c;
      break;
    case(ByCSC) :
      t_ = ByCSC;
      rows_ = r;
      cols_ = c;
      m_lin = new CSC(r, c, r, indices);
      break;
    default:
      break;
  }
  return;
}
void Data::load_colors_comp(const std::vector< std::size_t > & indices) {
  if(m_lin == nullptr) {
    throw std::logic_error("Data::load_colors_comp : nullptr");
  }
  switch(t_) {
    case(ByCSR) :
      load_colors_byCSR(m_lin, indices);
      break;
    case(ByCSC) :
      load_colors_byCSC(m_lin, indices);
      break;
    default:
    throw std::logic_error("Data::load_colors_comp : not compact matrix");
      break;
  }
  return;
}
void Data::load_moving_colors_comp(const std::vector< std::size_t > & indices) {
  if(m_lin == nullptr) {
    throw std::logic_error("Data::load_mov_colors_comp : nullptr");
  }
  switch(t_) {
    case(ByCSR) :
      load_moving_colors_byCSR(m_lin, indices);
      break;
    case(ByCSC) :
      load_moving_colors_byCSC(m_lin, indices);
      break;
    default:
    throw std::logic_error("Data::load_mov_colors_comp : not compact matrix");
      break;
  }
  return;
}
void Data::unload_moving_colors_comp(MoveType move_type) {
  switch(move_type) {
    case(MoveColor) :
      delete data_white;
      data_white = nullptr;
      break;
    case(MoveWhite) :
      delete data_blue;
      data_blue = nullptr;
      delete data_red;
      data_red = nullptr;
      break;
    default:
    throw std::logic_error("Data::load_mov_colors_comp : not moving type");
      break;
  }
  return;
}

std::istream & operator>>(std::istream & is, Data & d){
  d.load_input(is);
  d.load_matrix();
//  d.update_statistics();
  return is;
}
void Data::load_input(std::istream & is) {
  std::string line;
  while(getline(is, line)) {
    tok_push_back(line);
  }
  // updated also rows_ cols_
  return;
}
void Data::load_matrix() {
  if(cols_ <= rows_) {
    t_ = ByRows;
    if(m_lin != nullptr) {
     delete m_lin;
    }
    
    m_lin = new MatrixRow(rows_, cols_);
    m_lin->load_same_order(* m_inp);
    
    if(m_inp != nullptr) {
      delete m_inp;
      m_inp = nullptr;
    }
    load_colors_byrows(m_lin);
  } else {
    t_ = ByCols;
    if(m_lin != nullptr) {
     delete m_lin;
    }

    m_lin = new MatrixCol(rows_, cols_);
    m_lin->load_tran_order(* m_inp);

    if(m_inp != nullptr) {
      delete m_inp;
      m_inp = nullptr;
    }
    load_colors_bycols(m_lin);
  }
  return;
}
void Data::load_colors_byrows(const Matrix * ptr) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors from nullptr");
  }
  if(white != nullptr) {
    delete white;
    }
  if(blue != nullptr) {
    delete blue;
    }
  if(red != nullptr) {
    delete red;
    }
  white = new OneColor;
  blue = new OneColor;
  red = new OneColor;
  std::vector< Scalar >::const_iterator it_from = ptr->begin();
  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t i = 0; i < rows_; ++i) {
    for(std::size_t j = 0; j < cols_; ++j) {
      switch( * it_from ) {
        case(White):
          white->push_back( Coordinates(i,j) );
          break;
        case(Blue):
          blue->push_back( Coordinates(i,j) );
          break;
        case(Red):
          red->push_back( Coordinates(i,j) );
          break;
        default:
          break;
      }
    ++it_from;
    }
  }
  white_count_ = white->size();
  blue_count_ = blue->size();
  red_count_ = red->size();
  return;
}
void Data::load_colors_bycols(const Matrix * ptr) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors from nullptr");
  }
  if(white != nullptr) {
    delete white;
    }
  if(blue != nullptr) {
    delete blue;
    }
  if(red != nullptr) {
    delete red;
    }
  white = new OneColor;
  blue = new OneColor;
  red = new OneColor;
  std::vector< Scalar >::const_iterator it_from = ptr->begin();
  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t j = 0; j < cols_; ++j) {
    for(std::size_t i = 0; i < rows_; ++i) {
      switch( * it_from ) {
        case(White):
          white->push_back( Coordinates(i,j) );
          break;
        case(Blue):
          blue->push_back( Coordinates(i,j) );
          break;
        case(Red):
          red->push_back( Coordinates(i,j) );
          break;
        default:
          break;
      }
    ++it_from;
    }
  }
  white_count_ = white->size();
  blue_count_ = blue->size();
  red_count_ = red->size();
  return;
}
OneColor & switch_color(const Scalar & s, OneColor & white, OneColor & blue, OneColor & red) {
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
          throw std::logic_error("switch_color exception");
          break;
      }
}
DataColor & switch_moving_color(const Scalar & s, DataColor & white, DataColor & blue, DataColor & red) {
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
          throw std::logic_error("switch_moving_color exception");
          break;
      }
}

void Data::load_colors_byCSR(const Matrix * ptr, const std::vector< std::size_t > & indices) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors_byCSR from nullptr");
  }
  if(indices.empty()) {
    throw std::logic_error("Data::load_colors_byCSR with empty indices");
    }
  if(white != nullptr) {
    delete white;
    }
  if(blue != nullptr) {
    delete blue;
    }
  if(red != nullptr) {
    delete red;
    }
  if(first != nullptr) {
    delete first;
    }
  if(last != nullptr) {
    delete last;
    }
  white = new OneColor;
  blue = new OneColor;
  red = new OneColor;
  first = new ThreeColor;
  last = new ThreeColor;
  
  std::vector< Scalar >::const_iterator it_from = ptr->begin();

  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t j = 0; j < cols_; j++) {
    switch_color(* it_from, first->white, first->blue, first->red).push_back(Coordinates(indices[0], j));
    ++it_from;
  }
  for(std::size_t i = 1; i < indices.size() - 1 ; ++i) {
    for(std::size_t j = 0; j < cols_; ++j) {
    switch_color(* it_from, * white, * blue, * red).push_back(Coordinates(indices[i], j));
    ++it_from;
    }
  }
  for(std::size_t j = 0; j < cols_; j++) {
    switch_color(* it_from, last->white, last->blue, last->red).push_back(Coordinates(indices[ indices.size() - 1 ], j));
    ++it_from;
  }

  white_count_  = white->size() + last->white.size();
  blue_count_   = blue->size()  + last->blue.size();
  red_count_    = red->size()   + last->red.size();
  return;
}
void Data::load_colors_byCSC(const Matrix * ptr, const std::vector< std::size_t > & indices) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors_byCSC from nullptr");
  }
  if(indices.empty()) {
    throw std::logic_error("Data::load_colors_byCSC with empty indices");
    }
  if(white != nullptr) {
    delete white;
    }
  if(blue != nullptr) {
    delete blue;
    }
  if(red != nullptr) {
    delete red;
    }
  if(first != nullptr) {
    delete first;
    }
  if(last != nullptr) {
    delete last;
    }
  white = new OneColor;
  blue = new OneColor;
  red = new OneColor;
  first = new ThreeColor;
  last = new ThreeColor;
  
  std::vector< Scalar >::const_iterator it_from = ptr->begin();

  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t i = 0; i < rows_; i++) {
    switch_color(* it_from, first->white, first->blue, first->red).push_back(Coordinates(i, indices[0]));
    ++it_from;
  }
  for(std::size_t j = 1; j < indices.size() - 1 ; ++j) {
    for(std::size_t i = 0; i < rows_; ++i) {
    switch_color(* it_from, * white, * blue, * red).push_back(Coordinates(i, indices[j]));
    ++it_from;
    }
  }
  for(std::size_t i = 0; i < rows_; i++) {
    switch_color(* it_from, last->white, last->blue, last->red).push_back(Coordinates(i, indices[ indices.size() - 1 ]));
    ++it_from;
  }

  white_count_  = white->size() + last->white.size();
  blue_count_   = blue->size()  + last->blue.size();
  red_count_    = red->size()   + last->red.size();
  return;
}
void Data::load_moving_colors_byCSR(const Matrix * ptr, const std::vector< std::size_t > & indices) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors_byCSR from nullptr");
  }
  if(indices.empty()) {
    throw std::logic_error("Data::load_colors_byCSR with empty indices");
    }
  if(data_white != nullptr) {
    delete data_white;
  }
  if(data_blue != nullptr) {
    delete data_blue;
  }
  if(data_red != nullptr) {
    delete data_red;
  }
  std::size_t inn_count = m_lin->inn_count();
  std::size_t ext_count = m_lin->ext_count();

  data_white = new DataColor(ext_count, inn_count);
  data_blue = new DataColor(ext_count, inn_count);
  data_red =  new DataColor(ext_count, inn_count);
  
  std::vector< Scalar >::const_iterator it_from = ptr->begin();

  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t j = 0; j < cols_; j++) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, * data_red);
    c.first.push_back(j);
    ++it_from;
  }
  for(std::size_t i = 1; i < indices.size() - 1 ; ++i) {
    for(std::size_t j = 0; j < cols_; ++j) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, * data_red);
    c.inside.push_back(Coordinates(indices[i], j));
    ++it_from;
    }
  }
  for(std::size_t j = 0; j < cols_; j++) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, * data_red);
    c.last.push_back(j);
    ++it_from;
  }

  white_count_  = data_white->inside.size() + data_white->last.size();
  blue_count_  = data_blue->inside.size() + data_blue->last.size();
  red_count_  = data_red->inside.size() + data_red->last.size();
  return;
}
void Data::load_moving_colors_byCSC(const Matrix * ptr, const std::vector< std::size_t > & indices) {
  if(ptr == nullptr) {
    throw std::logic_error("Data::load_colors_byCSR from nullptr");
  }
  if(indices.empty()) {
    throw std::logic_error("Data::load_colors_byCSR with empty indices");
    }
  if(data_white != nullptr) {
    delete data_white;
  }
  if(data_blue != nullptr) {
    delete data_blue;
  }
  if(data_red != nullptr) {
    delete data_red;
  }
  
  std::size_t inn_count = m_lin->inn_count();
  std::size_t ext_count = m_lin->ext_count();

  data_white = new DataColor(ext_count, inn_count);
  data_blue = new DataColor(ext_count, inn_count);
  data_red =  new DataColor(ext_count, inn_count);
  
  std::vector< Scalar >::const_iterator it_from = ptr->begin();

  rows_ = ptr->rows_count();
  cols_ = ptr->cols_count();
  for(std::size_t i = 0; i < rows_; i++) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, *data_red);
    c.first.push_back(i);
    ++it_from;
  }
  for(std::size_t j = 1; j < indices.size() - 1 ; ++j) {
    for(std::size_t i = 0; i < rows_; ++i) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, * data_red);
    c.inside.push_back(Coordinates(i, indices[j]));
    ++it_from;
    }
  }
  for(std::size_t i = 0; i < rows_; i++) {
    DataColor & c = switch_moving_color(* it_from, * data_white, * data_blue, * data_red);
    c.last.push_back(i);
    ++it_from;
  }

  white_count_  = data_white->inside.size() + data_white->last.size();
  blue_count_  = data_blue->inside.size() + data_blue->last.size();
  red_count_  = data_red->inside.size() + data_red->last.size();
  return;
}

void Data::update_statistics() {
  if(m_lin != nullptr && rows_ != m_lin->rows_count()) {
    throw std::logic_error("Data::update_statistics rows error");
  }
  if(m_lin != nullptr && cols_ != m_lin->cols_count()) {
    throw std::logic_error("Data::update_statistics cols error");
  }
  if(white != nullptr && white_count_ != white->size()) {
    throw std::logic_error("Data::update_statistics white error");
  }
  if(blue != nullptr && blue_count_ != blue->size()) {
    throw std::logic_error("Data::update_statistics blue error");
  }
  if(red != nullptr && red_count_ != red->size()) {
    throw std::logic_error("Data::update_statistics red error");
  }
  return;
}

void Data::tok_push_back(const std::string & line) {
  const std::size_t line_len = line.length();
  const std::size_t line_cols = (line_len + 1) / 2;
  if(m_inp->empty()) {
    cols_ = line_cols;
  } else if(cols_ != line_cols) {
    throw std::runtime_error("Data::tok_push_back row with different length");
    return;
  }
  ++rows_;
  
	m_inp->push_back(std::vector< Scalar >(line_cols));
	std::vector< Scalar > & row_to = * -- m_inp->end();

	const char * ptr_to_one = & line[0];
	
  for(std::vector< Scalar >::iterator it = row_to.begin() ; it < row_to.end(); ++it) {
    Scalar c = static_cast< Scalar >(* ptr_to_one -START);
    * it = c;
    ptr_to_one += 2;
  }
  return;
}


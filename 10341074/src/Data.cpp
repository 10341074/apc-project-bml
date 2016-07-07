#include "Data.h"

#define START '0'

void load_same_order(const std::list< std::vector< Scalar > > & m_inp, std::vector< Scalar > & mat, std::size_t & ext_count, std::size_t & inn_count) {
  ext_count = m_inp.size();
  if(m_inp.empty())
    throw std::runtime_error("load_same_order: empty list");
  inn_count = m_inp.begin()->size();
  if(inn_count == 0)
    throw std::runtime_error("load_same_order: list of empty vectors");

  mat.resize(ext_count * inn_count);
  
  std::vector< Scalar >::iterator it_to = mat.begin();
  for(std::list< std::vector< Scalar > >::const_iterator it_ext = m_inp.begin(); it_ext != m_inp.end(); ++it_ext) {
    for(std::vector< Scalar >::const_iterator it_inn = it_ext->begin(); it_inn != it_ext->end(); ++it_inn) {
      * it_to = * it_inn;
      ++it_to;
    }
  }
  return;
}
void load_tran_order(const std::list< std::vector< Scalar > > & m_inp, std::vector< Scalar > & mat, std::size_t & ext_count, std::size_t & inn_count) {
  inn_count = m_inp.size();
  if(m_inp.empty())
    throw std::runtime_error("load_tran_order: empty list");
  ext_count = m_inp.begin()->size();
  if(ext_count == 0)
    throw std::runtime_error("load_tran_order: list of empty vectors");

  mat.resize(ext_count * inn_count);
  
  std::vector< Scalar >::iterator it_to = mat.begin();
  
  // behaviour: Const_ColumnIt as std::vector<const T>
  Const_ColumnIt column(m_inp);

  for(std::size_t it_ext = 0; it_ext < ext_count; ++it_ext) {
    for(Const_ColumnIt::const_iterator it_inn = column.begin(); it_inn != column.end(); ++it_inn) {
      * it_to = * it_inn; // unmodified
      ++it_to;
    }
    ++column;
  }
  return;
}

Data::Data(MatrixType t) : t_(t) {
  switch(t) {
    case(Input) :
      if(m_inp != nullptr)
        delete m_inp;
      m_inp = new MatrixInp;
      break;
    case(None) :
      if(m_inp != nullptr)
        delete m_inp;
      m_inp = nullptr;
      break;
    default:
      if(m_inp != nullptr)
        delete m_inp;
      m_inp = nullptr;
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
      throw std::logic_error("Data::build_comp with not compact type");
      break;
  }
  return;
}

std::istream & operator>>(std::istream & is, Data & d){
  d.load_input(is);
  d.load_matrix();
  return is;
}
std::ostream & operator<<(std::ostream & os, Data & d) {
  if(d.m_lin!=nullptr) 
    os << * d.m_lin;
  return os;
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
  if(m_inp == nullptr)
    throw std::logic_error("Data::load_matrix from null input matrix");
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
//    load_colors_byrows(m_lin);
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
//    load_colors_bycols(m_lin);
  }
  return;
}
void Data::load_matrix(MatrixType t) {
  if(m_inp == nullptr)
    throw std::logic_error("Data::load_matrix(type) from null input matrix");
  switch(t) {
    case(ByRows) :
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
      break;
    case(ByCols) :
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
      break;
    default:
      throw std::logic_error("Data::load_matrix(type) with not fill type matrix");
      break;
  }
  return;
}

void Data::tok_push_back(const std::string & line) {
  const std::size_t line_len = line.length();
  const std::size_t line_cols = (line_len + 1) / 2;
  if(m_inp->empty()) {
    cols_ = line_cols;
  } else if(cols_ != line_cols) {
    std::cout << "line_len " << line_cols << std::endl;
    std::cout << "cols " << cols_ << std::endl;
    std::cout << "rows " << rows_ << std::endl;
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


#include "CSC.h"	

CSC::CSC(std::size_t r, std::size_t c) : rows_(r), cols_(c) {
}
CSC::CSC(std::size_t r, std::size_t c, size_type n) : Matrix(n), rows_(r), cols_(c) {
  if(r != n)
    throw std::logic_error("CSC construction wrong dimensions");
}
CSC::CSC(std::size_t r, std::size_t c, size_type n, const std::vector< std::size_t > & indices) : Matrix(indices.size(), n), rows_(r), cols_(c), J_(c+1) {
  if(r != n || indices.size() > c)
    throw std::logic_error("CSC construction wrong dimensions");
  std::size_t indices_k = 0;
  std::size_t current_position = 0;
  for(std::size_t col = 0; col < c; ++col) {
    J_[col] = current_position;
    if(indices[indices_k] == col ) {
      ++indices_k;
      current_position += n;
    }
  }
  J_[c] = indices.size() * n;
}
CSC::CSC(std::size_t r, std::size_t c, size_type n, const std::vector< std::size_t > & indices, const Scalar & val) : Matrix(indices.size(), n, val), rows_(r), cols_(c), J_(c+1) {
  if(r != n || indices.size() > c)
    throw std::logic_error("CSC construction wrong dimensions");
  std::size_t indices_k = 0;
  std::size_t current_position = 0;
  for(std::size_t col = 0; col < c; ++col) {
    J_[col] = current_position;
    if(indices[indices_k] == col ) {
      ++indices_k;
      current_position += n;
    }
  }
  J_[c] = indices.size() * n;
}

CSC::~CSC() {}

/*
Vector<Scalar> * CSC::row_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
Vector<Scalar> * CSC::column_vector(size_type ind) {throw std::logic_error("Function not defined for CSC"); return nullptr;}
*/
/*
std::vector< Scalar > * CSC::row_copy(size_type ind) const {
  return inn_vec_copy(ind);
}
std::vector< Scalar > * CSC::col_copy(size_type ind) const {
  return ext_vec_copy(ind);
}
*/
void CSC::print_matrix() const {
  std::size_t m = inn_count_;
  std::size_t n = ext_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n; ++j) {
      std::cout << mat[(j * m) + i] << '\t';
    }
    std::cout << '\n';
  }
  return;
}

void CSC::print_elements(std::ostream & os) const {
  std::size_t m = inn_count_;
  std::size_t n = ext_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n; ++j) {
      os << mat[(j * m) + i] << Separator;
    }
    os << '\n';
  }
  return;
}

Scalar & CSC::operator()(size_type i, size_type j) {
  if(i >= rows_count() || j >= cols_count(  )) throw std::out_of_range("CSC::operator() : out of range");
  if(J_[j+1] == J_[j])
    throw std::logic_error("CSC::operator() : matrix doesn't contain this element");
  return mat[J_[j] + i];
}
const Scalar & CSC::operator()(size_type i, size_type j) const {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("CSC::operator() : out of range");
  if(J_[j+1] == J_[j])
    throw std::logic_error("CSC::operator() : matrix doesn't contain this element");
  return mat[J_[j] + i];
}


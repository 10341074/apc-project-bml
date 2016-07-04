#include "CSR.h"	

CSR::CSR(std::size_t r, std::size_t c) : rows_(r), cols_(c) {
}
CSR::CSR(std::size_t r, std::size_t c, size_type n) : Matrix(n), rows_(r), cols_(c) {
  if(c != n)
    throw std::logic_error("CSR construction wrong dimensions");
}
CSR::CSR(std::size_t r, std::size_t c, const std::vector< std::size_t > & indices, size_type n) : Matrix(indices.size(), n), rows_(r), cols_(c), I_(r+1) {
  if(c != n || indices.size() > r)
    throw std::logic_error("CSR construction wrong dimensions");
  std::size_t indices_k = 0;
  std::size_t current_position = 0;
  for(std::size_t row = 0; row < r; ++row) {
    I_[row] = current_position;
    if(indices[indices_k] == row ) {
      ++indices_k;
      current_position += n;
    }
  }
  I_[r] = indices.size() * n;
}
CSR::CSR(std::size_t r, std::size_t c, const std::vector< std::size_t > & indices, size_type n, const Scalar & val) : Matrix(indices.size(), n, val), rows_(r), cols_(c), I_(r+1) {
  if(c != n || indices.size() > r)
    throw std::logic_error("CSR construction wrong dimensions");
  std::size_t indices_k = 0;
  std::size_t current_position = 0;
  for(std::size_t row = 0; row < r; ++row) {
    I_[row] = current_position;
    if(indices[indices_k] == row ) {
      ++indices_k;
      current_position += n;
    }
  }
  I_[r] = indices.size() * n;
}

CSR::~CSR() {}

/*
Vector<Scalar> * CSR::row_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
Vector<Scalar> * CSR::column_vector(size_type ind) {throw std::logic_error("Function not defined for CSR"); return nullptr;}
*/
/*
std::vector< Scalar > * CSR::row_copy(size_type ind) const {
  return inn_vec_copy(ind);
}
std::vector< Scalar > * CSR::col_copy(size_type ind) const {
  return ext_vec_copy(ind);
}
*/

void CSR::print_matrix(std::ostream & os) const {
  std::size_t m = ext_count_;
  std::size_t n = inn_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n - 1; ++j) {
      os << mat[(i * n) + j] << Separator;
    }
  os << mat[i * n + n - 1] << std::endl;
  }
  return;
}

Scalar & CSR::operator()(size_type i, size_type j) {
  if(i >= rows_count() || j >= cols_count(  )) throw std::out_of_range("CSR::operator() : out of range");
  if(I_[i+1] == I_[i])
    throw std::logic_error("CSR::operator() : matrix doesn't contain this element");
  return mat[I_[i] + j];
}
const Scalar & CSR::operator()(size_type i, size_type j) const {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("CSR::operator() : out of range");
  if(I_[i+1] == I_[i])
    throw std::logic_error("CSR::operator() : matrix doesn't contain this element");
  return mat[I_[i] + j];
}


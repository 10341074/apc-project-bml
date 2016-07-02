#include "MatrixRow.h"	

MatrixRow::MatrixRow() {}
MatrixRow::MatrixRow(size_type n) : Matrix(n) {}
MatrixRow::MatrixRow(size_type m, size_type n) : Matrix(m, n) {}
MatrixRow::MatrixRow(size_type m, size_type n, const Scalar & val) : Matrix(m, n, val) {}

MatrixRow::~MatrixRow() {}
/*
Vector<Scalar> * MatrixRow::row_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
Vector<Scalar> * MatrixRow::column_vector(size_type ind) {throw std::logic_error("Function not defined for MatrixRow"); return nullptr;}
*/
/*
std::vector< Scalar > * MatrixRow::row_copy(size_type ind) const {
  return inn_vec_copy(ind);
}
std::vector< Scalar > * MatrixRow::col_copy(size_type ind) const {
  return ext_vec_copy(ind);
}
*/
void MatrixRow::print_matrix() const {
  std::size_t m = ext_count_;
  std::size_t n = inn_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n; ++j) {
      std::cout << mat[(i * n) + j] << '\t';
    }
    std::cout << '\n';
  }
  return;
}

void MatrixRow::print_elements(std::ostream & os) const {
  std::size_t m = ext_count_;
  std::size_t n = inn_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n; ++j) {
      os << mat[(i * n) + j] << Separator;
    }
    os << '\n';
  }
  return;
}
Scalar & MatrixRow::operator()(size_type i, size_type j) {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("MatrixRow::operator() : out of range");
  return mat[(i * cols_count()) + j];
}
const Scalar & MatrixRow::operator()(size_type i, size_type j) const {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("MatrixRow::operator() : out of range");
  return mat[(i * cols_count()) + j];
}

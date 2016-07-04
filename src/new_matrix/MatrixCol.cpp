#include "MatrixCol.h"	

MatrixCol::MatrixCol(){}
MatrixCol::MatrixCol(size_type n) : Matrix(n) {}
MatrixCol::MatrixCol(size_type m, size_type n) : Matrix(n, m) {}
MatrixCol::MatrixCol(size_type m, size_type n, const Scalar & val) : Matrix(n, m, val) {}

MatrixCol::~MatrixCol() {}
/*
Vector<Scalar> * MatrixCol::row_vector(size_type ind) {throw std::logic_error("Function not defined for MatrixCol"); return nullptr;}
Vector<Scalar> * MatrixCol::column_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
*/
/*
std::vector< Scalar > * MatrixCol::row_copy(size_type ind) const {
  return ext_vec_copy(ind);
}
std::vector< Scalar > * MatrixCol::col_copy(size_type ind) const {
  return inn_vec_copy(ind);
}
*/

void MatrixCol::print_matrix(std::ostream & os) const {
  std::size_t m = inn_count_;
  std::size_t n = ext_count_;
  for(std::size_t i=0; i < m; ++i) {
    for(std::size_t j=0; j < n - 1; ++j) {
      os << mat[(j * m) + i] << Separator;
    }
    os << mat[(n - 1) * m + i] << std::endl;
  }
  return;
}
Scalar & MatrixCol::operator()(size_type i, size_type j) {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("MatrixCol::operator() : out of range");
  return mat[(j * rows_count()) + i];
}
const Scalar & MatrixCol::operator()(size_type i, size_type j) const {
  if(i >= rows_count() || j >= cols_count()) throw std::out_of_range("MatrixRow::operator() : out of range");
  return mat[(j * rows_count()) + i];
}

#include "Matrix.h"

Matrix::Matrix(){}
Matrix::Matrix(size_type n) : mat(n * n), ext_count_(n), inn_count_(n) {}
Matrix::Matrix(size_type a, size_type b) : mat(a * b), ext_count_(a), inn_count_(b) {}
Matrix::Matrix(size_type a, size_type b, const Scalar & val) : mat(a * b, val), ext_count_(a), inn_count_(b) {}

Matrix::~Matrix(){}

/*
Vector<Scalar> * Matrix::first_vec_vector(size_type ind){
	if(ind>=first_count()) throw std::out_of_range("Outside matrix");
	return &mat[ind];}
*/

std::vector< Scalar > * Matrix::inn_vec_copy(size_type ind) const {
  if(ind >= ext_count_) throw std::out_of_range("Matrix::inn_vec_copy : out of range");

  std::vector< Scalar >::const_iterator it = mat.begin() + ind;
  std::vector< Scalar > * ptr = new std::vector< Scalar >(it, it + inn_count_);
  return ptr;
}

std::vector< Scalar > * Matrix::ext_vec_copy(size_type ind) const {
  if(ind >= inn_count_) throw std::out_of_range("Matrix::ext_vec_copy : out of range");

  std::vector< Scalar > * ptr = new std::vector< Scalar >(ext_count_);
  std::vector< Scalar >::const_iterator   it_from = mat.begin();
  std::vector< Scalar >::iterator         it_to = ptr->begin();
  for(std::size_t k = 0; k < inn_count_; ++k) {
    * it_to = * it_from;
    std::advance(it_from, ext_count_);
    ++it_to;
  }
  return ptr;
}
		
void Matrix::info() const {
  std::cout << "number of rows = " << rows_count() << std::endl;
  std::cout << "number of cols = " << cols_count() << std::endl;
  return;
}

std::ostream & operator<<(std::ostream & os, const Matrix & m){
  m.print_elements(os);	//trick for virtual stream operator
	return os;}


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

std::ostream & operator<<(std::ostream & os, const Matrix & m) {
  m.print_matrix(os);	//trick for virtual stream operator
	return os;}
	
void Matrix::load_same_order(const std::list< std::vector< Scalar > > & m_inp) {
  ext_count_ = m_inp.size();
  if(m_inp.empty())
    throw std::runtime_error("load_same_order: empty list");
  inn_count_ = m_inp.begin()->size();
  if(inn_count_ == 0)
    throw std::runtime_error("load_same_order: list of empty vectors");
  mat.resize(ext_count_ * inn_count_);
  
  std::vector< Scalar >::iterator it_to = mat.begin();
  for(std::list< std::vector< Scalar > >::const_iterator it_ext = m_inp.begin(); it_ext != m_inp.end(); ++it_ext) {
    for(std::vector< Scalar >::const_iterator it_inn = it_ext->begin(); it_inn != it_ext->end(); ++it_inn) {
      * it_to = * it_inn;
      ++it_to;
    }
  }
  return;
}
void Matrix::load_tran_order(const std::list< std::vector< Scalar > > & m_inp) {
  inn_count_ = m_inp.size();
  if(m_inp.empty())
    throw std::runtime_error("load_tran_order: empty list");
  ext_count_ = m_inp.begin()->size();
  if(ext_count_ == 0)
    throw std::runtime_error("load_tran_order: list of empty vectors");
  mat.resize(ext_count_ * inn_count_);
  
  std::vector< Scalar >::iterator it_to = mat.begin();
  
  // behaviour: Const_ColumnIt as std::vector<const T>
  Const_ColumnIt column(m_inp);

  for(std::size_t it_ext = 0; it_ext < ext_count_; ++it_ext) {
    for(Const_ColumnIt::const_iterator it_inn = column.begin(); it_inn != column.end(); ++it_inn) {
      * it_to = * it_inn; // unmodified
      ++it_to;
    }
    ++column;
  }
  return;
}


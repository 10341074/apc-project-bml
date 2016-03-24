#include <iostream>
#include <stdexcept>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Matrix.h"

Matrix::Matrix(){}
Matrix::Matrix(size_type n) : mat(n,Vector<Scalar>(n)){}
Matrix::Matrix(size_type a,size_type b) : mat(a,Vector<Scalar>(b)){}
Matrix::Matrix(size_type a,size_type b,const Scalar & val) : mat(a,Vector<Scalar>(b,val)){}

Matrix::Matrix(Matrix * ptr): mat(ptr->mat) {}
Matrix::Matrix(std::unique_ptr<Matrix> & ptr): mat(ptr->mat) {}					//unique ptr can be pass by ref

Matrix::Matrix(std::shared_ptr<Sparse> ptr): Matrix(ptr->rows(),ptr->cols(),0) {}
Matrix::Matrix(std::unique_ptr<Symmetric> & ptr): Matrix(ptr->rows(),ptr->cols()) {}
Matrix::~Matrix(){}


Vector<Scalar> * Matrix::first_vec_vector(size_type ind){
	if(ind>=first_count()) throw std::out_of_range("Outside matrix");
	return &mat[ind];}

Vector<Scalar> * Matrix::first_vec_copy(size_type ind) const {
	if(ind>=first_count()) throw std::out_of_range("Outside matrix");
	Vector<Scalar> * ptr = new Vector<Scalar>(mat[ind]);
	return ptr;}

Vector<Scalar> * Matrix::second_vec_copy(size_type ind) const {
	if(ind>=second_count()) throw std::out_of_range("Outside matrix");
	size_type length=first_count();
	Vector<Scalar> * ptr = new Vector<Scalar>(length,0);
		for(std::size_t it=0;it<length;++it)
			(*ptr)[it]=mat[it][ind];
		return ptr;}
		
void Matrix::info() const {
	std::cout<<"number of rows= "<<row_count()<<std::endl;
	std::cout<<"number of cols= "<<column_count()<<std::endl;
	return;}

std::ostream & operator<<(std::ostream & os,const Matrix & m){
	m.print_elements(os);	//trick for virtual stream operator
	return os;}


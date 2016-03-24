#include <iostream>
#include <stdexcept>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Matrix.h"
#include "MatrixCol.h"	

MatrixCol::MatrixCol(){}
MatrixCol::MatrixCol(size_type n) : Matrix(n){}
MatrixCol::MatrixCol(size_type m,size_type n) : Matrix(n,m){}
MatrixCol::MatrixCol(size_type m,size_type n,const Scalar & val) : Matrix(n,m,val){}

MatrixCol::MatrixCol(Matrix * ptr) : Matrix(ptr) {}
MatrixCol::MatrixCol(std::unique_ptr<Matrix> & ptr): Matrix(ptr) {}

MatrixCol::MatrixCol(std::shared_ptr<Sparse> ptr): Matrix(ptr->cols(),ptr->rows(),0) {
		auto it_end=(ptr->A).end();
		for(auto it=(ptr->A).begin();it<it_end;++it)
			*item_add(it->i,it->j)=it->item;
		}
MatrixCol::MatrixCol(std::unique_ptr<Symmetric> & ptr): Matrix(ptr) {
	sim_type * it=ptr->begin();
	std::size_t n=ptr->cols();
	for(std::size_t j=0;j<n;++j)
		for(std::size_t i=0;i<=j;++i){
			*item_add(i,j)=*it;
			*item_add(j,i)=*it;
			++it;}	// sort of Symmetric
	}

MatrixCol::~MatrixCol(){}

Vector<Scalar> * MatrixCol::row_vector(size_type ind) {throw std::logic_error("Function not defined for MatrixCol"); return nullptr;}
Vector<Scalar> * MatrixCol::column_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
Vector<Scalar> * MatrixCol::row_copy(size_type ind) const {return this->second_vec_copy(ind);}
Vector<Scalar> * MatrixCol::column_copy(size_type ind) const {return this->first_vec_copy(ind);}

void MatrixCol::print_matrix() const {
	std::size_t i_len=this->second_count(), j_len=this->first_count();
	for(std::size_t i=0;i<i_len;++i){
		for(std::size_t j=0;j<j_len;++j)
			std::cout<<this->mat[j][i]<<'\t';
		std::cout<<'\n';}	
	return;}

void MatrixCol::print_elements(std::ostream & os) const {	// trick for print matrix using streams
	std::size_t j_len=this->first_count(), i_len=this->second_count();
	for(std::size_t j=0;j<j_len;++j)
		for(std::size_t i=0;i<i_len;++i)
			os<<i+1<<SEPARATOR<<j+1<<SEPARATOR<<this->mat[j][i]<<std::endl;	//correction 1-based
	return;}

Scalar * MatrixCol::item_add(size_type i,size_type j){
	if(i>=row_count() || j>=column_count()) throw std::out_of_range("Error: item outside matrix");
	return &(this->mat[j][i]);}
	
const Scalar MatrixCol::item(size_type i,size_type j) const{
	if(i>=row_count() || j>=column_count()) throw std::out_of_range("Error: item outside matrix");
	return this->mat[j][i];}

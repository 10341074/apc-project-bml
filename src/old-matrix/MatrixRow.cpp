#include <iostream>
#include <stdexcept>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Matrix.h"
#include "MatrixRow.h"	

MatrixRow::MatrixRow(){}
MatrixRow::MatrixRow(size_type n) : Matrix(n){}
MatrixRow::MatrixRow(size_type m,size_type n) : Matrix(m,n){}												// row
MatrixRow::MatrixRow(size_type m,size_type n,const Scalar & val) : Matrix(m,n,val){}				// row

MatrixRow::MatrixRow(Matrix * ptr) : Matrix(ptr) {}
MatrixRow::MatrixRow(std::unique_ptr<Matrix> & ptr): Matrix(ptr) {}

MatrixRow::MatrixRow(std::shared_ptr<Sparse> ptr): Matrix(ptr->rows(),ptr->cols(),0) {				// row
		auto it_end=(ptr->A).end();
		for(auto it=(ptr->A).begin();it<it_end;++it)
			*item_add(it->i,it->j)=it->item;
		}
MatrixRow::MatrixRow(std::unique_ptr<Symmetric> & ptr): Matrix(ptr) {
	sim_type * it=ptr->begin();
	std::size_t n=ptr->cols();
	for(std::size_t j=0;j<n;++j)
		for(std::size_t i=0;i<=j;++i){
			*item_add(i,j)=*it;
			*item_add(j,i)=*it;
			++it;}	// sort of Symmetric
	}

MatrixRow::~MatrixRow(){}

Vector<Scalar> * MatrixRow::row_vector(size_type ind) {return this->first_vec_vector(ind);}	//exceptions in base member
Vector<Scalar> * MatrixRow::column_vector(size_type ind) {throw std::logic_error("Function not defined for MatrixRow"); return nullptr;}
Vector<Scalar> * MatrixRow::row_copy(size_type ind) const {return this->first_vec_copy(ind);}		// row
Vector<Scalar> * MatrixRow::column_copy(size_type ind) const {return this->second_vec_copy(ind);}	// row

void MatrixRow::print_matrix() const {
	std::size_t i_len=this->first_count(), j_len=this->second_count();										// row
	for(std::size_t i=0;i<i_len;++i){
		for(std::size_t j=0;j<j_len;++j)
			std::cout<<this->mat[i][j]<<'\t';																			// row
		std::cout<<'\n';}	
	return;}

void MatrixRow::print_elements(std::ostream & os) const {	// trick for print matrix using streams
	std::size_t j_len=this->second_count(), i_len=this->first_count();										// row
	for(std::size_t j=0;j<j_len;++j)
		for(std::size_t i=0;i<i_len;++i)
			os<<i+1<<SEPARATOR<<j+1<<SEPARATOR<<this->mat[i][j]<<std::endl;	//correction 1-based		// row
	return;}

Scalar * MatrixRow::item_add(size_type i,size_type j){
	if(i>=row_count() || j>=column_count()) throw std::out_of_range("Error: item outside matrix");
	return &(this->mat[i][j]);}																							// row
	
const Scalar MatrixRow::item(size_type i,size_type j) const{
	if(i>=row_count() || j>=column_count()) throw std::out_of_range("Error: item outside matrix");
	return this->mat[i][j];}																								// row

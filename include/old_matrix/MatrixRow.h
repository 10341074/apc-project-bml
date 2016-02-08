#ifndef MATRIX_ROW_H
#define MATRIX_ROW_H
#include <iostream>
#include <stdexcept>
#include <memory>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Symmetric.h"
#include "Matrix.h"

class MatrixRow: public Matrix{
	public:
	MatrixRow();
	MatrixRow(size_type n);
	MatrixRow(size_type m,size_type n);
	MatrixRow(size_type m,size_type n,const Scalar & val);

	MatrixRow(Matrix * ptr);
	MatrixRow(std::unique_ptr<Matrix> & ptr);
//	Matrix(std::shared_ptr<Matrix> & ptr);

//	MatrixRow(Sparse * ptr);
	MatrixRow(std::shared_ptr<Sparse> ptr);
//	MatrixRow(const Sparse & src); 
	MatrixRow(std::unique_ptr<Symmetric> & ptr);
	virtual ~MatrixRow();
	
	inline size_type row_count() const override {return first_count();}					// number of rows		// row
	inline size_type column_count() const override {return second_count();}				// number of cols		// row
	Vector<Scalar> * row_vector(size_type ind) override;		// unsafe to dealloc
	Vector<Scalar> * column_vector(size_type ind) override;	// not implemented
	Vector<Scalar> * row_copy(size_type ind) const override;
	Vector<Scalar> * column_copy(size_type ind) const override;
	void print_matrix() const override;
	void print_elements(std::ostream & os) const override;							// trick for print matrix using streams + correction 1-based
	Scalar * item_add(size_type i,size_type j) override;
	const Scalar item(size_type i,size_type j) const override;
	void what() const override {std::cout<<"I'm a MatrixRow"<<std::endl;}
	};//finish class

#endif

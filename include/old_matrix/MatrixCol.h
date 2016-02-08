#ifndef MATRIX_COL_H
#define MATRIX_COL_H
#include <iostream>
#include <stdexcept>
#include <memory>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Symmetric.h"
#include "Matrix.h"

class MatrixCol: public Matrix{
	public:
	MatrixCol();
	MatrixCol(size_type n);
	MatrixCol(size_type m,size_type n);
	MatrixCol(size_type m,size_type n,const Scalar & val);

	MatrixCol(Matrix * ptr);
	MatrixCol(std::unique_ptr<Matrix> & ptr);
//	Matrix(std::shared_ptr<Matrix> & ptr);

//	MatrixCol(Sparse * ptr);
	MatrixCol(std::shared_ptr<Sparse> ptr);
//	MatrixCol(const Sparse & src); 
	MatrixCol(std::unique_ptr<Symmetric> & ptr);
	virtual ~MatrixCol();
	
	inline size_type row_count() const override {return second_count();}					// number of rows
	inline size_type column_count() const override {return first_count();}				// number of cols
	Vector<Scalar> * row_vector(size_type ind) override;		// not implemented
	Vector<Scalar> * column_vector(size_type ind) override;	// unsafe to dealloc
	Vector<Scalar> * row_copy(size_type ind) const override;
	Vector<Scalar> * column_copy(size_type ind) const override;
	void print_matrix() const override;
	void print_elements(std::ostream & os) const override;							// trick for print matrix using streams + correction 1-based
	Scalar * item_add(size_type i,size_type j) override;
	const Scalar item(size_type i,size_type j) const override;
	void what() const override {std::cout<<"I'm a MatrixCol"<<std::endl;}
	};//finish class

#endif

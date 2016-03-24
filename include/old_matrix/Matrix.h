#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <memory>
#include "Vector.h"
#include "Scalar.h"
#include "Item.h"
#include "Sparse.h"
#include "Symmetric.h"

// #define SEPARATOR ','
// using size_type=const std::size_t;	// from Item.h

class Matrix{
	protected:
	Vector<Vector<Scalar>> mat;
	
	size_type first_count() const {return mat.size();}
	size_type second_count() const {return mat[0].size();}
	Vector<Scalar> * first_vec_vector(size_type ind);				//fix first index
	Vector<Scalar> * first_vec_copy(size_type ind) const;			//fix first index
	Vector<Scalar> * second_vec_copy(size_type ind) const;		//fix second index
	public:
	Matrix();
	Matrix(size_type n);
	Matrix(size_type a,size_type b);
	Matrix(size_type a,size_type b,const Scalar & val);

	Matrix(Matrix * ptr);
	Matrix(std::unique_ptr<Matrix> & ptr);								//pass by ref
//	Matrix(std::shared_ptr<Matrix> & ptr);

//	Matrix(Sparse * ptr);
	Matrix(std::shared_ptr<Sparse> ptr);
	Matrix(std::unique_ptr<Symmetric> & ptr);
	virtual ~Matrix();
	
	virtual size_type row_count() const = 0;
	virtual size_type column_count() const = 0;
	virtual Vector<Scalar> * row_vector(size_type ind) = 0;		// unsafe to dealloc
	virtual Vector<Scalar> * column_vector(size_type ind) = 0;	// unsafe to dealloc
	virtual Vector<Scalar> * row_copy(size_type ind) const = 0;
	virtual Vector<Scalar> * column_copy(size_type ind) const = 0;
	virtual void print_matrix() const = 0;
	virtual void print_elements(std::ostream & os) const = 0;	// trick for print matrix using streams
	virtual Scalar * item_add(size_type i,size_type j) = 0;
	virtual const Scalar item(size_type i,size_type j) const = 0;
	virtual void what() const = 0;
	void info() const;
	};//finish class

std::ostream & operator<<(std::ostream & os,const Matrix & m);

#endif

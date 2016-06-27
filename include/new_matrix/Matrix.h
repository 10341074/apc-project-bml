#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

#include "Color.h"
#include "ColumnIt.h"
// using Scalar = Color;
// using size_type = const std::size_t;
// const char Separator = ',';

class Matrix{
  protected:
    std::vector< Scalar > mat;
    std::size_t ext_count_ = 0;
    std::size_t inn_count_ = 0;
    
	public:
    Matrix();
    Matrix(size_type n);
    Matrix(size_type a, size_type b); // ext_count_(a), inn_count_(b)
    Matrix(size_type a, size_type b, const Scalar & val);

    virtual ~Matrix();

    const std::size_t ext_count() const { return ext_count_; }
    const std::size_t inn_count() const { return inn_count_; }
    const std::size_t size()      const { return mat.size(); }
    std::vector< Scalar >::const_iterator begin() const { return mat.begin(); }
    std::vector< Scalar >::iterator       begin()       { return mat.begin(); }
    std::vector< Scalar >::const_iterator end() const { return mat.end(); }
    
//    std::vector< Scalar >   inn_vec_ref(size_type ind);
    std::vector< Scalar > * inn_vec_copy(size_type ind) const;         // by copy
    std::vector< Scalar > * ext_vec_copy(size_type ind) const;         // by copy

    virtual const std::size_t rows_count() const = 0;
    virtual const std::size_t cols_count() const = 0;
//    virtual std::vector< Scalar > * row_vector(size_type index) = 0;     // unsafe to dealloc
//    virtual std::vector< Scalar > * col_vector(size_type index) = 0;     // unsafe to dealloc

//    virtual std::vector< Scalar > * row_copy(size_type ind) const = 0;
//    virtual std::vector< Scalar > * col_copy(size_type ind) const = 0;
    virtual void print_matrix() const = 0;
    virtual void print_elements(std::ostream & os) const = 0;	// trick for print matrix using streams

//    virtual       Scalar * item_add(size_type i,size_type j) = 0;
//    virtual const Scalar item(size_type i,size_type j) const = 0;
          Scalar & operator[](size_type k)       { if(k >= mat.size()) throw std::out_of_range("Matrix::operator[] : out of range"); return mat[k]; }
    const Scalar & operator[](size_type k) const { if(k >= mat.size()) throw std::out_of_range("Matrix::operator[] : out of range"); return mat[k]; }

    virtual       Scalar & operator()(size_type i,size_type j)       = 0;
    virtual const Scalar & operator()(size_type i,size_type j) const = 0;

    virtual void what() const = 0;

    void info() const;
    
    void load_same_order(const std::list< std::vector< Scalar > > & m_inp);
    void load_tran_order(const std::list< std::vector< Scalar > > & m_inp);
	};//finish class

std::ostream & operator<<(std::ostream & os, const Matrix & m);

#endif

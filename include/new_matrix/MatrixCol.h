#ifndef MATRIX_COL_H
#define MATRIX_COL_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Matrix.h"

class MatrixCol: public Matrix{
  public:
    MatrixCol();
    MatrixCol(size_type n);
    MatrixCol(size_type m, size_type n);
    MatrixCol(size_type m, size_type n, const Scalar & val);

    virtual ~MatrixCol();
	
    inline const std::size_t rows_count() const override { return inn_count_; }
    inline const std::size_t cols_count() const override { return ext_count_; }
//    std::vector< Scalar > * row_vector(size_type ind) override;   // unsafe to dealloc
//    std::vector< Scalar > * col_vector(size_type ind) override;   // not implemented
    std::vector< Scalar > * row_copy(size_type ind) const override;
    std::vector< Scalar > * col_copy(size_type ind) const override;
    void print_matrix() const override;
    void print_elements(std::ostream & os) const override; // trick for print matrix using streams + correction 1-based
          Scalar & operator()(size_type i, size_type j)       override;
    const Scalar & operator()(size_type i, size_type j) const override;
    void what() const override { std::cout << "I'm a MatrixCol" << std::endl; }
	};//finish class

#endif

#ifndef MATRIX_ROW_H
#define MATRIX_ROW_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Matrix.h"

class MatrixRow: public Matrix{
  public:
    MatrixRow();
    MatrixRow(size_type n);
    MatrixRow(size_type m, size_type n);
    MatrixRow(size_type m, size_type n, const Scalar & val);

    virtual ~MatrixRow();
	
    inline const std::size_t rows_count() const override { return ext_count_; }
    inline const std::size_t cols_count() const override { return inn_count_; }
//    std::vector< Scalar > * row_vector(size_type ind) override;   // unsafe to dealloc
//    std::vector< Scalar > * col_vector(size_type ind) override;   // not implemented
    std::vector< Scalar > * row_copy(size_type ind) const override;
    std::vector< Scalar > * col_copy(size_type ind) const override;
    void print_matrix() const override;
    void print_elements(std::ostream & os) const override; // trick for print matrix using streams
          Scalar & operator()(size_type i, size_type j)       override;
    const Scalar & operator()(size_type i, size_type j) const override;
    void what() const override { std::cout << "I'm a MatrixRow" << std::endl; }
};//finish class

#endif

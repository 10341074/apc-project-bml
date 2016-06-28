#ifndef CSC_H
#define CSC_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Matrix.h"

class CSC: public Matrix{
  private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector< std::size_t > J_; // notation with final total count (size + 1)
  public:
    CSC(std::size_t r, std::size_t c);
    CSC(std::size_t r, std::size_t c, size_type n);
    CSC(std::size_t r, std::size_t c, size_type n, const std::vector< std::size_t > & indices);
    CSC(std::size_t r, std::size_t c, size_type n, const std::vector< std::size_t > & indices, const Scalar & val);

    virtual ~CSC();
	
    inline const std::size_t rows_count() const override { return rows_; }
    inline const std::size_t cols_count() const override { return cols_; }
//    std::vector< Scalar > * row_vector(size_type ind) override;   // unsafe to dealloc
//    std::vector< Scalar > * col_vector(size_type ind) override;   // not implemented
//    std::vector< Scalar > * row_copy(size_type ind) const override {}
//    std::vector< Scalar > * col_copy(size_type ind) const override {}
    void print_matrix() const override;
    void print_elements(std::ostream & os) const override; // trick for print matrix using streams
    Scalar & operator()(size_type i, size_type j)       override;
    const Scalar & operator()(size_type i, size_type j) const override;
    void what() const override { std::cout << "I'm a CSC" << std::endl; }
};//finish class

#endif

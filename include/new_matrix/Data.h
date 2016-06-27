#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

#include "Color.h"
#include "Matrix.h"
#include "MatrixRow.h"
#include "MatrixCol.h"

struct Coordinates {
  std::size_t i_ = 0;
  std::size_t j_ = 0;
  Coordinates() {}
  Coordinates(const std::size_t & i, const std::size_t & j) : i_(i), j_(j) {}
};


enum MatrixType{None, Input, ByRows, ByCols, ByCSR, ByCSC};
// using OneColor = std::vector<std::size_t>;
using OneColor = std::vector< Coordinates >;
using MatrixInp = std::list< std::vector< Scalar > >;

class Data {
  private:
    MatrixType    t_;
    MatrixInp     * m_inp = nullptr;
    Matrix        * m_lin = nullptr;
/*
    Matrix        * m_row = nullptr;
    Matrix        * m_col = nullptr;
    MatrixType    type = None;
*/    
    OneColor      * white = nullptr;
    OneColor      * blue = nullptr;
    OneColor      * red = nullptr;
    
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::size_t white_count_ = 0;
    std::size_t blue_count_ = 0;
    std::size_t red_count_ = 0;
    
    void load_input(std::istream & is);
    void update_statistics();
    void load_matrix();
    void load_colors_byrows(const Matrix * ptr);
    void load_colors_bycols(const Matrix * ptr);
    void tok_push_back(const std::string & line);
  public:
    Data(MatrixType t);
    ~Data();
    
    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
    MatrixType type() const { return t_; }
    
    friend std::istream & operator>>(std::istream & is, Data & d);
    friend std::ostream & operator>>(std::ostream & os, Data & d);
    
    void print() const {if(m_lin!=nullptr) std::cout << * m_lin << std::endl; return;}
    std::vector< Scalar >::const_iterator begin() const { if(m_lin == nullptr) throw std::logic_error("Data::begin : nullptr pointer"); return m_lin->begin(); }
    std::vector< Scalar >::iterator       begin()       { if(m_lin == nullptr) throw std::logic_error("Data::begin : nullptr pointer"); return m_lin->begin(); }
          Scalar & operator[](size_type k)       { if(m_lin == nullptr)   throw std::logic_error("Data::begin : nullptr pointer");
                                                   if(k >= m_lin->size()) throw std::out_of_range("Matrix::operator[] : out of range");
                                                   return (* m_lin)[k]; }
    const Scalar & operator[](size_type k) const { if(m_lin == nullptr)   throw std::logic_error("Data::begin : nullptr pointer");
                                                   if(k >= m_lin->size()) throw std::out_of_range("Matrix::operator[] : out of range");
                                                   return (* m_lin)[k]; }
}; // finish class
#endif  

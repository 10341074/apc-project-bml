#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

#include "Template.h"
#include "Color.h"

#include "Matrix.h"
#include "MatrixRow.h"
#include "MatrixCol.h"
#include "CSR.h"
#include "CSC.h"

void load_same_order(const std::list< std::vector< Scalar > > & m_inp, std::vector< Scalar > & mat, std::size_t & ext_count, std::size_t & inn_count);
void load_tran_order(const std::list< std::vector< Scalar > > & m_inp, std::vector< Scalar > & mat, std::size_t & ext_count, std::size_t & inn_count);
/*
input
        const std::list< std::vector< Scalar > > & m_inp
output
        std::vector< Scalar > & mat
        std::size_t & ext_count
        std::size_t & inn_count
*/

enum MatrixType   {None, Input, ByRows, ByCols, ByCSR, ByCSC};
enum MoveType     {MoveColor, MoveWhite};
const char * const MatrixTypeStr [] = {"None", "Input", "ByRows", "ByCols", "ByCSR", "ByCSC"};
const char * const MoveTypeStr   [] = {"MoveColor", "MoveWhite" };

using MatrixInp = std::list< std::vector< Scalar > >;

class Data {
  private:
    MatrixType    t_;
    MatrixInp     * m_inp = nullptr;
    Matrix        * m_lin = nullptr;

    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::size_t white_count_ = 0;   // white+ last->white (no first)
    std::size_t blue_count_ = 0;    // white+ last->white (no first)
    std::size_t red_count_ = 0;     // white+ last->white (no first)
    
    void tok_push_back(const std::string & line);
  public:
    Data(MatrixType t);
    ~Data();

    void load_input(std::istream & is);
    void load_matrix();
    void load_matrix(MatrixType t);
    void build_comp(MatrixType t, std::size_t r, std::size_t c, const std::vector< std::size_t > & indices);

    std::size_t rows() const          { return rows_; }
    std::size_t cols() const          { return cols_; }
    std::size_t white_count() const   { return white_count_; }
    std::size_t blue_count() const    { return blue_count_; }
    std::size_t red_count() const     { return red_count_; }
    MatrixType type() const           { return t_; }
    
          std::vector< Scalar > & matrix()        { if(m_lin == nullptr) throw std::logic_error("Data::matrix : nullptr pointer"); return m_lin->matrix(); } 
    const std::vector< Scalar > & matrix() const  { if(m_lin == nullptr) throw std::logic_error("Data::matrix : nullptr pointer"); return m_lin->matrix(); }
    Matrix *  & matrix_pointer()        { if(m_lin == nullptr) throw std::logic_error("Data::matrix_pointer : nullptr pointer"); return m_lin; }
    Matrix *    matrix_pointer() const  { if(m_lin == nullptr) throw std::logic_error("Data::matrix_pointer : nullptr pointer"); return m_lin; }

    
    friend std::istream & operator>>(std::istream & is, Data & d); // load_input() + load_matrix()
    friend std::ostream & operator<<(std::ostream & os, Data & d);
    inline void print() const;
    
    inline std::vector< Scalar >::iterator       begin();
    inline std::vector< Scalar >::const_iterator begin() const;
    inline       Scalar & operator[](size_type k);
    inline const Scalar & operator[](size_type k) const;
}; // finish class

void Data::print() const {
  if(m_lin!=nullptr)
    std::cout << * m_lin << std::endl;
  return;
}

std::vector< Scalar >::iterator Data::begin() {
  if(m_lin == nullptr) 
    throw std::logic_error("Data::begin : nullptr pointer");
  return m_lin->begin();
}
std::vector< Scalar >::const_iterator Data::begin() const {
  if(m_lin == nullptr) 
    throw std::logic_error("Data::begin : nullptr pointer");
  return m_lin->begin();
}
Scalar & Data::operator[](size_type k) {
  if(m_lin == nullptr)
    throw std::logic_error("Data::operator[] : nullptr pointer");
  if(k >= m_lin->size())
    throw std::out_of_range("Matrix::operator[] : out of range");
  return (* m_lin)[k];
}
const Scalar & Data::operator[](size_type k) const {
  if(m_lin == nullptr)
    throw std::logic_error("Data::operator[] : nullptr pointer");
  if(k >= m_lin->size())
    throw std::out_of_range("Matrix::operator[] : out of range");
  return (* m_lin)[k]; 
}
#endif

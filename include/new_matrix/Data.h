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
struct Coordinates {
  std::size_t i_ = 0;
  std::size_t j_ = 0;
  Coordinates() {}
  Coordinates(const std::size_t & i, const std::size_t & j) : i_(i), j_(j) {}
  friend std::ostream & operator<<(std::ostream & os, const Coordinates & c) { os << "(" << c.i_ << ", " << c.j_ << ")"; return os; }
};

enum MatrixType{None, Input, ByRows, ByCols, ByCSR, ByCSC};
enum MoveType{MoveColor, MoveWhite};
enum MoveTypeDirection{Horizontal, Vertical};
// using OneColor = std::vector<std::size_t>;
using OneColor = std::vector< Coordinates >;
using MatrixInp = std::list< std::vector< Scalar > >;

struct ThreeColor {
  OneColor white;
  OneColor blue;
  OneColor red;
};

struct DataColor {
  OneColor                      inside;
  std::size_t                   first_ind = 0;
  std::size_t                   last_ind = 0;
  std::vector< std::size_t >    first;
  std::vector< std::size_t >    last;
  std::vector< std::size_t >    first_new;
  std::vector< std::size_t >    last_new;
  DataColor(std::size_t ext_count, std::size_t inn_count) {
    inside.reserve( (ext_count - 2) * inn_count );
    first.reserve( inn_count );
    last.reserve( inn_count );
    first_new.reserve( inn_count );
    last_new.reserve( inn_count );
  }
};
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
    
    ThreeColor    * first = nullptr;
    ThreeColor    * last = nullptr;

    DataColor     * data_white = nullptr;
    DataColor     * data_blue = nullptr;
    DataColor     * data_red = nullptr;
    
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::size_t white_count_ = 0;   // white+ last->white (no first)
    std::size_t blue_count_ = 0;    // white+ last->white (no first)
    std::size_t red_count_ = 0;     // white+ last->white (no first)
    
    void load_input(std::istream & is);
    void update_statistics();
    void load_matrix();
    void load_colors_byrows(const Matrix * ptr);
    void load_colors_bycols(const Matrix * ptr);
    void load_colors_byCSR(const Matrix * ptr, const std::vector< std::size_t > & indices);
    void load_colors_byCSC(const Matrix * ptr, const std::vector< std::size_t > & indices);
    void load_moving_colors_byCSR(const Matrix * ptr, const std::vector< std::size_t > & indices);
    void load_moving_colors_byCSC(const Matrix * ptr, const std::vector< std::size_t > & indices);
    void tok_push_back(const std::string & line);
  public:
    Data(MatrixType t);
    ~Data();
    void build_full(MatrixType t, std::size_t m, std::size_t n);
    void build_comp(MatrixType t, std::size_t r, std::size_t c, const std::vector< std::size_t > & indices);
    void load_colors_comp(const std::vector< std::size_t > & indices);
    void load_moving_colors_comp(const std::vector< std::size_t > & indices);
    void unload_moving_colors_comp(MoveType move_type);

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
    std::size_t white_count() const { return white_count_; }
    std::size_t blue_count() const { return blue_count_; }
    std::size_t red_count() const { return red_count_; }
    MatrixType type() const { return t_; }
    
    friend std::istream & operator>>(std::istream & is, Data & d);
    friend std::ostream & operator>>(std::ostream & os, Data & d);
    
    void print() const {if(m_lin!=nullptr) std::cout << * m_lin << std::endl; return;}
    std::vector< Scalar >::const_iterator begin() const { if(m_lin == nullptr) throw std::logic_error("Data::begin : nullptr pointer"); return m_lin->begin(); }
    std::vector< Scalar >::iterator       begin()       { if(m_lin == nullptr) throw std::logic_error("Data::begin : nullptr pointer"); return m_lin->begin(); }
          Scalar & operator[](size_type k)       { if(m_lin == nullptr)   throw std::logic_error("Data::operator[] : nullptr pointer");
                                                   if(k >= m_lin->size()) throw std::out_of_range("Matrix::operator[] : out of range");
                                                   return (* m_lin)[k]; }
    const Scalar & operator[](size_type k) const { if(m_lin == nullptr)   throw std::logic_error("Data::operator[] : nullptr pointer");
                                                   if(k >= m_lin->size()) throw std::out_of_range("Matrix::operator[] : out of range");
                                                   return (* m_lin)[k]; }
   friend class Move;
}; // finish class
#endif  

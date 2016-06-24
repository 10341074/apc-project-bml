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

enum MatrixType{ByRows, ByCols, None};
using OneColor = std::vector<std::size_t>;
using MatrixInp = std::list< std::vector< Scalar > >;

class Data {
  private:
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
    void load_colors();
    void tok_push_back(const std::string & line);
  public:
    Data();
    ~Data();
    friend std::istream & operator>>(std::istream & is, Data & d);
    friend std::ostream & operator>>(std::ostream & os, Data & d);
    
}; // finish class
#endif

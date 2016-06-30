#ifndef MOVE_H
#define MOVE_H
#include "Data.h"
#include "DataLocal.h"
void move_parall(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);
void move_across(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);

class Move {
        //matrix_type
    // pointer to function
    void (* move)(void);
    MatrixType  matrix_type_;
    MoveType    move_type_;

    // move_type
    DataColor * blue = nullptr;
    DataColor * red = nullptr;
    std::vector< std::size_t > * blue_add = nullptr;
    std::vector< std::size_t > * blue_rem = nullptr;
    std::vector< std::size_t > * red_add = nullptr;
    std::vector< std::size_t > * red_rem = nullptr;
    int increment = 0;
    
  public:
    Move() {}
    Move(MatrixType matrix_type, MoveType move_type, MoveTypeDirection blue_direction, MoveTypeDirection red_direction, Data & data_local);
      void par() {}
  void ort() {}

  
};

class MoveWhiteClass: public Move {
  public:
  void par() { std::cout << "son\n";}
  void ort() {}
};
#endif

#ifndef MOVE_H
#define MOVE_H
#include "Data.h"
#include "DataLocal.h"
void move_parall(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);
void move_across(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);

void move_parall_bi(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);
void move_across_bi(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);

struct Parameters {
  DataLocalColor  * data_color_ = nullptr;
  Scalar          first_color_;
  Scalar          second_color_;
  int             increment_;
  std::vector< std::size_t > *    border_move_p_ = nullptr;
  std::size_t                     border_no_move_;
  Parameters() {}
  Parameters(DataLocalColor * data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > * border_move_p, std::size_t border_no_move) : data_color_(data_color), first_color_(first_color), second_color_(second_color), increment_(increment), border_move_p_(border_move_p), border_no_move_(border_no_move) {}
//  Parameters(const DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > * border_move_p, std::size_t border_no_move) : data_color_(data_color), first_color_(first_color), second_color_(second_color), increment_(increment), border_move_p_(border_move_p), border_no_move_(border_no_move) {}
//  void build(const DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > * border_move_p, std::size_t border_no_move) { data_color_= data_color; first_color_ = first_color; second_color_ = second_color; increment_  = increment; border_move_p_ = border_move_p; border_no_move_ = border_no_move;}
};
class Move {
 //   std::vector< Scalar > & mat;
    void (* move_active)(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);
    void (* move_inactive)(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);

    MatrixType  matrix_type_;
    MoveType    move_type_;

    // move_type
    Parameters blue_;
    Parameters red_;
    std::vector< std::size_t > out_border;
    std::vector< std::size_t > on_border;
    
//    Parameters * current = & blue_;
//    Parameters * pausing = & red_
  public:
    Move() {}
    Move(MatrixType matrix_type, MoveType move_type, Data & data_local);
    Move(MatrixType matrix_type, MoveType move_type, DataLocalColor & data_white, DataLocalColor & data_blue, DataLocalColor & data_red);
//    void call_to_move(std::vector< Scalar > & mat) { move(mat, * (current->data_color_), current->second_color_, current->increment_, * (current->border_move_p_), current->border_no_move_, out_border, on_border); return;} // if no nullptr, or check 1 for all
    friend void odd_move(std::vector< Scalar > & mat, Move & m);
    friend void even_move(std::vector< Scalar > & mat, Move & m);

};

void odd_move(std::vector< Scalar > & mat, Move & m);
void even_move(std::vector< Scalar > & mat, Move & m);





/*
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
*/
#endif

#ifndef MOVE_H
#define MOVE_H
#include "Data.h"
#include "DataLocal.h"
void swap(Scalar & s1, Scalar & s2);
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
};

class Move {
    void (* move_active)(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);
    void (* move_inactive)(std::vector< Scalar > & mat, DataLocalColor & data_color, Scalar first_color, Scalar second_color, int increment, std::vector< std::size_t > & border_move, std::size_t border_no_move, std::vector< std::size_t > & out_border, std::vector< std::size_t > & on_border);

    MatrixType  matrix_type_;
    MoveType    move_type_;

    // move_type
    Parameters blue_;
    Parameters red_;
    std::vector< std::size_t > out_border;
    std::vector< std::size_t > on_border;
    
  public:
    Move() {}
    Move(MatrixType matrix_type, MoveType move_type, DataLocalColor & data_white, DataLocalColor & data_blue, DataLocalColor & data_red);
    friend void odd_move(std::vector< Scalar > & mat, Move & m);
    friend void even_move(std::vector< Scalar > & mat, Move & m);

};

void odd_move(std::vector< Scalar > & mat, Move & m);
void even_move(std::vector< Scalar > & mat, Move & m);

#endif

#ifndef MOVE_SINGLE_H
#define MOVE_SINGLE_H
#include "Data.h"
#include "DataLocal.h"
void swap(Scalar & s1, Scalar & s2);
void move_parall(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment);
void move_across(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment);

struct ParametersSingle {
  DataSingleColor  * data_color_ = nullptr;
  Scalar          first_color_;
  Scalar          second_color_;
  int             increment_;
  ParametersSingle() {}
  ParametersSingle(DataSingleColor * data_color, Scalar first_color, Scalar second_color, int increment) : data_color_(data_color), first_color_(first_color), second_color_(second_color), increment_(increment) {}
};

class MoveSingle {
    void (* move_active)(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment);
    void (* move_inactive)(std::vector< Scalar > & mat, DataSingleColor & data_color, Scalar first_color, Scalar second_color, int increment);

    MatrixType  matrix_type_;
    MoveType    move_type_;

    // move_type
    ParametersSingle blue_;
    ParametersSingle red_;

  public:
    MoveSingle() {}
    MoveSingle(MatrixType matrix_type, MoveType move_type, DataSingleColor & data_white, DataSingleColor & data_blue, DataSingleColor & data_red);

    friend void odd_move(std::vector< Scalar > & mat, MoveSingle & m);
    friend void even_move(std::vector< Scalar > & mat, MoveSingle & m);

};

void odd_move(std::vector< Scalar > & mat, MoveSingle & m);
void even_move(std::vector< Scalar > & mat, MoveSingle & m);

#endif

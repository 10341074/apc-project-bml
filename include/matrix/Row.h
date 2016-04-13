#ifndef ROW_H
#define ROW_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <list>

#include "Color.h"
#include "Car.h"

enum MatrixType{ByRows, ByCols, None};

using Row = std::vector<Color>;

using RowS = std::list<Car>;

std::ostream & operator<<(std::ostream & os, const Row & v);

#endif

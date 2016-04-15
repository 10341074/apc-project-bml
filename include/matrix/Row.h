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

class ColorP;

std::ostream & operator<<(std::ostream & os, const Row & v);
std::ostream & operator<<(std::ostream & os, const std::list<std::list<Car>> & v);
std::ostream & operator<<(std::ostream & os, const std::list<Car> & v);
std::ostream & operator<<(std::ostream & os, const std::list<std::list<Color>> & v);


#endif

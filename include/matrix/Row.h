#ifndef ROW_H
#define ROW_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Color.h"

using Row = std::vector<Color>;

std::ostream & operator<<(std::ostream & os, const Row & v);

#endif

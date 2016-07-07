#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include <Color.h>

std::vector<Color> tokenize(const std::string & line);
void tokenize_first_line(const std::string & line,std::vector<std::size_t> & times);

#endif

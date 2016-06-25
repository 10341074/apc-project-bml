#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include <Color.h>

std::vector<Color> tokenize(std::string & line);
void tokenize(std::string & line, std::vector<Color> & v);
void tokenize_first_line(std::string & line,std::vector<std::size_t> & times);

#endif

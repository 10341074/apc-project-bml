#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
/*
#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "Col.h"

#include "Traffic.h"
#include "Tokenize.h"

#include "CellTraffic.h"
*/
#include "Tokenize.h"
#include "Template.h"

#include "Matrix.h"
#include "MatrixRow.h"
#include "MatrixCol.h"

int main(int argc, char ** argv){
	std::string if_string(argv[1]);
	std::ifstream if_stream(if_string);
	
	std::string first_line;
	std::vector<std::size_t> times(1, 0);
	if(std::getline(if_stream, first_line))
		tokenize_first_line(first_line,times);
	
	std::cout << times ;
	
  return 0;
}

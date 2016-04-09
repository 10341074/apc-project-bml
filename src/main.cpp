#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <fstream>
#include <string>


#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "Col.h"

#include "Traffic.h"
#include "Tokenize.h"

int main(int argc, char ** argv){
	std::string if_string(argv[1]);
	std::ifstream if_stream(if_string);
	
	std::string first_line;
	std::getline(if_stream, first_line);
	std::vector<std::size_t> v;
	tokenize_first_line(first_line,v);
	
	std::cout << v ;
	
//	std::unique_ptr< std::vector<std::vector<Color>> > p(new std::vector<std::vector<Color>>);
//	VecVector * p = new VecVector(ByRows);
	Traffic traffic(ByCols);
	
	if_stream >> traffic;
	if_stream.close();
	
	traffic.print();
	
	std::ofstream of_stream("output.csv");
	of_stream << traffic;
	of_stream.close();
	
//	Row r;
//	std::cout << &r <<std::endl;
	return 0;
}

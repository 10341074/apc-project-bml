#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>


#include "Color.h"
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
	
	Traffic traffic;
	if_stream >> traffic;
	if_stream.close();
	
	traffic.print();
	std::ofstream of_stream("output.csv");
	of_stream << traffic;
	of_stream.close();
	return 0;
}

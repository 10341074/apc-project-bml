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
#include "RowsVector.h"

#include "Traffic.h"
#include "Tokenize.h"

DynRow f(){
	DynRow dr;
	return dr;
}

int main(int argc, char ** argv){
	std::string if_string(argv[1]);
	std::ifstream if_stream(if_string);
	
	std::string first_line;
	std::getline(if_stream, first_line);
	std::vector<std::size_t> v;
	tokenize_first_line(first_line,v);
	
	std::cout << v ;
	
	std::unique_ptr< std::vector<std::vector<Color>> > p(new std::vector<std::vector<Color>>);
	Traffic traffic(p);
	if_stream >> traffic;
	if_stream.close();
	
	traffic.print();
	
	std::ofstream of_stream("output.csv");
	of_stream << traffic;
	of_stream.close();
	
	Row r;
	std::cout << &r <<std::endl;
	
	Row * pp = nullptr;
	delete pp;
	
	Row row(10,Blue);
	std::cout << row;
	DynRow dr;
	RowsVector rvec;
	rvec.push_back(dr);
	rvec.push_back(f());
	
	return 0;
}

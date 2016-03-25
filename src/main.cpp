#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Color.h"
#include "Traffic.h"
#include "Tokenize.h"
int main(int argc, char ** argv){
	std::string s("12");
	std::vector<std::size_t> v;
	tokenize_first_line(s,v);
	
	std::cout << v ;
	return 0;
}

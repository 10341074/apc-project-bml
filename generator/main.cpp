#include <iostream>
#include <cstdlib>
#include <fstream>

#define SEPARATOR ','

int classify(std::size_t n, std::size_t rho){
	if(n>=rho) return 0;
	if(n>=rho/2) return 1;
	return 2;
}

int main(int argc, char ** argv){
	std::size_t rows=std::stoul(argv[1]);
	std::size_t cols=std::stoul(argv[2]);
	std::size_t rho=std::stoul(argv[3]);
	std::string name(argv[4]); 
	
	std::ofstream of(name);
	int num;
	for(std::size_t i=0; i<rows; ++i){
		for(std::size_t j=0; j<cols; ++j){
			num=rand() % 100;
			of<<classify(num,rho);
			if(j<cols-1) of<<SEPARATOR;
			
		}
	of<<'\n';
	}
	of.close();
	return 0;
}

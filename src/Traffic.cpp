#include <iostream>
#include <stdexcept>
#include <vector>

#include "Traffic.h"
#include "Tokenize.h"

#define START '0'
Traffic::Traffic() : 
	pmat(nullptr) {
}
Traffic::Traffic(RowsVector * p) :
	pmat(p) {
}
Traffic::~Traffic() {
	if(pmat != nullptr)
		delete pmat;
	pmat = nullptr;
}
// void Traffic::push_back(std::vector<Color> & v){
//	pmat->push_back(v);
//	return;
// }
void Traffic::tok_push_back(const std::string & line){
	std::size_t len=line.length();
	Row * row = new Row((len+1)/2);
	std::vector<Color> & v = *row;
//	std::vector<Color> v((len+1)/2);
	const char * p2one = &line[0];
	
	for(std::vector<Color>::iterator it=v.begin(); it!=v.end(); ++it){
			*it = static_cast<Color>(*p2one -START);
//			std::cout<<"char= "<<(*p2one -START);
		p2one+=2;
//     	std::string n=std::string(1,line[2*index]);
//     	v[index]=(Color)std::stoul(n);
	}
//	std::cout << v;
	this->pmat->push_back(row);
//	this->pmat->push_back(v);
	return;
}
void Traffic::print() const {
//	for(std::vector<std::vector<Color>>::const_iterator it = this->pmat->begin(); it != this->pmat->end(); ++it){
//		std::cout << *it;
//	}
	std::cout << * pmat;
	return;
}
std::istream & operator>>(std::istream & is, Traffic & traffic){
	std::string line;
	while(getline(is,line)){
		traffic.tok_push_back(line);
	}
	return is;
}
std::ostream & operator<<(std::ostream & os, const Traffic & traffic){
//	for(std::vector<std::vector<Color>>::const_iterator it = traffic.pmat->begin(); it != traffic.pmat->end(); ++it){
//		os << *it;
//	}
	os << * traffic.pmat;
	return os;
}

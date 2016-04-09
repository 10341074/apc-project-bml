#include <iostream>
#include <stdexcept>
#include <vector>

#include "Traffic.h"
#include "Tokenize.h"

#define START '0'
Traffic::Traffic(TypeMatrix t) : 
	pmat(nullptr) {
		if(t == ByRows)
			pmat = new RowsVector;
		else if(t == ByCols)
			pmat = new ColsVector;
}
Traffic::~Traffic() {
	if(pmat != nullptr)
		delete pmat;
	pmat = nullptr;
}
void Traffic::tok_push_back(const std::string & line){
	std::size_t len=line.length();
	std::unique_ptr<Row> row(new Row((len+1)/2));
	std::vector<Color> & v = *row;
	const char * p2one = &line[0];
	
	for(std::vector<Color>::iterator it=v.begin(); it!=v.end(); ++it){
			*it = static_cast<Color>(*p2one -START);
		p2one+=2;
	}
	if(pmat == nullptr)
		throw std::logic_error("Traffic::tok_push_back null pmat");
	this->pmat->push_back( std::unique_ptr<Row>(row.release()) );
	return;
}
void Traffic::print() const {
	if(pmat != nullptr)
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
	if(traffic.pmat != nullptr)
		os << * traffic.pmat;
	return os;
}
// void Traffic::move_row(size_type row, Color cl){
//	std::cout<<mat.size()<<std::endl;
//	if(row>=mat.size()){ throw std::out_of_range("Error: item outside matrix");}
// 
//	auto it_end = mat[row].end();
//	std::vector<Color>::iterator it_old = (mat[row]).begin();
//	Color first_cl = *it_old;
//	
//	for(std::vector<Color>::iterator it = mat[row].begin()+1; it<it_end; ++it){
//		if(((*it) == White) && ((*it_old) == cl)){
//			*it = *it_old;
//			*it_old = White;
//			++it;
//			++it_old;
//		}
//	++it_old;
//	}
//	if((it_old<it_end) && (first_cl == White) && ((*it_old) == cl)){
//		*mat[row].begin() = *it_old;
//		*it_old = White;
//		}
//	return;
// }


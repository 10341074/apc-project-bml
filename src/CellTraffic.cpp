#include <iostream>
#include <stdexcept>
#include <vector>

#include "Traffic.h"
#include "Tokenize.h"
#include "CellTraffic.h"

#define START '0'
CellTraffic::CellTraffic() :
	data(), rmat(new CellMatrixRows(&data)), cmat(new CellMatrixCols(&data)) {
}
CellTraffic::~CellTraffic() {
	if(rmat != nullptr) {
		delete rmat; rmat = nullptr;
	}
	if(cmat != nullptr) {
		delete cmat; cmat = nullptr;
	}
}

std::istream & operator>>(std::istream & is, CellTraffic & traffic){
	std::string line;
	std::size_t rowsCount = 0;
	traffic.type = ByRows;
	while(getline(is,line)){
		traffic.tok_push_back(line,rowsCount);
		++rowsCount;
	}
//	std::cout << "Read from file " << traffic.type <<std::endl;
//	std::cout << * traffic.rmat;

//	traffic.rmat->border_columns();
	traffic.rmat->update_data();
	return is;
}
void CellTraffic::tok_push_back(const std::string & line, const std::size_t & rowsCount) {
	const std::size_t len=line.length();
	const std::size_t colsTot = (len + 1)/2; 
	CarsData row;
	row.push_back(CarsDataIn(colsTot));
	const char * p2one = &line[0];
//	std::size_t colsCount = 0;
	
	CarsDataIn & rowv =  * row.begin();
//	for( ; colsCount < colsTot; ++colsCount){
	for(CarsDataIn::iterator it = rowv.begin() ; it < rowv.end(); ++it){
		Color c = static_cast<Color>(*p2one -START);
//		row->push_back(c);
		* it = c;
		p2one+=2;
	}
//	if(rmat == nullptr)
//		throw std::logic_error("Traffic::tok_push_back null pmat");
//	if(type == ByRows)
	if(rmat != nullptr)
		this->rmat->push_back(row,colsTot);
	return;
}
//*/
std::ostream & operator<<(std::ostream & os, const CellTraffic & traffic){
	if((traffic.type == ByRows) && (traffic.rmat != nullptr)) {
		os << * traffic.rmat;
	} else if ((traffic.type == ByCols) && (traffic.cmat != nullptr)) {
		os << * traffic.cmat;
	}
	return os;
}
void CellTraffic::print() const {
	data.print();
	return;
}
void CellTraffic::move_forward(const MatrixType & t, const Color & cl) {
	if((t == ByRows) && (rmat != nullptr)) {
		rmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *rmat;
	} else if((t == ByCols) && (cmat != nullptr)) {
		cmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *cmat;
	}
	return;
}
void CellTraffic::move_white(const MatrixType & t, const Color & cl) {
	if((t == ByRows) && (rmat != nullptr)) {
		rmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *rmat;
	} else if((t == ByCols) && (cmat != nullptr)) {
		cmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *cmat;
	}
	return;
}


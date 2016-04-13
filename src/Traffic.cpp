#include <iostream>
#include <stdexcept>
#include <vector>

#include "Traffic.h"
#include "Tokenize.h"

#define START '0'
Traffic::Traffic(MatrixType t) : 
	pmat(nullptr) {
		type = t;
		if(t == ByRows)
			pmat = new RowsVector;
		else if(t == ByCols)
			pmat = new ColsVector;
}
Traffic::Traffic(MatrixType t, size_type rows, size_type cols) :
	pmat(nullptr) {
		type = t;
		if(t == ByRows)
			pmat = new RowsVector(rows,cols);
		else if(t == ByCols)
			pmat = new ColsVector(cols,rows);
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
Row::const_iterator Traffic::get_row_it(size_type index) const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::get_iterator of empty pmat");
	return pmat->get_it_from(index);
}
DrVec::const_iterator Traffic::get_vec_it_begin() const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::get_iterator of empty pmat");
	return pmat->begin();
}
DrVec::const_iterator Traffic::get_vec_it_end() const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::get_iterator of empty pmat");
	return pmat->end();
}
Row::size_type Traffic::get_cMaxIndex() const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::get_cMaxIndex of empty pmat");
	return pmat->get_cMaxIndex();
}
size_type Traffic::rows() const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::rows of empty pmat");
	return pmat->rows();
}
size_type Traffic::cols() const {
	if(pmat == nullptr)
		throw std::logic_error("Traffic::get_cMaxIndex of empty pmat");
	return pmat->cols();
}
void Traffic::move_from(const Traffic & from, Color cl){
	DrVec::const_iterator ext_it = from.get_vec_it_begin();
	DrVec::const_iterator ext_it_end = from.get_vec_it_end();
	if(pmat == nullptr)
		throw std::logic_error("Traffic::move of empty pmat");
	if(from.get_cMaxIndex() != pmat->get_length())
		throw std::logic_error("Traffic::move with to matrices with not coincident lengths");
	pmat->column_start();
	ColumnVec::iterator it_to_begin = pmat->column_begin();
	ColumnVec::iterator it_to_end = pmat->column_end();
	
	for(; ext_it != ext_it_end; ++ext_it) { // loop on all lines
		Row::const_iterator it_from_old = ext_it->begin();
		Row::const_iterator it_from = ext_it->begin() + 1;
		Row::const_iterator it_from_end = ext_it->end();
		ColumnVec::iterator it_to_old = it_to_begin;
		ColumnVec::iterator it_to = it_to_begin + 1;
		
		Color first_cl = *it_from_old;
		* it_to_old = * it_from_old; // correct if not moved neither with first neither with last
		for(; it_from < it_from_end; ++it_from){
			if(((*it_from) == White) && ((*it_from_old) == cl)){
				* it_to = * it_from_old;
				* it_to_old = White;
				++it_to;
				++it_to_old;
				++it_from;
				++it_from_old;
			} else {
				* it_to_old = * it_from_old;
			}
		++it_to;
		++it_to_old;
		++it_from_old;
		}
		if((it_from_old<it_from_end) && (first_cl == White) && ((*it_from_old) == cl)){
			* it_to_begin = cl;
			* it_to_old = White;
			}
//		for(auto it=it_to_begin; it<it_to_end; ++it){
//			std::cout<<*it<<',';
//		}
//	std::cout<<std::endl;
	pmat->column_shift();
	}
	return;
}
void Traffic::transpose_from(const Traffic & from) {
	DrVec::const_iterator ext_it = from.get_vec_it_begin();
	DrVec::const_iterator ext_it_end = from.get_vec_it_end();
	delete pmat;
	if(type == ByRows)
		pmat = new RowsVector(from.rows(), from.cols());
	else if(type == ByCols)
		pmat = new ColsVector(from.cols(), from.rows());
	if(pmat == nullptr)
		throw std::logic_error("Traffic::transpose of empty pmat");
	if(from.get_cMaxIndex() != pmat->get_length())
		throw std::logic_error("Traffic::transpose with to matrices with not coincident lengths");
	pmat->column_start();
	ColumnVec::iterator it_to_begin = pmat->column_begin();
	ColumnVec::iterator it_to_end = pmat->column_end();
	
	for(; ext_it != ext_it_end; ++ext_it) { // loop on all lines
		Row::const_iterator it_from = ext_it->begin();
		Row::const_iterator it_from_end = ext_it->end();
		ColumnVec::iterator it_to = it_to_begin;
		
		for(; it_from < it_from_end; ++it_from){
			* it_to = * it_from;
		++it_to;
		}
	pmat->column_shift();
	}
	return;
}

TrafficS::TrafficS(MatrixType t) :
	type(t) {
	if(type == ByRows) {
		rmat = new RowsVectorS;
	} else if(type == ByCols) {
		cmat = new ColsVectorS;
	}
}
TrafficS::~TrafficS() {
	if(rmat != nullptr) {
		delete rmat; rmat = nullptr;
	}
	if(cmat != nullptr) {
		delete cmat; cmat = nullptr;
	}
}
std::istream & operator>>(std::istream & is, TrafficS & traffic){
	std::string line;
	std::size_t rowsCount = 0;
	while(getline(is,line)){
		traffic.tok_push_back(line,rowsCount);
		++rowsCount;
	}
	return is;
}
void TrafficS::tok_push_back(const std::string & line, const std::size_t & rowsCount) {
	const std::size_t len=line.length();
	const std::size_t colsTot = (len + 1)/2; 
	std::list<Car> row;
	const char * p2one = &line[0];
	std::size_t colsCount = 0;
	
	for( ; colsCount < colsTot; ++colsCount){
			Color c = static_cast<Color>(*p2one -START);
			if(c != White) {
				row.push_back(Car(rowsCount, colsCount, c));
			}
		p2one+=2;
	}
//	if(rmat == nullptr)
//		throw std::logic_error("Traffic::tok_push_back null pmat");
	if(type == ByRows)
		this->rmat->push_back(row,colsTot);
	return;
}
std::ostream & operator<<(std::ostream & os, const TrafficS & traffic){
	if(traffic.rmat != nullptr) {
		os << * traffic.rmat;
	}
	return os;
}


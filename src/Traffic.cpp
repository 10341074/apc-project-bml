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
Traffic::Traffic(TypeMatrix t, size_type rows, size_type cols) :
	pmat(nullptr) {
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
void Traffic::move_from(const Traffic & from, Color cl){
	DrVec::const_iterator ext_it = from.get_vec_it_begin();
	DrVec::const_iterator ext_it_end = from.get_vec_it_end();
	
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

		for(; it_from < it_from_end; ++it_from){
			if(((*it_from) == White) && ((*it_from_old) == cl)){
				* it_to = * it_from_old;
				* it_to_old = White;
				++it_to;
				++it_to_old;
				++it_from;
				++it_from_old;
			} else {
				* it_to = * it_from;
			}
		++it_to;
		++it_to_old;
		++it_from_old;
		}
		if((it_from_old<it_from_end) && (first_cl == White) && ((*it_from_old) == cl)){
			* it_to_begin = cl;
			* it_to_old = White;
			}
		else
			* it_to_begin = first_cl;
//	for(auto it=it_to_begin; it<it_to_end; ++it){
//		std::cout<<*it<<',';
//	}
//	std::cout<<std::endl;
	pmat->column_shift();
	}
	return;
}

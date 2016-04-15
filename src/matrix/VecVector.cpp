#include "VecVector.h"
VecVector::VecVector(DataD::size_type rows, Row::size_type cols) :
	vec(rows,DynRow(cols)), cVec(rows) {
	lin_size = cols;
	lin_ind = 0;
	this->column_start();
}
bool VecVector::empty() const {
	return vec.empty();
}
DataD::const_iterator VecVector::begin() const {
	return vec.begin();
}
DataD::const_iterator VecVector::end() const {
	return vec.end();
}
ColumnVec::iterator VecVector::column_begin() {
	return cVec.begin();
}
ColumnVec::iterator VecVector::column_end() {
	return cVec.end();
}

// void VecVector::push_back(const DynRow & dr) {
//	vec.push_back(dr);
//	return;
// }
// void VecVector::push_back(DynRow && dr) {
//	vec.push_back(dr);
//	return;
// }
// void VecVector::push_back(Row * r){
//	if(r == nullptr)
//		throw std::logic_error("VecVector::push_back with Row * equal to nullptr");
//	if(vec.empty())
//		lin_size = r->size();
//	else if(lin_size != r->size())
//		throw std::runtime_error("VecVector::push_back row with different length");
//	
//	cVec.push_back(r->begin());
//	vec.push_back(r);
//	lin_ind = 0;
// return;
// }
void VecVector::push_back(std::unique_ptr<Row> r){
	if(r == nullptr)
		throw std::logic_error("VecVector::push_back with unique_ptr<Row> equal to nullptr");
	if(vec.empty())
		lin_size = r->size();
	else if(lin_size != r->size())
		throw std::runtime_error("VecVector::push_back row with different length");

	cVec.push_back(r->begin());
	vec.push_back( std::unique_ptr<Row>(r.release()) );
	lin_ind = 0;
	this->update_counts();
	return;
}
void VecVector::column_start() {
	if(vec.empty())
		throw std::logic_error("VecVector::column_start() with empty vectors");
	if(vec.size() != cVec.size())
		throw std::logic_error("VecVector::column_start() cVec and vec different sizes");
	DataD::iterator dr_it = vec.begin();
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		* it = dr_it->begin();
		++ dr_it;
	}
	return;
}
void VecVector::column_shift() {
	if(vec.empty())
		throw std::logic_error("VecVector::column_start() with empty vectors");
	if(lin_ind >= lin_size)
		throw std::out_of_range("VecVector::column_shift out of range");
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		++ (* it);
	}
	return;
}
Row::const_iterator VecVector::get_it_from(size_type index) const {
	return vec[index].begin();
}
std::ostream & operator<<(std::ostream & os, VecVector & vecVec) {
	vecVec.print(os);
	return os;
}
//////////////////////////////////////////////////////////////////////////////////////
RowsVector::RowsVector(DataD::size_type rows, Row::size_type cols) : 
	VecVector(rows,cols) {
	rowsCount = rows;
	colsCount = cols;
}
std::ostream & operator<<(std::ostream & os,RowsVector & rowsVec) {
	rowsVec.print(os);
	return os;
}
void RowsVector::print(std::ostream & os) {
	for(std::vector<DynRow>::const_iterator it = this->vec.begin(); it != this->vec.end(); ++it) {
		os << * it->get_row_pointer();
	}
	return;
}
void RowsVector::update_counts() {
	++rowsCount;
	colsCount = lin_size;
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
ColsVector::ColsVector(DataD::size_type cols, Row::size_type rows) :
	VecVector(cols,rows) {
	rowsCount = rows;
	colsCount = cols;
}
std::ostream & operator<<(std::ostream & os,ColsVector & colsVec) {
	colsVec.print(os);
	return os;
}
void ColsVector::print(std::ostream & os) {
	if( ! this->empty() ) {
		this->column_start();
		for(Row::size_type it = 0; it < this->lin_size; ++it) {
			os << this->cVec;
			this->column_shift();
		}
	}
	return;
}
void ColsVector::update_counts() {
	++colsCount;
	rowsCount = lin_size;
	return;
}


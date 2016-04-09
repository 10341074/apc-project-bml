#include "VecVector.h"
bool VecVector::empty() const {
	return drVec.empty();
}
// void VecVector::push_back(const DynRow & dr) {
//	drVec.push_back(dr);
//	return;
// }
// void VecVector::push_back(DynRow && dr) {
//	drVec.push_back(dr);
//	return;
// }
// void VecVector::push_back(Row * r){
//	if(r == nullptr)
//		throw std::logic_error("VecVector::push_back with Row * equal to nullptr");
//	if(drVec.empty())
//		cMaxIndex = r->size();
//	else if(cMaxIndex != r->size())
//		throw std::runtime_error("VecVector::push_back row with different length");
//	
//	cVec.push_back(r->begin());
//	drVec.push_back(r);
//	cIndex = 0;
// return;
// }
void VecVector::push_back(std::unique_ptr<Row> r){
	if(r == nullptr)
		throw std::logic_error("VecVector::push_back with unique_ptr<Row> equal to nullptr");
	if(drVec.empty())
		cMaxIndex = r->size();
	else if(cMaxIndex != r->size())
		throw std::runtime_error("VecVector::push_back row with different length");

	cVec.push_back(r->begin());
	drVec.push_back( std::unique_ptr<Row>(r.release()) );
	cIndex = 0;
	this->update_counts();
	return;
}
void VecVector::column_start() {
	if(drVec.empty())
		throw std::logic_error("VecVector::column_start() with empty vectors");
	if(drVec.size() != cVec.size())
		throw std::logic_error("VecVector::column_start() cVec and drVec different sizes");
	DrVec::iterator dr_it = drVec.begin();
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		* it = dr_it->begin();
		++ dr_it;
	}
	return;
}
void VecVector::column_shift() {
	if(drVec.empty())
		throw std::logic_error("VecVector::column_start() with empty vectors");
	if(cIndex >= cMaxIndex)
		throw std::out_of_range("VecVector::column_shift out of range");
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		++ (* it);
	}
	return;
}
VecVector::VecVector(DrVec::size_type rows, Row::size_type cols) :
	drVec(rows,DynRow(cols)), cVec(rows) {
	cMaxIndex = cols;
	cIndex = 0;
	this->column_start();
}
std::ostream & operator<<(std::ostream & os, VecVector & vecVec) {
	vecVec.print(os);
	return os;
}
//////////////////////////////////////////////////////////////////////////////////////
RowsVector::RowsVector(DrVec::size_type rows, Row::size_type cols) : 
	VecVector(rows,cols) {
	rowsCount = rows;
	colsCount = cols;
}
std::ostream & operator<<(std::ostream & os,RowsVector & rowsVec) {
	rowsVec.print(os);
	return os;
}
void RowsVector::print(std::ostream & os) {
	for(std::vector<DynRow>::const_iterator it = this->drVec.begin(); it != this->drVec.end(); ++it) {
		os << * it->get_row_pointer();
	}
	return;
}
void RowsVector::update_counts() {
	++rowsCount;
	colsCount = cMaxIndex;
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
ColsVector::ColsVector(DrVec::size_type cols, Row::size_type rows) :
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
		for(Row::size_type it = 0; it < this->cMaxIndex; ++it) {
			os << this->cVec;
			this->column_shift();
		}
	}
	return;
}
void ColsVector::update_counts() {
	++colsCount;
	rowsCount = cMaxIndex;
	return;
}


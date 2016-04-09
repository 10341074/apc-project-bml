#include "RowsVector.h"
RowsVector::RowsVector(DrVec::size_type rows, Row::size_type cols, TypeMatrix t) :
	drVec(rows,DynRow(cols)), cVec(rows), type(t) {
	cMaxIndex = cols;
	cIndex = 0;
	this->column_start();
}
// void RowsVector::push_back(const DynRow & dr) {
//	drVec.push_back(dr);
//	return;
// }
// void RowsVector::push_back(DynRow && dr) {
//	drVec.push_back(dr);
//	return;
// }
void RowsVector::push_back(Row * r){
	if(r == nullptr)
		throw std::logic_error("RowsVector::push_back with Row * equal to nullptr");
	if(drVec.empty())
		cMaxIndex = r->size();
	else if(cMaxIndex != r->size())
		throw std::runtime_error("RowsVector::push_back row with different length");
	
	cVec.push_back(r->begin());
	drVec.push_back(r);
	cIndex = 0;
return;
}
void RowsVector::push_back(std::unique_ptr<Row> r){
	if(r == nullptr)
		throw std::logic_error("RowsVector::push_back with unique_ptr<Row> equal to nullptr");
	if(drVec.empty())
		cMaxIndex = r->size();
	else if(cMaxIndex != r->size())
		throw std::runtime_error("RowsVector::push_back row with different length");

	cVec.push_back(r->begin());
	drVec.push_back( std::unique_ptr<Row>(r.release()) );
	cIndex = 0;
return;
}
std::ostream & operator<<(std::ostream & os,RowsVector & rowsVec) {
	if(rowsVec.type == ByRows) {
		for(std::vector<DynRow>::const_iterator it = rowsVec.drVec.begin(); it != rowsVec.drVec.end(); ++it) {
			os << * it->get_row_pointer();
		}
	} else if (rowsVec.type == ByCols) {
		rowsVec.column_start();
		for(Row::size_type it = 0; it < rowsVec.cMaxIndex; ++it) {
			os << rowsVec.cVec;
			rowsVec.column_shift();
		}
	}
	return os;
}
void RowsVector::column_start() {
	if(drVec.empty())
		throw std::logic_error("RowsVector::column_start() with empty vectors");
	if(drVec.size() != cVec.size())
		throw std::logic_error("RowsVector::column_start() cVec and drVec different sizes");
	DrVec::iterator dr_it = drVec.begin();
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		* it = dr_it->begin();
		++ dr_it;
	}
	return;
}
void RowsVector::column_shift() {
	if(drVec.empty())
		throw std::logic_error("RowsVector::column_start() with empty vectors");
	if(cIndex >= cMaxIndex)
		throw std::out_of_range("RowsVector::column_shift out of range");
	for(ColumnVec::iterator it = cVec.begin(); it != cVec.end(); ++it){
		++ (* it);
	}
	return;
}

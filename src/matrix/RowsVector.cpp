#include "RowsVector.h"
// RowsVector::size_type DynRow::size() const {
//	if(row != nullptr)
//		throw std::logic_error("DynRow::size() with row = nullptr");
//	return row->size();
// }
// bool DynRow::empty() const {
//	if(row != nullptr)
//		throw std::logic_error("DynRow::empty() with row = nullptr");
//	return row->empty();
// }
// 
// Row::iterator DynRow::begin(){
//	if(row != nullptr)
//		throw std::logic_error("DynRow::size() with row = nullptr");
//	return row->begin();
// }
// Row::iterator DynRow::begin() const {
//	if(row != nullptr)
//		throw std::logic_error("DynRow::size() with row = nullptr");
//	return row->begin();
// }
// //	Row::const_iterator cbegin() const;
// Row::iterator DynRow::end() {
//	if(row != nullptr)
//		throw std::logic_error("DynRow::size() with row = nullptr");
//	return row->end();
// }
// Row::iterator DynRow::end() const {
//	if(row != nullptr)
//		throw std::logic_error("DynRow::size() with row = nullptr");
//	return row->end();
// }
// //	Row::const_iterator cend() const;


void RowsVector::push_back(const DynRow & dr) {
//	drVec.push_back(dr);
	return;
}
void RowsVector::push_back(DynRow && dr) {
//	drVec.push_back(dr);
	return;
}
void RowsVector::push_back(Row * r){
	drVec.push_back(r);
return;
}
std::ostream & operator<<(std::ostream & os, const RowsVector & rowsVec) {
	for(std::vector<DynRow>::const_iterator it = rowsVec.drVec.begin(); it != rowsVec.drVec.end(); ++it) {
		os << * it->get_row_pointer();
	}
	return os;
}

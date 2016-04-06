#include "DynRow.h"
DynRow::DynRow() :
	row(new Row){
}
DynRow::~DynRow() {
	if(row != nullptr)
		delete row;
	row = nullptr;
}
DynRow::DynRow(const DynRow & dr) : 
	row(new Row(* dr.row)) {
	std::cout << "DynRow copy cons" << std::endl;
}
DynRow & DynRow::operator=(const DynRow & dr) {
	std::cout << "DynRow copy ass" << std::endl;
	if(row != nullptr)
		delete row;
	row = new Row(* dr.row);
	return * this;
}
DynRow::DynRow(DynRow && dr) : 
	row(dr.row) {
	std::cout << "DynRow move cons" << std::endl;
	dr.row = nullptr;
}
DynRow & DynRow::operator=(DynRow && dr) {
	std::cout << "DynRow move ass" << std::endl;
	if(row != nullptr)
		delete row;
	row = dr.row;
	dr.row = nullptr;
	return * this;
}
DynRow::DynRow(Row * r) : 
	row(r) {
}
Row::size_type DynRow::size() const {
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->size();
}
bool DynRow::empty() const {
	if(row != nullptr)
		throw std::logic_error("DynRow::empty() with row = nullptr");
	return row->empty();
}

Row::iterator DynRow::begin(){
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->begin();
}
Row::const_iterator DynRow::begin() const {
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->begin();
}
//	Row::const_iterator cbegin() const;
Row::iterator DynRow::end() {
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->end();
}
Row::const_iterator DynRow::end() const {
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->end();
}
//	Row::const_iterator cend() const;

void DynRow::push_back(const Color & col){
	std::cout << "DynRow push_back &" << std::endl;
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	row->push_back(col);
	return;
}
void DynRow::push_back(Color && col){
	std::cout << "DynRow push_back &&" << std::endl;
	if(row != nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	row->push_back(col);
	return;
}


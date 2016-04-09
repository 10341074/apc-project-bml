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
}
DynRow & DynRow::operator=(const DynRow & dr) {
	if(row != nullptr)
		delete row;
	row = new Row(* dr.row);
	return * this;
}
DynRow::DynRow(DynRow && dr) : 
	row(dr.row) {
	dr.row = nullptr;
}
DynRow & DynRow::operator=(DynRow && dr) {
	if(row != nullptr)
		delete row;
	row = dr.row;
	dr.row = nullptr;
	return * this;
}
DynRow::DynRow(Row * r) : 
	row(r) {
}
DynRow::DynRow(std::unique_ptr<Row> r) :
	row(r.release()) {
}
DynRow::DynRow(Row::size_type s) : 
	row(new Row(s,White)) {
}
Row::size_type DynRow::size() const {
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->size();
}
bool DynRow::empty() const {
	if(row == nullptr)
		throw std::logic_error("DynRow::empty() with row = nullptr");
	return row->empty();
}

Row::iterator DynRow::begin(){
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->begin();
}
Row::const_iterator DynRow::begin() const {
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->begin();
}
//	Row::const_iterator cbegin() const;
Row::iterator DynRow::end() {
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->end();
}
Row::const_iterator DynRow::end() const {
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	return row->end();
}
//	Row::const_iterator cend() const;

void DynRow::push_back(const Color & col){
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	row->push_back(col);
	return;
}
void DynRow::push_back(Color && col){
	if(row == nullptr)
		throw std::logic_error("DynRow::size() with row = nullptr");
	row->push_back(col);
	return;
}


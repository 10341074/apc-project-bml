#include "DynRowDeque.h"
DynRowDeque::DynRowDeque() :
	row(new DequeCar), length(0) {
}
DynRowDeque::~DynRowDeque() {
	if(row != nullptr)
		delete row;
	row = nullptr;
}
DynRowDeque::DynRowDeque(const DynRowDeque & dr) :
	row(new DequeCar(* dr.row)), length(dr.length) {
}
DynRowDeque & DynRowDeque::operator=(const DynRowDeque & dr) {
	if(row != nullptr)
		delete row;
	row = new DequeCar(* dr.row);
	length = dr.length;
	return * this;
}
DynRowDeque::DynRowDeque(DynRowDeque && dr) : 
	row(dr.row), length(dr.length) {
	dr.row = nullptr;
}
DynRowDeque & DynRowDeque::operator=(DynRowDeque && dr) {
	if(row != nullptr)
		delete row;
	row = dr.row;
	length = dr.length;
	dr.row = nullptr;
	return * this;
}
DynRowDeque::DynRowDeque(DequeCar * & r, size_type l) : 
	row(r), length(l) {
		r = nullptr;
}
DynRowDeque::DynRowDeque(std::unique_ptr<DequeCar> r, size_type l) :
	row(r.release()), length(l) {
}
// DynRowDeque::DynRowDeque(size_type s) : 
//	row(new DequeCar(s)), length(s) {
// }
size_type DynRowDeque::size() const {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	return row->size();
}
bool DynRowDeque::empty() const {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::empty() with row = nullptr");
	return row->empty();
}

DequeCar::iterator DynRowDeque::begin(){
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	return row->begin();
}
DequeCar::const_iterator DynRowDeque::begin() const {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	return row->begin();
}
//	DequeCar::const_iterator cbegin() const;
DequeCar::iterator DynRowDeque::end() {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	return row->end();
}
DequeCar::const_iterator DynRowDeque::end() const {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	return row->end();
}
//	DequeCar::const_iterator cend() const;

void DynRowDeque::push_back(const Car & car){
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	row->push_back(car);
	return;
}
void DynRowDeque::push_back(Car && car){
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::size() with row = nullptr");
	row->push_back(car);
	return;
}
void DynRowDeque::move(const Color & cl) {
	if(row == nullptr)
		throw std::logic_error("DynRowDeque::move with row = nullptr");
	row->push_back( *row->begin() );
	row->end()->J += length;
	DequeCar::iterator it = row->begin() + 1;
	DequeCar::iterator it_old = row->begin();
	DequeCar::iterator it_end = row->end();
	for(;it != it_end; ++it) {
		if((it_old->A == cl) && (it_old->J + 1 < it->J))
			++(it_old->J);
	}
	row->pop_back();
	if(row->end()->J >= length){
		row->end()->J = 0;
		row->push_front( *row->end() );
		row->pop_back();
	}
	return;
}

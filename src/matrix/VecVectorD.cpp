#include "VecVectorD.h"
std::ostream & operator<<(std::ostream & os, const OwnerDataD & d) {
	os << d.vec;
	return os;
}
void OwnerDataD::print() const {
	std::cout << "vec\n" << vec;
	std::cout << "cVec\n";
	for(ColumnD::const_iterator it1 = cVec.begin(); it1 != cVec.end(); ++it1) {
		for(std::list<ColorD>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * * it2 << Separator;
		}
		std::cout << std::endl;
	} 
	std::cout << "White\n";
	for(std::list<ColorD * >::const_iterator it = white.begin(); it != white.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Blue\n";
	for(std::list<ColorD * >::const_iterator it = blue.begin(); it != blue.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Red\n";
	for(std::list<ColorD * >::const_iterator it = red.begin(); it != red.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	return;
}
void VecVectorD::push_back(std::list<Color> & l2, const std::size_t & count) {
	RowD & vec = pVec->vec;
	ColumnD & cVec = pVec->cVec;
	if(vec.empty()) {
		lin_size = count;
		for(std::size_t in = 0; in < count; ++in) {	// build all columns
			cVec.push_back( std::list<ColorD>() );
		}
	} else if(lin_size != count)
		throw std::runtime_error("VecVector::push_back row with different length");
	++vec_size;
	// add row
	vec.push_back( std::list<Color>() );
	std::list<Color> & l1 = * (--vec.end());
	l1.splice(l1.begin(), l2);
	// add column
	std::list<ColorD * > white;
	std::list<ColorD * > blue;
	std::list<ColorD * > red;
	
	std::list<std::list<ColorD>>::iterator it_c = cVec.begin();
	for(std::list<Color>::iterator it = l1.begin(); it != l1.end(); ++it) {
		it_c->push_back(it);
		ColorD & last = * (--(it_c->end()));
		switch(* it) {
			case(White):
				white.push_back(&last);
				break;
			case(Blue):
				blue.push_back(&last);
				break;
			case(Red):
				red.push_back(&last);
				break;
//			default:
//				break;
		}
		
		++it_c;
	}
	this->push_back_white(white);
	this->push_back_blue(blue);
	this->push_back_red(red);
	return;
}
void VecVectorD::push_back_white(std::list<ColorD * > & l2) {
	std::list<ColorD * > & l1 = pVec->white;
	l1.splice(l1.end(), l2);
	return;
}
void VecVectorD::push_back_blue(std::list<ColorD * > & l2) {
	std::list<ColorD * > & l1 = pVec->blue;
	l1.splice(l1.end(), l2);
	return;
}
void VecVectorD::push_back_red(std::list<ColorD * > & l2) {
	std::list<ColorD * > & l1 = pVec->red;
	l1.splice(l1.end(), l2);
	return;
}

std::ostream & operator<<(std::ostream & os, RowsVectorD & rowsvec) {
	if(rowsvec.pVec != nullptr) {
		os << * rowsvec.pVec;
	}
	return os;
}
std::ostream & operator<<(std::ostream & os, ColsVectorD & colsvec) {
	if(colsvec.pVec != nullptr) {
		os << * colsvec.pVec;
	}
	return os;
}
/*
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
//*/

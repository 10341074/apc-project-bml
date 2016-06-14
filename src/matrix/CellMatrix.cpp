#include "CellMatrix.h"

std::ostream & operator<<(std::ostream & os, const OwnerData & d) {
	for(CarsData::const_iterator it1 = d.cars.begin(); it1 != d.cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * it2 << Separator;
		}
		std::cout << std::endl;
	}
	return os;
}
void OwnerData::print() const {
	std::cout << "cars\n";
	for(CarsData::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * it2 << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "White\n";
	for(OneColor::const_iterator it = white.begin(); it != white.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Blue\n";
	for(OneColor::const_iterator it = blue.begin(); it != blue.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Red\n";
	for(OneColor::const_iterator it = red.begin(); it != red.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	return;
}
bool OwnerData::choose_white() const {
	if(2 * white.size() > red.size() + blue.size())
		return true;
	else 
		return false;
}

void CellMatrix::push_back(CarsData & l2, const std::size_t & count) {
	// count == l2->size()
	CarsData & 	cars 		= pvec->cars;
	if(cars.empty()) {
		inn_size = count;
	} else if(inn_size != count)
		throw std::runtime_error("CellMatrix::push_back row with different length");
	++ext_size;
	// add row
	cars.splice(cars.end(),l2);
	return;
}
void CellMatrix::push_back_white(OneColor & l2) {
	OneColor & l1 = pvec->white;
//	l1.push_pack(l2);
	l1.splice(l1.end(), l2);
	return;
}
void CellMatrix::push_back_blue(OneColor & l2) {
	OneColor & l1 = pvec->blue;
//	l1.push_pack(l2);
	l1.splice(l1.end(), l2);
	return;
}
void CellMatrix::push_back_red(OneColor & l2) {
	OneColor & l1 = pvec->red;
//	l1.push_pack(l2);
	l1.splice(l1.end(), l2);
	return;
}
void two_lines(CarsData::iterator it_ext, CarsData::iterator it_ext2, OneColor & white, OneColor & blue, OneColor & red) {
		CarsDataIn::iterator it_in				= it_ext->begin();
		CarsDataIn::iterator it_in_next		= it_in;	++it_in_next;
		CarsDataIn::iterator it_in_end		= it_ext->end();
		// next row
		CarsDataIn::iterator it_in2			= it_ext2->begin();
//		CarsDataIn::iterator it_in2_next		= it_in2; ++it_in2_next;
//		CarsDataIn::iterator it_in2_end		= it2_ext->end();

		Cell * first = &*it_in;	// save for after
		for( ; it_in_next != it_in_end; ++it_in_next) { // loop on columns along 1 row
			// 1 interface with next along row
			it_in->update_r(&*it_in_next);
			it_in_next->update_l(&*it_in);
			
			// 2 interface with next along col
			it_in->update_d(&*it_in2);
			it_in2->update_u(&*it_in);
			
			// 3 save color
			switch( it_in->get_color() ) {
				case(White):
					white.push_back(&*it_in);
					break;
				case(Blue):
					blue.push_back(&*it_in);
					break;
				case(Red):
					red.push_back(&*it_in);
					break;
//				default:
//					break;
			}
			// advance 3 iterator
			++it_in;
			++it_in2;
			}
		
		// it_in points to last
		// 1 interface with next along row
		it_in->update_r(first);
		first->update_l(&*it_in);
		// 2 interface with next along col
		it_in->update_d(&*it_in2);
		it_in2->update_u(&*it_in);
		// 3 save color
		switch( it_in->get_color() ) {
			case(White):
		white.push_back(&*it_in);
				break;
			case(Blue):
				blue.push_back(&*it_in);
				break;
			case(Red):
				red.push_back(&*it_in);
				break;
//			default:
//				break;
		}
	return;
}
///*
void CellMatrix::update_data() {
	OneColor white;
	OneColor blue;
	OneColor red;

	CarsData::iterator it_ext 			= pvec->cars.begin();
	CarsData::iterator it_ext_end 	= pvec->cars.end();
	if(it_ext == it_ext_end) {			// empty matrix
		return;
	}
	if(it_ext->begin() == it_ext->end()){ // length zero row (check only first row)
		return;
	}
	
	CarsData::iterator it_ext2 = it_ext; ++it_ext2;		// to next row
	for( ; it_ext2 != it_ext_end; ++it_ext2) {	// loop on rows, without last				
		// current row
		CarsDataIn::iterator it_in				= it_ext->begin();
		CarsDataIn::iterator it_in_next		= it_in;	++it_in_next;
		CarsDataIn::iterator it_in_end		= it_ext->end();
		// next row
		CarsDataIn::iterator it_in2			= it_ext2->begin();
//		CarsDataIn::iterator it_in2_next		= it_in2; ++it_in2_next;
//		CarsDataIn::iterator it_in2_end		= it2_ext->end();
		
		Cell * first = &*it_in;	// save for after
		for( ; it_in_next != it_in_end; ++it_in_next) { // loop on columns along 1 row
			// 1 interface with next along row
			it_in->update_r(&*it_in_next);
			it_in_next->update_l(&*it_in);
			
			// 2 interface with next along col
			it_in->update_d(&*it_in2);
			it_in2->update_u(&*it_in);
			
			// 3 save color
			switch( it_in->get_color() ) {
				case(White):
					white.push_back(&*it_in);
					break;
				case(Blue):
					blue.push_back(&*it_in);
					break;
				case(Red):
					red.push_back(&*it_in);
					break;
//				default:
//					break;
			}
			// advance 3 iterator
			++it_in;
			++it_in2;
			}
		
		// it_in points to last
		// 1 interface with next along row
		it_in->update_r(first);
		first->update_l(&*it_in);
		// 2 interface with next along col
		it_in->update_d(&*it_in2);
		it_in2->update_u(&*it_in);
		// 3 save color
		switch( it_in->get_color() ) {
			case(White):
		white.push_back(&*it_in);
				break;
			case(Blue):
				blue.push_back(&*it_in);
				break;
			case(Red):
				red.push_back(&*it_in);
				break;
//			default:
//				break;
		}
		
		// advance 2 iterators
		++it_ext;	// advance current row with it_ext2 (next row)
	}
	// last row	
	two_lines(it_ext,pvec->cars.begin(),white,blue,red);
	this->push_back_white(white);
	this->push_back_blue(blue);
	this->push_back_red(red);
	return;
}
//*/
/*
void RowsVectorD::move_forward(const Color & cl) {
	std::list<ColorDD > * cll = & pvec->white;
	switch(cl) {
		case(Blue):
			cll = & pvec->blue;
			break;
		case(Red):
			cll = & pvec->red;
			break;
		case(White):
			break;
	}
	std::list<ColorDD *> cllp;
	for(std::list<ColorDD >::iterator it = cll->begin(); it != cll->end(); ++it) {
		ColorD it_r 	= * * it;
		ColorD it_r2 	= it_r; ++it_r2;
		if(it_r2->cl() == White) {
			cllp.push_back(& * it);
		}
	}
	for(std::list<ColorDD *>::iterator it = cllp.begin(); it != cllp.end(); ++it) {
		ColorDD & col	= * * it;
		ColorD it_r 	= * col;
		ColorD it_r2 	= it_r; ++it_r2;
		std::swap(it_r->cl(),it_r2->cl());
		// update color list
		col = it_r2->p();
	}
	return;
}
void RowsVectorD::move_white(const Color & cl) {
	std::list<ColorDD > * cll = & pvec->white;
	std::list<ColorDD *> cllp;
	for(std::list<ColorDD >::iterator it = cll->begin(); it != cll->end(); ++it) {
		ColorD it_r 	= * * it;
		ColorD it_r2 	= it_r; --it_r2;
		if(it_r2->cl() == cl) {
			cllp.push_back(& * it);
		}
	}
	for(std::list<ColorDD *>::iterator it = cllp.begin(); it != cllp.end(); ++it) {
		ColorDD & col	= * * it;
		ColorD it_r 	= * col;
		ColorD it_r2 	= it_r; --it_r2;
		std::swap(it_r->cl(),it_r2->cl());
		// update color list
		col = it_r2->p();
	}
	return;
}
std::ostream & operator<<(std::ostream & os, ColsVectorD & colsvec) {
	if(colsvec.pvec != nullptr) {
		os << * colsvec.pvec;
	}
	return os;
}
void ColsVectorD::move_forward(const Color & cl) {
	std::list<ColorDD > * cll = & pvec->white;
	switch(cl) {
		case(Blue):
			cll = & pvec->blue;
			break;
		case(Red):
			cll = & pvec->red;
			break;
		case(White):
			break;
	}
	std::list<ColorDD *> cllp;
	for(std::list<ColorDD >::iterator it = cll->begin(); it != cll->end(); ++it) {
		ColorDD 	it_c = * it;
		ColorDD 	it_c2 = it_c; ++it_c2;
		if((*it_c2)->cl() == White) {
			cllp.push_back(& * it);
		}
	}
	for(std::list<ColorDD *>::iterator it = cllp.begin(); it != cllp.end(); ++it) {
		ColorDD & col	= * * it;
		ColorDD it_c 	= col;
		ColorDD it_c2 	= it_c; ++it_c2;
		std::swap((*it_c)->cl(),(*it_c2)->cl());
		// update color list
		col = (*it_c2)->p();
	}
	return;
}
void ColsVectorD::move_white(const Color & cl) {
	std::list<ColorDD > * cll = & pvec->white;
	std::list<ColorDD *> cllp;
	for(std::list<ColorDD >::iterator it = cll->begin(); it != cll->end(); ++it) {
		ColorDD 	it_c = * it;
		ColorDD 	it_c2 = it_c; --it_c2;
		if((*it_c2)->cl() == cl) {
			cllp.push_back(& * it);
		}
	}
	for(std::list<ColorDD *>::iterator it = cllp.begin(); it != cllp.end(); ++it) {
		ColorDD & col	= * * it;
		ColorDD it_c 	= col;
		ColorDD it_c2 	= it_c; --it_c2;
		std::swap((*it_c)->cl(),(*it_c2)->cl());
		// update color list
		col = (*it_c2)->p();
	}
	return;
}
//*/

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

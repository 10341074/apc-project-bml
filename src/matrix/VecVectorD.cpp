#include "VecVectorD.h"

std::ostream & operator<<(std::ostream & os, const ColorP & o) {
	os << * o.my_c;
	return os;
}
std::ostream & operator<<(std::ostream & os, const RowD & v) {
	for(std::list<std::vector<ColorP>>::const_iterator it1 = v.begin(); it1 != v.end(); ++it1) {
		std::vector<ColorP>::const_iterator it2	 		= it1->begin();
		std::vector<ColorP>::const_iterator it2_end	 	= it1->end();
		if(it2 != it2_end) {
			--it2_end;
			// last column is copy of first column
			if(it2 != it2_end) {
				--it2_end;
				// first column is copy of last
				if(it2 != it2_end) {
					++it2;
					for( ; it2 != it2_end; ++it2) {
						os << * it2 << Separator;
					}
					os << * it2 << std::endl;
				}
			}
		}
	}
	return os;
}
std::ostream & operator<<(std::ostream & os, const OwnerDataD & d) {
	os << d.vec;
	return os;
}
void OwnerDataD::print() const {
	std::cout << "cars\n";
	for(CarsD::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(std::vector<Color>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * it2 << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "vec\n";
	for(RowD::const_iterator it1 = vec.begin(); it1 != vec.end(); ++it1) {
		for(std::vector<ColorP>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * it2 << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "cVec\n";
	for(ColumnD::const_iterator it1 = cvec.begin(); it1 != cvec.end(); ++it1) {
		for(std::list<ColorD>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * * it2 << Separator;
		}
		std::cout << std::endl;
	} 
	std::cout << "White\n";
	for(std::list<ColorDD >::const_iterator it = white.begin(); it != white.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Blue\n";
	for(std::list<ColorDD >::const_iterator it = blue.begin(); it != blue.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Red\n";
	for(std::list<ColorDD >::const_iterator it = red.begin(); it != red.end(); ++it) {
		std::cout << ***it << Separator;
	}
	std::cout << std::endl;
	return;
}
void VecVectorD::push_back(CarsD & l2, const std::size_t & count) {
	// count == l2->size()
	CarsD & 	cars 		= pvec->cars;
	RowD & 	vec 		= pvec->vec;
	ColumnD & cvec 	= pvec->cvec;
	if(cars.empty()) {
		lin_size = count;
		// build all columns (exact count)
		for(std::size_t in = 0; in < count; ++in) {
			cvec.push_back( std::list<ColorD>() );
		}
	} else if(lin_size != count)
		throw std::runtime_error("VecVector::push_back row with different length");
	++vec_size;
	// (rows 2 longer) add cars
	cars.splice(cars.end(),l2);
	vec.push_back( std::vector<ColorP>(count+1+1) );
	// update row and column
	std::vector<Color> & 	v_car = * ( --(cars.end()) );
	std::vector<ColorP> & 	v_row = * ( --(vec.end()) );
	std::list<ColorDD > white;
	std::list<ColorDD > blue;
	std::list<ColorDD > red;

	ColumnD::iterator 									it_c = cvec.begin();
	std::vector<ColorP>::iterator						it_r = v_row.begin();
	std::vector<Color>::iterator 						it = v_car.begin();
	// (rows 2 longer) not first column
	++it_r;
	for( ; it != v_car.end(); ++it) {
		it_c->push_back(it_r);
		ColorDD last = ( --(it_c->end()) );
		it_r->cp() = & * it;
		it_r->p() = last;
		switch( * it ) {
			case(White):
				white.push_back(last);
				break;
			case(Blue):
				blue.push_back(last);
				break;
			case(Red):
				red.push_back(last);
				break;
//			default:
//				break;
		}
		++it_r;
		++it_c;
	}
	// (rows 2 longer) add first column equal to last
	std::vector<ColorP>::iterator 	it_rr = v_row.begin();
	--it_r;
	* it_rr = * it_r;
	// (rows 1 longer) add last column equal to first
	++it_rr;
	++it_r;
	* it_r = * it_rr;
//	* it_r = * v_row.begin();
	this->push_back_white(white);
	this->push_back_blue(blue);
	this->push_back_red(red);
	return;
}
void VecVectorD::border_columns() {
	ColumnD & 				cvec = pvec->cvec;
	ColumnD::iterator 	it_c = cvec.begin();
	for( ; it_c != cvec.end(); ++it_c) {
		std::list< ColorD >::iterator it_c2 = it_c->end();
		--it_c2;
		it_c->emplace_front(* it_c2);
		it_c2 = it_c->begin();
		++it_c2;
		it_c->emplace_back(* it_c2);
	}
	return;
}
void VecVectorD::push_back_white(std::list<ColorDD > & l2) {
	std::list<ColorDD > & l1 = pvec->white;
	l1.splice(l1.end(), l2);
	return;
}
void VecVectorD::push_back_blue(std::list<ColorDD > & l2) {
	std::list<ColorDD > & l1 = pvec->blue;
	l1.splice(l1.end(), l2);
	return;
}
void VecVectorD::push_back_red(std::list<ColorDD > & l2) {
	std::list<ColorDD > & l1 = pvec->red;
	l1.splice(l1.end(), l2);
	return;
}

std::ostream & operator<<(std::ostream & os, RowsVectorD & rowsvec) {
	if(rowsvec.pvec != nullptr) {
		os << * rowsvec.pvec;
	}
	return os;
}
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
/*
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

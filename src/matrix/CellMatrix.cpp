#include "CellMatrix.h"
void one_color_conv(const OneColor_Old & c_old, OneColor & c_new) {
	c_new = OneColor(c_old.size(),nullptr);
	OneColor_Old::const_iterator it_old = c_old.begin();
	OneColor_Old::const_iterator it_old_end = c_old.end();
	OneColor::iterator it_new = c_new.begin();
	for( ; it_old != it_old_end; ++it_old) {
		*it_new = *it_old;
		++it_new;
	}
	return;
}

void OwnerData::load_data(const OwnerData_Old & d) {
//	one_color_conv(d.white, white);
//	one_color_conv(d.blue, blue);
//	one_color_conv(d.red, red);

	cars = CarsData(d.ext_size, CarsDataIn(d.inn_size));
	CarsData_Old::const_iterator it_old = d.cars.begin();
	CarsData_Old::const_iterator it_old_end = d.cars.end();
	CarsData::iterator it_new = cars.begin();
	for( ; it_old != it_old_end; ++it_old) {
		*it_new = *it_old;
		++it_new;
	}
	return;
}

std::ostream & operator<<(std::ostream & os, const OwnerData & d) {
	for(CarsData::const_iterator it1 = d.cars.begin(); it1 != d.cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			os << * it2 << Separator;
		}
		os << std::endl;
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
	std::cout << "from right\n";
	for(CarsData::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_r();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from left\n";
	for(CarsData::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_l();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from up\n";
	for(CarsData::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_u();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from down\n";
	for(CarsData::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_d();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}


	return;
}

bool OwnerData::choose_white() const {
	if(2 * white.size() < red.size() + blue.size())
		return true;
	else 
		return false;
}
/*
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
*/
void two_lines(CarsData::iterator it_ext, CarsData::iterator it_ext2, OneColor_Old & white, OneColor_Old & blue, OneColor_Old & red) {
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
	return;
}
///*
void CellMatrix::update_data() {
	std::cout << "update data " << std::endl;
	OneColor_Old white;
	OneColor_Old blue;
	OneColor_Old red;

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
		two_lines(it_ext,it_ext2,white,blue,red);
		
		// advance 2 iterators
		++it_ext;	// advance current row with it_ext2 (next row)
	}
	// it_ext points to last
	// last row	
	two_lines(it_ext,pvec->cars.begin(),white,blue,red);
	
	one_color_conv(white,pvec->white);
	one_color_conv(blue,pvec->blue);
	one_color_conv(red,pvec->red);
	
	//this->push_back_white(white);
	//this->push_back_blue(blue);
	//this->push_back_red(red);
	return;
}
//*/
///*

// to be done: mix cycle: two cycle together for each row or better allocate new Onecolor 2 list to swap and update current onelcolor immediately
void CellMatrixRows::move_forward(const Color & cl) {
//	std::cout << "move-for-row" << cl <<std::endl;
	// don't use reference otherwise error cause copy assignement
	OneColor * ptr_color = & pvec->white;
	switch(cl) {
		case(Blue):
			ptr_color = & pvec->blue;
			break;
		case(Red):
			ptr_color = & pvec->red;
			break;
		case(White):
			break;
	}
	
	OneColor & color = * ptr_color;
//	std::cout << "to be been moved " << cl;
//	for(OneColor::const_iterator itt = (pvec->red).begin(); itt != (pvec->red).end(); ++itt) {
//		std::cout << **itt << Separator;
//	}
//	std::cout<< std::endl;

	std::vector<Cell *> to_be_moved; to_be_moved.reserve(color.size());
	std::vector<Cell *> to_be_moved_next; to_be_moved_next.reserve(color.size());

	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		Cell * next = (*it)->get_r();
//	std::cout << "color pointed1 " << (*it)->get_color() << std::endl;	

		if(next->get_color() == White) {
			to_be_moved.push_back(*it);
			to_be_moved_next.push_back(next);
			
			// update color list
			* it = next;

		}
//	++index;
	}
	std::vector<Cell *>::iterator it_next = to_be_moved_next.begin(); 
	for(std::vector<Cell *>::iterator it = to_be_moved.begin(); it != to_be_moved.end(); ++it) {
		//Cell * next = (*it)->get_r();
		std::swap((*it)->get_color(),(*it_next)->get_color());
		++it_next;
	}

//	std::cout << "had been moved " << cl;
//	for(OneColor::const_iterator itt = color.begin(); itt != color.end(); ++itt) {
//		std::cout << **itt << Separator;
//	}
//	std::cout<< std::endl;
	return;
}
void CellMatrixRows::move_white(const Color & cl) {
//	std::cout << "move-white-row" << cl <<std::endl;
	OneColor & color = pvec->white;
	std::vector<std::size_t> to_be_moved; to_be_moved.reserve(color.size());
	std::size_t index = 0;
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		Cell * next = (*it)->get_l();
		if(next->get_color() == cl) {
			to_be_moved.push_back(index);
		}
	++index;
	}
	OneColor::iterator it = color.begin();
	index = 0;
	for(std::size_t index_to_be_moved=0; index_to_be_moved < to_be_moved.size(); ++index_to_be_moved) {
		for(; index < to_be_moved[index_to_be_moved]; ++index) {
			++it;
		}
		Cell * next = (*it)->get_l();
		std::swap((*it)->get_color(),next->get_color());		
		// update color list
		* it = next;
	}
	return;
}
std::ostream & operator<<(std::ostream & os, CellMatrixRows & mat) {
	if(mat.pvec != nullptr) {
		os << * mat.pvec;
	}
	return os;
}
void CellMatrixCols::move_forward(const Color & cl) {
//	std::cout << "move-for-col" << cl <<std::endl;
	OneColor * ptr_color = & pvec->white;
	switch(cl) {
		case(Blue):
			ptr_color = & pvec->blue;
			break;
		case(Red):
			ptr_color = & pvec->red;
			break;
		case(White):
			break;
	}
	
	OneColor & color = * ptr_color;

	std::vector<Cell *> to_be_moved; to_be_moved.reserve(color.size());
	std::vector<Cell *> to_be_moved_next; to_be_moved_next.reserve(color.size());
//	std::size_t index = 0;
	
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		Cell * next = (*it)->get_d();
		if(next->get_color() == White) {
			to_be_moved.push_back(*it);
			to_be_moved_next.push_back(next);
			
			// update color list
			* it = next;
		}
//	++index;
	}
	std::vector<Cell *>::iterator it_next = to_be_moved_next.begin(); 
	for(std::vector<Cell *>::iterator it = to_be_moved.begin(); it != to_be_moved.end(); ++it) {
		//Cell * next = (*it)->get_d();
		std::swap((*it)->get_color(),(*it_next)->get_color());
		++it_next;
	}
	return;
}
void CellMatrixCols::move_white(const Color & cl) {
//	std::cout << "move-white-col" << cl <<std::endl;
	OneColor & color = pvec->white;
	std::vector<std::size_t> to_be_moved; to_be_moved.reserve(color.size());
	std::size_t index = 0;
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		Cell * next = (*it)->get_u();
		if(next->get_color() == cl) {
			to_be_moved.push_back(index);
		}
	++index;
	}
	OneColor::iterator it = color.begin();
	index = 0;
	for(std::size_t index_to_be_moved=0; index_to_be_moved < to_be_moved.size(); ++index_to_be_moved) {
		for(; index < to_be_moved[index_to_be_moved]; ++index) {
			++it;
		}
		Cell * next = (*it)->get_u();
		std::swap((*it)->get_color(),next->get_color());		
		// update color list
		* it = next;
	}
	return;
}
std::ostream & operator<<(std::ostream & os, CellMatrixCols & mat) {
	if(mat.pvec != nullptr) {
		os << * mat.pvec;
	}
	return os;
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

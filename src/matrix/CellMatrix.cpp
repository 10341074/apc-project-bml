#include "CellMatrix.h"
CarsDataIn::const_iterator find_cell(const CarsData & d, const std::size_t & i, const std::size_t & j) {
	CarsData::const_iterator it_ext = d.begin();
	for(std::size_t ind_ext = 0; ind_ext < i; ++ind_ext) {
		++it_ext;
	}
	CarsDataIn::const_iterator it_in = it_ext->begin();
	for(std::size_t ind_in = 0; ind_in < j; ++ind_in) {
		++it_in;
	}
	return it_in;
}
CarsDataIn::iterator find_cell(CarsData & d, const std::size_t & i, const std::size_t & j) {
	CarsData::iterator it_ext = d.begin();
	for(std::size_t ind_ext = 0; ind_ext < i; ++ind_ext) {
		++it_ext;
	}
	CarsDataIn::iterator it_in = it_ext->begin();
	for(std::size_t ind_in = 0; ind_in < j; ++ind_in) {
		++it_in;
	}
	return it_in;
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
		std::cout << * find_cell(cars,it->i(), it->j() ) << Separator;
	}
	std::cout << std::endl;
	std::cout << "Blue\n";
	for(OneColor::const_iterator it = blue.begin(); it != blue.end(); ++it) {
		std::cout << * find_cell(cars,it->i(), it->j() ) << Separator;
	}
	std::cout << std::endl;
	std::cout << "Red\n";
	for(OneColor::const_iterator it = red.begin(); it != red.end(); ++it) {
		std::cout << * find_cell(cars,it->i(), it->j() ) << Separator;
	}
	std::cout << std::endl;
	return;
}

bool OwnerData::choose_white() const {
	if(2 * white.size() < red.size() + blue.size())
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
void one_line(CarsData::iterator it_ext, std::size_t index_row, OneColor & white, OneColor & blue, OneColor & red) {
		// current row
		CarsDataIn::iterator it_in				= it_ext->begin();
		CarsDataIn::iterator it_in_end		= it_ext->end();
		
		std::size_t index_col = 0;
		
		for( ; it_in != it_in_end; ++it_in) { // loop on columns along 1 row			
			// 3 save color
			switch( * it_in ) {
				case(White):
					white.push_back(Coordinates(index_row, index_col));
					break;
				case(Blue):
					blue.push_back(Coordinates(index_row, index_col));
					break;
				case(Red):
					red.push_back(Coordinates(index_row, index_col));
					break;
//				default:
//					break;
			}
			++index_col;
		}
	return;
}

///*
void CellMatrix::update_data() {
	std::cout << "update data " << std::endl;
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
	std::size_t index_row = 0;
	for( ; it_ext != it_ext_end; ++it_ext) {	// loop on rows			
		one_line(it_ext,index_row,white,blue,red);
		++index_row;
	}	

	this->push_back_white(white);
	this->push_back_blue(blue);
	this->push_back_red(red);

	return;
}
//*/
///*

// to be done: mix cycle: two cycle together for each row or better allocate new Onecolor 2 list to swap and update current onelcolor immediately
void CellMatrixRows::move_forward(const Color & cl) {
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

	std::vector<CarsDataIn::iterator> to_be_moved1; to_be_moved1.reserve(color.size());
	std::vector<CarsDataIn::iterator> to_be_moved2; to_be_moved2.reserve(color.size());
	
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		std::size_t 				index_next = (it->j() + 1) % inn_size;
		CarsDataIn::iterator 	color_current = find_cell(pvec->cars, it->i(), it->j() );
		CarsDataIn::iterator 	color_next = color_current + 1;
		if(index_next == 0) {
			color_next = find_cell(pvec->cars, it->i(), index_next);
			}
		if( * color_next == White) {
			to_be_moved1.push_back(color_current);
			to_be_moved2.push_back(color_next);
			// immediate update of color 
			it->j() = index_next;
		}
	}

	std::vector<CarsDataIn::iterator>::iterator it1 = to_be_moved1.begin();
	std::vector<CarsDataIn::iterator>::iterator it2 = to_be_moved2.begin();
	for(std::size_t index=0; index < to_be_moved1.size(); ++index) {

		std::swap(*(*it1),*(*it2));
		++it1;
		++it2;
	}
//			std::cout << "had been moved " << cl;
//	for(OneColor::const_iterator itt = pvec->red.begin(); itt != pvec->red.end(); ++itt) {
//		std::cout << * find_cell(pvec->cars, itt->i(), itt->j() ) << Separator;
//	}
//	std::cout<< std::endl;

	return;
}

void CellMatrixRows::move_white(const Color & cl) {
	OneColor & color = pvec->white;
	std::vector<CarsDataIn::iterator> to_be_moved1; to_be_moved1.reserve(color.size());
	std::vector<CarsDataIn::iterator> to_be_moved2; to_be_moved2.reserve(color.size());
	
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		std::size_t 				index_next = (it->j() - 1 + inn_size) % inn_size; // positive
		CarsDataIn::iterator 	color_current = find_cell(pvec->cars, it->i(), it->j() );
		CarsDataIn::iterator 	color_next = color_current - 1;
		if(index_next == (inn_size - 1)) {
			color_next = find_cell(pvec->cars, it->i(), index_next);
			}
		if( * color_next == cl) {
			to_be_moved1.push_back(color_current);
			to_be_moved2.push_back(color_next);
			// immediate update of color 
			it->j() = index_next;
		}
	}
	std::vector<CarsDataIn::iterator>::iterator it1 = to_be_moved1.begin();
	std::vector<CarsDataIn::iterator>::iterator it2 = to_be_moved2.begin();
	for(std::size_t index=0; index < to_be_moved1.size(); ++index) {

		std::swap(*(*it1),*(*it2));
		++it1;
		++it2;
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
	
	std::size_t ext_size = (pvec->cars).size();
	std::vector<CarsDataIn::iterator> to_be_moved1; to_be_moved1.reserve(color.size());
	std::vector<CarsDataIn::iterator> to_be_moved2; to_be_moved2.reserve(color.size());

	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		std::size_t 				index_next = (it->i() + 1) % ext_size;
		CarsDataIn::iterator 	color_current = find_cell(pvec->cars, it->i(), it->j() );
		CarsDataIn::iterator 	color_next = find_cell(pvec->cars, index_next, it->j() );
		if( * color_next == White) {
			to_be_moved1.push_back(color_current);
			to_be_moved2.push_back(color_next);
			// immediate update of color 
			it->i() = index_next;
		}
	}
	std::vector<CarsDataIn::iterator>::iterator it1 = to_be_moved1.begin();
	std::vector<CarsDataIn::iterator>::iterator it2 = to_be_moved2.begin();
	for(std::size_t index=0; index < to_be_moved1.size(); ++index) {

		std::swap(*(*it1),*(*it2));
		++it1;
		++it2;

	}
	return;
}
void CellMatrixCols::move_white(const Color & cl) {
	OneColor & color = pvec->white;

	std::size_t ext_size = (pvec->cars).size();
	std::vector<CarsDataIn::iterator> to_be_moved1; to_be_moved1.reserve(color.size());
	std::vector<CarsDataIn::iterator> to_be_moved2; to_be_moved2.reserve(color.size());
	
	for(OneColor::iterator it = color.begin(); it != color.end(); ++it) {
		std::size_t 				index_next = (it->i() - 1 + ext_size) % ext_size;
		CarsDataIn::iterator 	color_current = find_cell(pvec->cars, it->i(), it->j() );
		CarsDataIn::iterator 	color_next = find_cell(pvec->cars, index_next, it->j() );
		if( * color_next == cl) {
			to_be_moved1.push_back(color_current);
			to_be_moved2.push_back(color_next);
			// immediate update of color 
			it->i() = index_next;
		}
	}
	std::vector<CarsDataIn::iterator>::iterator it1 = to_be_moved1.begin();
	std::vector<CarsDataIn::iterator>::iterator it2 = to_be_moved2.begin();
	for(std::size_t index=0; index < to_be_moved1.size(); ++index) {

		std::swap(*(*it1),*(*it2));
		++it1;
		++it2;

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

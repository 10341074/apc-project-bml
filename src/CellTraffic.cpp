#include <iostream>
#include <stdexcept>
#include <vector>

#include "Traffic.h"
#include "Tokenize.h"
#include "CellTraffic.h"

#define START '0'
CellTraffic::CellTraffic() :
	data_old(), data(), rmat(new CellMatrixRows(&data)), cmat(new CellMatrixCols(&data)), mat(rmat), mat_inactive(cmat) {
}
CellTraffic::~CellTraffic() {
	if(rmat != nullptr) {
		delete rmat; rmat = nullptr;
	}
	if(cmat != nullptr) {
		delete cmat; cmat = nullptr;
	}
}

std::istream & operator>>(std::istream & is, CellTraffic & traffic){
	std::string line;
	std::size_t rowsCount = 0;
	traffic.type = ByRows;
	while(getline(is,line)){
		traffic.tok_push_back(line,rowsCount);
		++rowsCount;
	}
//	std::cout << "Read from file " << traffic.type <<std::endl;
//	std::cout << * traffic.rmat;

//	traffic.rmat->border_columns();

//	traffic.rmat->update_data();
//	traffic.update_data();
	
	traffic.data.load_data(traffic.data_old);
	traffic.data_old.empty_data();
	traffic.rmat->update_data();
	
	traffic.mat = traffic.cmat;
	traffic.mat_inactive = traffic.rmat;
	return is;
}
void CellTraffic::tok_push_back(const std::string & line, const std::size_t & rowsCount) {
	const std::size_t len=line.length();
	const std::size_t colsTot = (len + 1)/2; 
	CarsData_Old row;
	row.push_back(CarsDataIn(colsTot));
	const char * p2one = &line[0];
//	std::size_t colsCount = 0;
	
	CarsDataIn & rowv =  * row.begin();
//	for( ; colsCount < colsTot; ++colsCount){
	for(CarsDataIn::iterator it = rowv.begin() ; it < rowv.end(); ++it){
		Color c = static_cast<Color>(*p2one -START);
//		row->push_back(c);
		it->get_color() = c;
		p2one+=2;
	}
//	if(rmat == nullptr)
//		throw std::logic_error("Traffic::tok_push_back null pmat");
//	if(type == ByRows)

	
//	if(rmat != nullptr)
//		this->rmat->push_back(row,colsTot);
	
	const std::size_t count = colsTot;
	CarsData_Old & 	cars 		= data_old.cars;
	if(cars.empty()) {
		data_old.inn_size = count;
	} else if(data_old.inn_size != count)
		throw std::runtime_error("CellTraffic::push_back row with different length");
	++data_old.ext_size;
	// add row
	cars.splice(cars.end(),row);

	return;
}
//*/
std::ostream & operator<<(std::ostream & os, const CellTraffic & traffic){
	if((traffic.type == ByRows) && (traffic.rmat != nullptr)) {
		os << * traffic.rmat;
	} else if ((traffic.type == ByCols) && (traffic.cmat != nullptr)) {
		os << * traffic.cmat;
	}
	return os;
}
void CellTraffic::print() const {
	data.print();
	return;
}
void CellTraffic::move_forward(const MatrixType & t, const Color & cl) {
	mat->move_forward(cl);
	std::swap(mat, mat_inactive);
/*
	if((t == ByRows) && (rmat != nullptr)) {
		rmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *rmat;
	} else if((t == ByCols) && (cmat != nullptr)) {
		cmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *cmat;
	}
//*/
	return;
}
void CellTraffic::move_white(const MatrixType & t, const Color & cl) {
	mat->move_white(cl);
	std::swap(mat, mat_inactive);
/*
	if((t == ByRows) && (rmat != nullptr)) {
		rmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *rmat;
	} else if((t == ByCols) && (cmat != nullptr)) {
		cmat->move_forward(cl);
//		std::cout << "move "<<type<<std::endl;
//		std::cout << *cmat;
	}
*/
	return;
}

void two_lines_old(CarsData_Old::iterator it_ext, CarsData_Old::iterator it_ext2, OneColor_Old & white, OneColor_Old & blue, OneColor_Old & red) {
		// current row
		CarsDataIn_Old::iterator it_in				= it_ext->begin();
		CarsDataIn_Old::iterator it_in_next		= it_in;	++it_in_next;
		CarsDataIn_Old::iterator it_in_end		= it_ext->end();
		// next row
		CarsDataIn_Old::iterator it_in2			= it_ext2->begin();
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
void CellTraffic::update_data() {
	std::cout << "update data traffic" << std::endl;
	OneColor_Old white;
	OneColor_Old blue;
	OneColor_Old red;

	CarsData_Old::iterator it_ext 			= data_old.cars.begin();
	CarsData_Old::iterator it_ext_end 	= data_old.cars.end();
	if(it_ext == it_ext_end) {			// empty matrix
		return;
	}
	if(it_ext->begin() == it_ext->end()){ // length zero row (check only first row)
		return;
	}
	
	CarsData_Old::iterator it_ext2 = it_ext; ++it_ext2;		// to next row
	for( ; it_ext2 != it_ext_end; ++it_ext2) {	// loop on rows, without last				
		two_lines_old(it_ext,it_ext2,white,blue,red);
		
		// advance 2 iterators
		++it_ext;	// advance current row with it_ext2 (next row)
	}
	// it_ext points to last
	// last row	
	two_lines_old(it_ext,data_old.cars.begin(),white,blue,red);
	
	OneColor_Old & lw = data_old.white;
	lw.splice(lw.end(), white);
	OneColor_Old & lb = data_old.blue;
	lb.splice(lb.end(), blue);
	OneColor_Old & lr = data_old.red;
	lr.splice(lr.end(), red);

	return;
}


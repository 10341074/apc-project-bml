#include "Data.h"

#define START '0'
Data::Data() : m_inp(new MatrixInp) {}
Data::~Data() {
  if(m_inp != nullptr) {
    delete m_inp;
    m_inp = nullptr;
    }
  if(m_lin != nullptr) {
    delete m_lin;
    m_lin = nullptr;
    }
  if(white != nullptr) {
    delete white;
    white = nullptr;
    }
  if(blue != nullptr) {
    delete blue;
    blue = nullptr;
    }
  if(red != nullptr) {
    delete red;
    red = nullptr;
    }
}
std::istream & operator>>(std::istream & is, Data & d){
  d.load_input(is);
  d.load_matrix();
  d.load_colors();
  d.update_statistics();
  return is;
}
void Data::load_input(std::istream & is) {
  std::string line;
  while(getline(is, line)) {
    tok_push_back(line);
  }
  return;
}
void Data::load_matrix() {
  if(cols_ <= rows_) {
    m_lin = new MatrixRow(rows_, cols_);
    m_lin->load_same_order(* m_inp);
    delete m_inp;
    } else {
    m_lin = new MatrixCol(rows_, cols_);
    m_lin->load_tran_order(* m_inp);
    delete m_inp;
    }
  return;
}
void Data::load_colors() {
  return;
}

void Data::update_statistics() {
  if(rows_ != m_lin->rows_count()) {
    throw std::logic_error("Data::update_statistics rows error");
  }
  if(cols_ != m_lin->cols_count()) {
    throw std::logic_error("Data::update_statistics cols error");
  }
  if(white_count_ != white->size()) {
    throw std::logic_error("Data::update_statistics white error");
  }
  if(blue_count_ != blue->size()) {
    throw std::logic_error("Data::update_statistics blue error");
  }
  if(red_count_ != red->size()) {
    throw std::logic_error("Data::update_statistics red error");
  }
  return;
}

void Data::tok_push_back(const std::string & line) {
  const std::size_t line_len = line.length();
  const std::size_t line_cols = (line_len + 1) / 2;
  if(m_inp->empty()) {
    cols_ = line_cols;
  } else if(cols_ != line_cols) {
    throw std::runtime_error("Data::tok_push_back row with different length");
    return;
  }
  ++rows_;
  
	m_inp->push_back(std::vector< Scalar >(line_cols));
	std::vector< Scalar > & row_to = * -- m_inp->end();

	const char * ptr_to_one = & line[0];
	
  for(std::vector< Scalar >::iterator it = row_to.begin() ; it < row_to.end(); ++it) {
    Scalar c = static_cast< Scalar >(* ptr_to_one -START);
    * it = c;
    ptr_to_one += 2;
  }
  return;
}
/*
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
void Data::update_data() {
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
*/


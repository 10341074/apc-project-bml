#include "VecVectorS.h"
VecVectorS::VecVectorS() {}
VecVectorS::~VecVectorS() {}

void VecVectorS::push_back(std::list<Car> & l2, const std::size_t & count) {
	++vec_len;
	if(vec.empty())
		cMaxIndex = count;
	else if(cMaxIndex != count)
		throw std::runtime_error("VecVector::push_back row with different length");
	
	vec.push_back( std::list<Car>());
	std::list<Car> & l1 = *(--vec.end());
	l1.splice(l1.begin(), l2);
	return;
}

std::ostream & operator<<(std::ostream & os, RowsVectorS & rowsvec) {
	Data::const_iterator it_ext = rowsvec.vec.begin();
	Data::const_iterator it_ext_end = rowsvec.vec.end();
	for( ; it_ext != it_ext_end; ++it_ext) {	// loop on rows
		std::list<Car>::const_iterator it = it_ext->begin();
		std::list<Car>::const_iterator it_next = it;
//		std::advance(it_next,1);
		++it_next;
		std::list<Car>::const_iterator it_end = it_ext->end();
		--it_end;
		for(std::size_t in = 0; in < it->J; ++in) {
			os << White << Separator;
		}
		for( ; it != it_end; ++it){
			std::size_t num = it_next->J - it->J - 1;
			os << it->A << Separator;
			for(std::size_t in = 0; in < num; ++in) {
				os <<	White << Separator;
			}
			++it_next;
		}
		os << it->A;
		std::size_t num = rowsvec.cMaxIndex - it->J - 1;
		for(std::size_t in = 0; in < num; ++in) {
			os <<	Separator << White;
		}
		os << std::endl;
	}
	return os;
}

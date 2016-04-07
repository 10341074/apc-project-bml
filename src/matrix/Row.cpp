#include "Row.h"

std::ostream & operator<<(std::ostream & os, const Row & v){
	Row::const_iterator it_end_before_last = v.end() - 1;
	for(Row::const_iterator it = v.begin(); it != it_end_before_last; ++it){
		os << *it << SEPARATOR;
	}
	os << *(v.end() - 1);
	os << std::endl;
	return os;
}


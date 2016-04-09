#include "Row.h"

std::ostream & operator<<(std::ostream & os, const Row & v){
	const Row::const_iterator it_end_before_last = v.end() - 1;
	for(Row::const_iterator it = v.begin(); it != it_end_before_last; ++it){
		os << *it << SEPARATOR;
	}
	os << * it_end_before_last;
	os << std::endl;
	return os;
}


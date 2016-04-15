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
std::ostream & operator<<(std::ostream & os, const std::list<std::list<Car>> & v){
	for(std::list<std::list<Car>>::const_iterator it = v.begin(); it != v.end(); ++it){
		os <<"riga "<< *it;
	}
	os << "//" << std::endl;
	return os;
}
std::ostream & operator<<(std::ostream & os, const std::list<Car> & v){
	for(std::list<Car>::const_iterator it = v.begin(); it != v.end(); ++it){
		os << it->A << "("<<it->I<<","<<it->J<<")";
		os << ":";
	}
	os << std::endl;
	return os;
}
std::ostream & operator<<(std::ostream & os, const std::list<std::list<Color>> & v) {
	for(std::list<std::list<Color>>::const_iterator it1 = v.begin(); it1 != v.end(); ++it1) {
		if(it1->begin() != it1->end()) {
			std::list<Color>::const_iterator it2_end = it1->end();
			--it2_end;
			std::list<Color>::const_iterator it2 = it1->begin();
			for( ; it2 != it2_end; ++it2) {
				os << * it2 << Separator;
			}
			os << * it2 << std::endl;
		}
	}
	return os;
}

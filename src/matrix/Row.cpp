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


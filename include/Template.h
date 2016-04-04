#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> std::ostream & operator<<(std::ostream & os, const std::vector<T> & v){
	for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it){
		os << *it << ", - ,";
	}
	os << std::endl;
	return os;
}

#endif

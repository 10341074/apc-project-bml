#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include "Car.h"
template <typename T> std::ostream & operator<<(std::ostream & os, const std::vector<T> & v){
	for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it){
		os << *it << ", - ,";
	}
	os << std::endl;
	return os;
}
// template <typename T> std::ostream & operator<<(std::ostream & os, const std::list<T> & v);
// template <typename T> std::ostream & operator<<(std::ostream & os, const std::list<T> & v){
//	for(typename std::list<T>::const_iterator it = v.begin(); it != v.end(); ++it){
// //		os << *it;
//		os << ",,";
//	}
//	os << std::endl;
//	return os;
// }
#endif

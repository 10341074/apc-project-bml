#include "Col.h"
DynColor & DynColor::operator=(const Row::iterator & it) {
	item = it;
	return * this;
}
DynColor & DynColor::operator=(Row::iterator && it) {
	item = it;
	return * this;
}
DynColor & DynColor::operator=(const Color & c) {
	* item = c;
	return * this;
}
DynColor & DynColor::operator=(Color && c) {
	* item = c;
	return * this;
}
DynColor & DynColor::operator++() {
	++ item;
	return * this;
}
std::ostream & operator<<(std::ostream & os, const DynColor & dc) {
	os << * dc.item;
	return os;
}
std::ostream & operator<<(std::ostream & os, const std::vector< DynColor> & cVec) {
	for(std::vector<DynColor>::const_iterator it = cVec.begin(); it != cVec.end()-1; ++it) {
		os << *it << SEPARATOR;
	}
	os << * (cVec.end()-1);
	os << std::endl;
	return os;
}

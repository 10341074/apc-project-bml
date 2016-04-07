#include "Col.h"
DynColor & DynColor::operator=(const Color & c) {
	* item = c;
	return * this;
}
DynColor & DynColor::operator=(Color && c) {
	* item = c;
	return * this;
}
DynColor & DynColor::operator=(const Row::iterator & it) {
	item = it;
	return * this;
}
DynColor & DynColor::operator=(Row::iterator && it) {
	item = it;
	return * this;
}
DynColor & DynColor::operator++() {
	++ item;
	return * this;
}

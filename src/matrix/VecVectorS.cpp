#include "VecVectorS.h"
VecVectorS::VecVectorS() {}
VecVectorS::VecVectorS(MatrixType t) : type(t) {}
VecVectorS::~VecVectorS() {}
VecVectorS::VecVectorS(const VecVectorS * p) :
	type(p->type), vec(p->vec), vec_size(p->vec_size), lin_size(p->lin_size) {}
void VecVectorS::push_back(std::list<Car> & l2, const std::size_t & count) {
	++vec_size;
	if(vec.empty()) {
		lin_size = count;
	} else if(lin_size != count)
		throw std::runtime_error("VecVector::push_back row with different length");
	
	vec.push_back( std::list<Car>());
	std::list<Car> & l1 = *(--vec.end());
	l1.splice(l1.begin(), l2);
	return;
}
RowsVectorS::RowsVectorS(const RowsVectorS & v) :
	VecVectorS(&v), rowsCount(v.rowsCount), colsCount(v.colsCount) {
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
		std::size_t num = rowsvec.lin_size - it->J - 1;
		for(std::size_t in = 0; in < num; ++in) {
			os <<	Separator << White;
		}
		os << std::endl;
	}
	return os;
}
void RowsVectorS::transpose(ColsVectorS & colsvec) {
	rowsCount = colsvec.rowsCount;
	colsCount = colsvec.colsCount;
	vec_size = colsvec.lin_size;
	lin_size = colsvec.vec_size;
	vec.clear();
	for(std::size_t in = 0; in < vec_size; ++in) {
		vec.push_back(std::list<Car>());
	}
	Data::iterator it = colsvec.vec.begin();
	for(std::size_t in = 0; in < lin_size; ++in) { // loop on colsvec lines
		std::list<Car> & l2 = * it;
		std::size_t k_tot = l2.size();
		Data::iterator it1 = vec.begin();
		std::size_t i = 0, i_old = 0; 
		for(std::size_t k = 0; k < k_tot; ++k) {
			i = ( l2.begin() )->I;
			std::advance(it1,i-i_old);
			it1->splice(it1->end(),l2,l2.begin());
			i_old = i;
		}
		++it;
	}
	return;
}
void RowsVectorS::print() const {
	std::cout << "Prova row " << std::endl<<vec << std::endl;
//	std::cout << vec;
	return;
}
void ColsVectorS::transpose(RowsVectorS & rowsvec) {
	rowsCount = rowsvec.rowsCount;
	colsCount = rowsvec.colsCount;
	vec_size = rowsvec.lin_size;
	lin_size = rowsvec.vec_size;
	vec.clear();
	for(std::size_t in = 0; in < vec_size; ++in) {
		vec.push_back(std::list<Car>());
	}
	Data::iterator it = rowsvec.vec.begin();
	for(std::size_t in = 0; in < lin_size; ++in) { // loop on rowsvec lines
		std::list<Car> & l2 = * it;
		std::size_t k_tot = l2.size();
		Data::iterator it1 = vec.begin();
		std::size_t j = 0, j_old = 0; 
		for(std::size_t k = 0; k < k_tot; ++k) {
			j = ( l2.begin() )->J;
			std::advance(it1,j-j_old);
			it1->splice(it1->end(),l2,l2.begin());
			j_old = j;
		}
		++it;
	}
	return;
}
ColsVectorS::ColsVectorS(const ColsVectorS & v) :
	VecVectorS(&v), rowsCount(v.rowsCount), colsCount(v.colsCount) {
}
std::ostream & operator<<(std::ostream & os, ColsVectorS & colsvec) {
	ColsVectorS cols2(colsvec);
	RowsVectorS rows2;
	cols2.print();
	rows2.transpose(cols2);
	rows2.print();
	os << rows2;
	return os;
}
void ColsVectorS::print() const {
	std::cout << "Prova col " << std::endl<< vec << std::endl;
	return;
}
std::ostream & operator<<(std::ostream & os, const std::list<std::list<Car>> & v){
	for(std::list<std::list<Car>>::const_iterator it = v.begin(); it != v.end(); ++it){
		os <<"riga "<< *it;
//		os << std::endl;
	}
	os << "//" << std::endl;
	return os;
}
std::ostream & operator<<(std::ostream & os, const std::list<Car> & v){
	for(std::list<Car>::const_iterator it = v.begin(); it != v.end(); ++it){
		os << it->A;
		os << ":";
	}
	os << std::endl;
	return os;
}


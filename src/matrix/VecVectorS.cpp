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
		std::list<Car>::const_iterator it_end = it_ext->end();
		for(std::size_t in = 0; (it!=it_end) && (in < it->J); ++in) {
			os << White << Separator;
		}
		std::list<Car>::const_iterator it_next = it;
		++it_next;
		it_end = it_ext->end();
		--it_end;
//		std::cout << "verifica"<< (it == it_end);
		for( ; it != it_end; ++it){
			std::size_t num = it_next->J - it->J - 1;
			os << it->A << Separator;
			for(std::size_t in = 0; in < num; ++in) {
				os <<	White << Separator;
			}
			++it_next;
		}
		std::size_t num = 0;
		if(it!=it_ext->end()) {
			os << it->A;
			num = rowsvec.lin_size - it->J - 1;
		} else {
			os << White;
			num = rowsvec.lin_size - 1;
		}
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
	std::cout << "Print by rows ("<<vec_size<<","<<lin_size<<")"<< std::endl<<vec << std::endl;
	return;
}
void RowsVectorS::move_forward(const Color & cl) {
	for(Data::iterator itv = vec.begin(); itv != vec.end(); ++itv) {	// loop on lines
		RowS & l = * itv;
		if(!l.empty()) {
			// add first as last
			l.push_back( * l.begin() );
			RowS::iterator itl_end = l.end();
			--itl_end;
//			std::cout << "end " << itl_end->A<<std::endl;
//			std::cout << "linnn " << l ; 
			itl_end->J += lin_size;
//			// move
			RowS::iterator itl = l.begin();
			RowS::iterator itl_next = l.begin();
//			++itl_next;
			std::size_t j_next = itl_next->J;
			for( ; itl != itl_end; ++itl) {
				++itl_next;
				j_next = itl_next->J;
				if((itl->A == cl) && (itl->J + 1 < j_next))
					++(itl->J);
			}
//			--itl_end;
			l.pop_back();
			itl_end = l.end(); // deque invaidates pointer?
			--itl_end;
			
			if(itl_end->J >= lin_size) {
				itl_end->J %= lin_size;
				l.splice(l.begin(),l,itl_end);
			}
		}
	}
//	this->print();
	return;
} 
ColsVectorS::ColsVectorS(const ColsVectorS & v) :
	VecVectorS(&v), rowsCount(v.rowsCount), colsCount(v.colsCount) {
}
std::ostream & operator<<(std::ostream & os, ColsVectorS & colsvec) {
	ColsVectorS cols2(colsvec);
	RowsVectorS rows2;
//	cols2.print();
	rows2.transpose(cols2);
//	rows2.print();
	os << rows2;
	return os;
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
//	std::cout << "transpose from rows "<< std::endl;
//	rowsvec.print();
	return;
}
void ColsVectorS::print() const {
	std::cout << "Print by cols (" <<vec_size<<","<<lin_size<<")"<< std::endl<< vec << std::endl;
	return;
}
void ColsVectorS::move_forward(const Color & cl) {
	for(Data::iterator itv = vec.begin(); itv != vec.end(); ++itv) {	// loop on lines
		RowS & l = * itv;
		if(!l.empty()) {
			// add first as last
			l.push_back( * l.begin() );
			RowS::iterator itl_end = l.end();
			--itl_end;
//			std::cout << "end " << itl_end->A<<std::endl;
//			std::cout << "linnn " << l ; 
			itl_end->I += lin_size;
//			// move
			RowS::iterator itl = l.begin();
			RowS::iterator itl_next = l.begin();
//			++itl_next;
			std::size_t i_next = itl_next->I;
			for( ; itl != itl_end; ++itl) {
				++itl_next;
				i_next = itl_next->I;
				if((itl->A == cl) && (itl->I + 1 < i_next))
					++(itl->I);
			}
//			--itl_end;
			l.pop_back();
			itl_end = l.end(); // deque invaidates pointer?
			--itl_end;
			
			if(itl_end->I >= lin_size) {
				itl_end->I %= lin_size;
				l.splice(l.begin(),l,itl_end);
			}
		}
	}
//	this->print();
//	std::cout<<*this;
	return;
} 


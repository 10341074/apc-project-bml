#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <CSC.h>
#include <Tokenize.h>
	
CSC::CSC(std::vector<Car> * p): Sparse(p) {}
CSC::CSC(std::unique_ptr< std::vector<Car> > & p): Sparse(p) {}
CSC::CSC(std::size_t nr, std::size_t nc, std::size_t nz, std::vector<Car> * p): Sparse(nr,nc,nz,p) {}
CSC::CSC(std::size_t nr, std::size_t nc, std::size_t nz, std::unique_ptr< std::vector<Car> > & p): Sparse(nr,nc,nz,p) {}


// Sparse::Sparse(): nz(), nr(), nc(), P(), V() {}
// Sparse::Sparse(std::vector<Car> * p): nz(), nr(), nc(), P(), V(p) {}
// Sparse::Sparse(std::unique_ptr< std::vector<Car> > & p): nz(), nr(), nc(), P(), V(&*p) {}

// Sparse::Sparse(size_type ni): nz(ni), nr(ni), nc(ni), V.I(ni+1), V.J(ni), A(ni) {}
// 
// Sparse::Sparse(size_type n,size_type ni): nz(ni), nr(n), nc(n), V.I(n+1), V.J(ni), A(ni){
//	if(ni > n*n) throw std::logic_error("Dimensions don't agree");
// }
// 
// Sparse::Sparse(size_type m,size_type n,size_type ni): nz(ni), nr(m), nc(n), V.I(m+1), V.J(ni), A(ni){
//	if(ni > m*n) throw std::logic_error("Dimensions don't agree");
// }
// 
// Sparse::Sparse(size_type ni, const Scalar & val): nz(ni), nr(ni), nc(ni), V.I(ni+1), V.J(ni), A(ni,val){
//	for(std::size_t i=0; i<ni; ++i){
//		V.I[i]=i;
//		V.J[i]=i;
// //		A[i]=val;
//		}
//	V.I[ni]=ni;
//	}//diagonal matrix

CSC::~CSC(){}	//Destructor

// void CSC::ostream(std::ostream & os) const{
//	std::vector<Car>::const_iterator				it=this->V->begin();
// //	std::vector<std::size_t>::const_iterator 	itJ=mat.V->J.begin();
// //	std::vector<Color>::const_iterator 			itA=mat.V->A.begin();
//	for(std::size_t k=0; k < this->nr; ++k){
//		for(int init = it->J; init>0; --init)		// zeri iniziali
//			os << White << SEPARATOR;
//		for(std::size_t cars = this->P[k]; cars < this->P[k+1]-1; ++cars){
//			os << it->A << SEPARATOR;
//			++it;
//			for(int spaces = (*this->V)[cars+1].J-(*this->V)[cars].J-1; spaces>0; --spaces)
//				os << White << SEPARATOR;
//		}
//		os << it->A;	// after move pointers
//		
//		if(it->J == this->nc-1)	os<<'\n';
//		else{
//			os << SEPARATOR;
//			for(int spaces = this->nc-1 - it->J; spaces>1; --spaces)
//				os << White << SEPARATOR;
//			os<<White<<'\n';
//		}
//		++it;
//	}
//	return;
// }	

// std::ostream & operator<<(std::ostream & os, const Sparse & mat){
//	std::vector<Car>::const_iterator				it=mat.V->begin();
// //	std::vector<std::size_t>::const_iterator 	itJ=mat.V->J.begin();
// //	std::vector<Color>::const_iterator 			itA=mat.V->A.begin();
//	for(std::size_t k=0; k<mat.nr; ++k){
//		for(int init = it->J; init>0; --init)		// zeri iniziali
//			os << White << SEPARATOR;
//		for(std::size_t cars = mat.P[k]; cars<mat.P[k+1]-1; ++cars){
//			os << it->A << SEPARATOR;
//			++it;
//			for(int spaces = (*mat.V)[cars+1].J-(*mat.V)[cars].J-1; spaces>0; --spaces)
//				os << White << SEPARATOR;
//		}
//		os << it->A;	// after move pointers
//		
//		if(it->J == mat.nc-1)	os<<'\n';
//		else{
//			os << SEPARATOR;
//			for(int spaces = mat.nc-1 - it->J; spaces>1; --spaces)
//				os << White << SEPARATOR;
//			os<<White<<'\n';
//		}
//		++it;
//	}
//	return os;
// }	
// std::istream & operator>>(std::istream & is, Sparse & mat){
//	mat.P.push_back(0);
//	std::string line;
// //	std::getline(is,line);
//	while(std::getline(is,line)){
//		mat.push_back(tokenize(line));
//	}
//	return is;
// }

void CSC::push_back(const std::vector<Color> & vec){
	std::size_t row=0;
	for(std::vector<Color>::const_iterator it=vec.begin(); it!=vec.end(); ++it){
		if(*it != White){
			++nz;
			V->push_back(Car(row,nc,*it));
//			V->A.push_back(*it);
//			V->J.push_back(col);
//			V->I.push_back(nr);
		}
		++row;
	}
	++nc;
	if(row>nr)	nr=row;
	P.push_back(nz);
return;	
}

// void Sparse::push_back(const std::vector<Color> & vec){
//	std::size_t col=0;
//	for(std::vector<Color>::const_iterator it=vec.begin(); it!=vec.end(); ++it){
//		if(*it != White){
//			++nz;
//			V->push_back(Car(nr,col,*it));
// //			V->A.push_back(*it);
// //			V->J.push_back(col);
// //			V->I.push_back(nr);
//		}
//	++col;
//	}
//	++nr;
//	if(col>nc)	nc=col;
//	P.push_back(nz);
// return;	
// }

// Color & CSR::operator()(const std::size_t i, const std::size_t j){
Color CSC::operator()(const std::size_t i, const std::size_t j) const {
	if((i>=nr) || (j>=nc)) throw std::out_of_range("Call out of range from sparse matrix");
	const Car * p = &((*V)[ P[j] ]);
	const Car * p_end = &((*V)[ P[j+1] ]);
	while(p != p_end){
		if(p->I == i) return p->A;
		++p;
	}
	return White;
}

// void Sparse::print_matrix() const {	// not efficient
//	if (nz==0){
//		std::cout<<"No print_matrix: empty matrix"<<std::endl;
//		return;
//		}
//	for(std::size_t i=0; i<nr; ++i){
//		for(std::size_t j=0; j<nc; ++j){
//			std::cout<<(*this)(i,j)<<'\t';
//			}
//		std::cout<<'\n';
//		}
//	return;
// }

void CSC::move_line(std::size_t line, Color cl){
//	std::vector<Color>::iterator itAend=V->A.begin() + P[line+1];
// 
//	std::vector<std::size_t>::iterator itJ1=V->J.begin() + P[line];
// //	std::vector<std::size_t>::iterator itJ2=itJ1+1;
	std::vector<Car>::iterator it=V->begin()+P[line];
	if(P[line]<P[line+1]){
		std::vector<Car>::iterator itEnd=V->begin()+P[line+1];
		std::size_t first = it->I;
		for(it=V->begin()+P[line]; it!=itEnd-1; ++it){	// correzione con ultimo
			if((it->A == cl) && ((it->I) + 1 < (it+1)->I))
				++(it->I);
		}
		if(((itEnd-1)->A == cl) && ((it->I) + 1 < nr + first))
	//		++(it->I);
			it->I = (it->I + 1) % nr;
	}
	return;
}

void CSC::transpose(){
	sort(V->begin(), V->end(),
		[](const Car & c1, const Car & c2){
			return c1.J < c2.J;
			});
	
	P=std::vector<std::size_t>(nc+1,0);
	std::size_t car=0;
	std::vector<Car>::iterator it = V->begin();
	for(std::size_t k=1; k<nc; ++k){
		while((it->J < k) && (car<nz)){
			++it;
			++car;
		}
	P[k]=car;
	}
	P[nc]=nz;
	return;
}


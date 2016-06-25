#ifndef CARSET_H
#define CARSET_H 
#include <iostream>
#include <stdexcept>
#include <vector>

#include <Color.h>
#include <Scalar.h>

class Car{
	public:
	std::size_t I;
	std::size_t J;
	Scalar A;
	
	Car(const std::size_t & i, const std::size_t & j, const Scalar & a): I(i), J(j), A(a) {}
};

#endif

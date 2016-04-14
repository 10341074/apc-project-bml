#ifndef CAR_H
#define CAR_H 
#include <iostream>
#include <stdexcept>
#include <vector>

#include <Color.h>

class Car{
	public:
	std::size_t I;
	std::size_t J;
	const Color A;
	
	Car(const std::size_t & i, const std::size_t & j, const Color & a) : I(i), J(j), A(a) {}
	Car(const Car & c) : I(c.I), J(c.J), A(c.A) {}
};

#endif
